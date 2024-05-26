from flask import Flask, render_template, request, session, jsonify, send_file, make_response
from PIL import Image, ImageOps, ImageDraw
from flask_socketio import SocketIO, emit
from google.cloud import translate_v3 as tl
import os
import time
import logging
import pymongo
import re
import hashlib
import base64

#client = MongoClient('mongodb://localhost:27017/')
client = pymongo.MongoClient('mongodb://localhost:27017/')

# Check if the connection was successful
try:
    # The ismaster command is cheap and does not require auth.
    client.admin.command('ismaster')
    logging.info("MongoDB connection established successfully!")
except pymongo.errors.ConnectionFailure:
    logging.error("ERROR: Failed to connect to MongoDB.")

db = client['GlobalTalk']
collection = db['Users']

g_email = ""
selected_friend = ""
STATIC_DIR = "static/"
def hash_password(password):
    # Convert the password to bytes before hashing
    password_bytes = password.encode('utf-8')

    # Choose a hashing algorithm, such as SHA-256
    hash_algorithm = hashlib.sha256()

    # Update the hash object with the password bytes
    hash_algorithm.update(password_bytes)

    # Get the hexadecimal representation of the hashed password
    hashed_password = hash_algorithm.hexdigest()

    return hashed_password


def crop_to_square(input_image_path, output_image_path):
    # Open the input image
    image = Image.open(input_image_path)

    # Get the dimensions of the image
    width, height = image.size

    # Calculate the size of the square
    min_dimension = min(width, height)

    # Calculate the coordinates for cropping
    left = (width - min_dimension) / 2
    top = (height - min_dimension) / 2
    right = (width + min_dimension) / 2
    bottom = (height + min_dimension) / 2

    # Crop the image to a square
    square_image = image.crop((left, top, right, bottom))

    # Save the cropped image
    square_image.save(output_image_path)

def make_circle_image(input_image_path, output_image_path):
    # Open the input image
    image = Image.open(input_image_path)

    # Create a mask to crop the image to a circle
    mask = Image.new('L', image.size, 0)
    draw = ImageDraw.Draw(mask)
    width, height = image.size
    width = height = min(width, height)
    draw.ellipse((0, 0, width, height), fill=255)

    # Apply the mask to the grayscale image
    circular_image = ImageOps.fit(image, mask.size, centering=(0.5, 0.5))
    circular_image.putalpha(mask)

    # Save the circular image
    circular_image.save(output_image_path, format='PNG')

# Function to check if a document exists based on email, password, and point
def user_exists(email):
    query = {"email": email}
    result = collection.find_one(query)
    return result is not None

def record_exists(email, password):
    password = hash_password(password)
    query = {"email": email, "password": password}
    result = collection.find_one(query)
    return result is not None

# Function to insert a new document
def update_record(email, name, password, language, point, friends):
    password = hash_password(password)
    record = {"email": email, "name": name, "password": password, "language": language, "point": point, "friends": friends}
    if user_exists(email):
        delete_record(email)

    collection.insert_one(record)

# Function to update an existing document
def update_pwd(email, new_password, new_point):
    query = {"email": email}
    new_values = {"$set": {"password": new_password, "point": new_point}}
    collection.update_one(query, new_values)

# Function to delete a document
def delete_record(email):
    query = {"email": email}
    collection.delete_one(query)

# Function to update an existing document
def update_image(email, image):
    query = {"email": email}
    new_values = {"$set": {"image": image}}
    collection.update_one(query, new_values)

def get_image(email):
    query = {"email": email}
    result = collection.find_one(query)
    #print(result)
    if "image" in result:
        #print(result["image"])
        return result["image"]
    else:
        return None

# Function to update an existing document
def update_language(email, language):
    query = {"email": email}
    new_values = {"$set": {"language": language}}
    collection.update_one(query, new_values)

def get_language(email):
    query = {"email": email}
    result = collection.find_one(query)
    #print(result)
    #print(result["language"])
    return result["language"]

# Function to update an existing document
def add_friend(email, friend):
    friends = get_friends(email)
    friends.append(friend)
    update_friends(email, friends)

def delete_friends(email, friend):
    friends = get_friends(email)
    del friends[friend]
    update_friends(email, friends)

def update_friends(email, friends):
    query = {"email": email}
    new_values = {"$set": {"friends": friends}}
    collection.update_one(query, new_values)

def get_friends(email):
    query = {"email": email}
    result = collection.find_one(query)
    if not result:
        return []

    if "friends" in result:
        #print(result["friends"])
        return result["friends"]
    else:
        return []


def get_friends_map(friends):
    if not friends:
        return {}
    result = {}
    for friend in friends:
        result[friend] = get_name(friend)

    return result

# Function to update an existing document
def update_budget(email, point):
    query = {"email": email}
    new_values = {"$set": {"point": point}}
    collection.update_one(query, new_values)

def get_budget(email):
    query = {"email": email}
    result = collection.find_one(query)
    #print(result)
    #print(result["point"])
    return result["point"]

# Function to update an existing document
def update_name(email, name):
    query = {"email": email}
    new_values = {"$set": {"name": name}}
    collection.update_one(query, new_values)

def get_name(email):
    query = {"email": email}
    result = collection.find_one(query)
    #print(result)
    #print(result["name"])
    return result["name"]

def validate_email(email):
    # Regular expression pattern for validating email addresses
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    return re.match(pattern, email) is not None

app = Flask(__name__)
# Set the GOOGLE_APPLICATION_CREDENTIALS environment variable to the path of your JSON key file
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "iconic-nimbus-411516-2e62e0e7d871.json"
socketio = SocketIO(app)

# Define language mappings
map_languages = {'arabian':'ar',
                'basque':'eu',
                'bengal':'bn',
                'english':'en-GB',
                'portugese_brazil':'pt-BR',
                'bungary':'bg',
                'catalan':'ca',
                'cherokee':'chr',
                'croatia':'giờ',
                'czech':'cs',
                'danish':'da',
                'holland':'nl',
                'english_american':'en',
                'estonia':'et',
                'philippines':'fil',
                'finland':'fi',
                'french':'fr',
                'german':'de',
                'greek':'el',
                'gujarat':'gu',
                'hebrew':'iw',
                'hindi':'hi',
                'hungary':'hu',
                'iceland':'là',
                'indonesia':'id',
                'italia':'it',
                'japanese':'ja',
                'kannada':'hải lý',
                'korean':'ko',
                'latvia':'lv',
                'lithuania':'lt',
                'malay':'ms',
                'malayalam':'ml',
                'maratha':'mr',
                'norway':'no',
                'poland':'pl',
                'portugese':'pt-PT',
                'rumani':'ro',
                'russian':'ru',
                'serbia':'sr',
                'china_prc':'zh-CN',
                'slovakia':'sk',
                'slovenia':'sl',
                'spainese':'es',
                'swahili':'sw',
                'swedish':'sv',
                'tamil':'ta',
                'telugu':'te',
                'thai':'th',
                'china_taiwan':'zh-TW',
                'turkish':'tr',
                'urdu':'ur',
                'ukraina':'uk',
                'vietnam':'vi',
                'wales':'cy'
}

# Dictionary to store the connection ID of each client
clients = {}

filepath = ""
def crack_text(text, max_len):
    output = []
    start_index = 0
    text_len = len(text)
    while True:
        end_index = start_index + max_len
        #print("start_index = {}, end_index = {}, text = {}".format(start_index, end_index, text[start_index: end_index]))
        if end_index <= text_len - 1:
            last_newline_index = text.rfind('\n', start_index, end_index)
            #print("last_newline_index = {}, text = {}".format(last_newline_index, text[last_newline_index:]))
            output.append(text[start_index:last_newline_index])
            #print("=================Added text1 = {}".format(text[start_index:last_newline_index]))
            start_index = last_newline_index + 1
            if start_index > text_len:
                break
        else:
            output.append(text[start_index:])
            #print("=================Added text2 = {}".format(text[start_index:]))
            break

    return output

def generate_file_name():
    current_time_ms = int(time.time() * 1000)
    file_name = f"output_{current_time_ms}.txt"
    return file_name

# Function to translate text from English to Vietnamese using Google Cloud Translation API
def translate(text, source_language_code, target_language_code):
    #print("translate text = {}, source_language_code = {}, target_language_code = {}".format(text, source_language_code, target_language_code))
    client = tl.TranslationServiceClient()

    # The project name is required to make an API call
    project_id = "iconic-nimbus-411516"
    location = "global"
    parent = f"projects/{project_id}/locations/{location}"

    subtexts = crack_text(text, 30000)

    translated_text = ""
    for subtext in subtexts:
        # Create a translation request
        #print("========================== subtext = {}".format(subtext))
        if subtext:
            response = client.translate_text(
                parent=parent,
                contents=[subtext],
                mime_type="text/plain",  # The type of the content, plain text in this case
                source_language_code=source_language_code,
                target_language_code=target_language_code,
            )

            # Extract and return the translated text
            translations = response.translations
            if translated_text:
                translated_text += '\n'
            translated_text += translations[0].translated_text
        else:
            translated_text += '\n'

    return translated_text

@app.route('/change_image_link')
def change_image_link():
    return render_template('upload_image.html')

@app.route('/change_image', methods=['POST'])
def change_image():
    if 'image' not in request.files:
        return render_template('message.html', goback="/", message="ERROR: No image part...")

    image = request.files['image']
    #print('image {}'.format(image))
    if image.filename == '':
        return render_template('message.html', goback="/", message="ERROR: selected image")

    # Read the image file
    image_data = image.read()

    # Convert image data to base64 string
    encoded_image = base64.b64encode(image_data).decode('utf-8')

    # Insert into MongoDB
    global g_email
    update_image(g_email, encoded_image)
    global selected_friend

    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

@app.route('/change_language_link')
def change_language_link():
    global g_email
    language = get_language(g_email)
    return render_template('change_language.html', cur_language=language)

@app.route('/change_language', methods=['GET', 'POST'])
def change_language():
    global g_email

    language = request.form['language']

    update_language(g_email, language)
    global selected_friend

    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

@app.route('/change_budget_link')
def change_budget_link():
    global g_email
    budget = get_budget(g_email)
    return render_template('change_budget.html', cur_budget=budget)

@app.route('/change_budget', methods=['GET', 'POST'])
def change_budget():
    global g_email

    budget = request.form['budget']

    update_budget(g_email, budget)
    global selected_friend

    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

@app.route('/image1')
def image1():
    global selected_friend
    print("image1 called")
    print(f"selected_friend: {selected_friend}")

    if not selected_friend:
        return send_file('icons/account.png', mimetype='image/png')

    print(f"selected_friend: {selected_friend}")
    image_data = get_image(selected_friend)
    out_path = ""
    if image_data:
        # Decode base64 string to image data
        decoded_image = base64.b64decode(image_data)

        # Save the image to a temporary file
        with open('temp_image1_image.jpg', 'wb') as f:
            f.write(decoded_image)

        # Return the temporary image file
        out_path = 'temp_image1_image.jpg'
    else:
        out_path = 'icons/account.png'

    crop_to_square(out_path, 'temp_image1_round_image.jpg')
    make_circle_image('temp_image1_round_image.jpg', 'temp_image1_round_image.jpg')
    return send_file('temp_image1_round_image.jpg', mimetype='image/jpeg')


@app.route('/image')
def image():
    print("image called")
    global g_email
    image_data = get_image(g_email)
    out_path = ""
    if image_data:
        # Decode base64 string to image data
        decoded_image = base64.b64decode(image_data)

        # Save the image to a temporary file
        with open('temp_image_image.jpg', 'wb') as f:
            f.write(decoded_image)

        # Return the temporary image file
        out_path = 'temp_image_image.jpg'
    else:
        out_path = 'icons/account.png'

    crop_to_square(out_path, 'temp_image_round_image.jpg')
    make_circle_image('temp_image_round_image.jpg', 'temp_image_round_image.jpg')
    return send_file('temp_image_round_image.jpg', mimetype='image/jpeg')

    return 'Image not found'

@app.route('/select_friend_name', methods=['POST'])
def hello():
    data = request.json
    if 'friend' in data:
        return jsonify(friend_name=get_name(data['friend']))
    return jsonify(message="No text provided"), 400

@app.route('/select_friend', methods=['POST'])
def select_friend():
    print("select_friend called")
    global selected_friend
    selected_friend = request.json['friend']
    print(f"select_friend {selected_friend} selected")
    image_data = get_image(selected_friend)
    out_path = ""
    if image_data:
        # Decode base64 string to image data
        decoded_image = base64.b64decode(image_data)

        # Save the image to a temporary file
        with open('temp_select_friend_image.jpg', 'wb') as f:
            f.write(decoded_image)

        # Return the temporary image file
        out_path = 'temp_select_friend_image.jpg'
    else:
        out_path = 'icons/account.png'

    crop_to_square(out_path, 'temp_select_friend_round_image.jpg')
    make_circle_image('temp_select_friend_round_image.jpg', 'temp_select_friend_round_image.jpg')
    return send_file('temp_select_friend_round_image.jpg', mimetype='image/jpeg')

@app.route('/icon/<int:icon_id>')
def icon(icon_id):
    icon_paths = {
        1: 'icons/account.png',
        2: 'icons/add.png',
        3: 'icons/attachment.png',
        4: 'icons/budget.png',
        5: 'icons/emoji.png',
        6: 'icons/language.png',
        7: 'icons/picture.png',
        8: 'icons/settings.png',
        9: 'icons/sign_in.png',
        10: 'icons/sign_out.png'
    }
    icon_path = icon_paths.get(icon_id)
    if icon_path:
        return send_file(icon_path, mimetype='image/png')
    else:
        return 'Icon not found', 404

# Set the secret key for the session
app.secret_key = os.urandom(24)

def print_session_id():
    # Check if session ID cookie exists
    # Retrieve or generate session ID
    session_id = session.get('session_id')
    if not session_id:
        session['session_id'] = os.urandom(24).hex()
        session_id = session['session_id']

    print(f"Your session ID is: {session_id}")

# Route to render the HTML form
@app.route('/')
def index():
    print_session_id()
    ip_address = request.remote_addr
    logging.info(f"The IP address of the request is: {ip_address}")
    return render_template('signin.html')

@app.route('/translate')
def translate():
    ip_address = request.remote_addr
    logging.info(f"The IP address of the request is: {ip_address}")
    return render_template('translate.html', num_languagues=len(map_languages), passed='no')

@app.route('/chat')
def chat():
    print_session_id()
    ip_address = request.remote_addr
    logging.info(f"The IP address of the request is: {ip_address}")
    global g_email
    global selected_friend

    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

@app.route('/upload_image', methods=['POST'])
def upload_image():
    print_session_id()

    if 'image' not in request.files:
        return 'No image uploaded', 400

    image = request.files['image']

    if image.filename == '':
        return 'No image selected', 400

    # Read the image file
    image_data = image.read()

    # Convert image data to base64 string
    encoded_image = base64.b64encode(image_data).decode('utf-8')

    # Insert into MongoDB
    global g_email
    update_image(g_email, encoded_image)

    return render_template('upload_image.html', user=g_email)

@app.route('/upload_image_done', methods=['POST'])
def upload_image_done():
    global g_email
    global selected_friend
    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

# Route to handle translation
@app.route('/translate', methods=['POST'])
def translate_text():
    try:
        text = request.form['text']
        if text:
            text_chosen = True
        else:
            text_chosen = False

        source_language = request.form['source_language']
        target_language = request.form['target_language']

        # Handle text file input
        if (not text_chosen) and ('file' in request.files):
            text_file = request.files['file']
            if text_file.filename != '':
                # Save the file temporarily
                temp_file_path = os.path.join(app.root_path, 'temp_file.txt')
                text_file.save(temp_file_path)

                # Read text from the file
                with open(temp_file_path, 'r', encoding='utf-8') as file:
                    text += file.read()

        logging.info(f"Starting translating text size = {len(text)} characters...")
        translated_text = translate(text, map_languages[source_language], map_languages[target_language])
        logging.info(f"Translating done.")
        if not text_chosen:
            # Write translated text to a file
            global filepath
            filepath = "outputs/" + generate_file_name()
            with open(filepath, 'w', encoding='utf-8') as file:
                file.write(translated_text)
                logging.info(f"Output file = {filepath}.")

            return render_template('result_file.html')
        else:
            return render_template('result_text.html', translated_text=translated_text)

    except Exception as e:
        error_message = f"Error: {str(e)}"
        logging.error(error_message)
        return render_template('message.html', goback="/", message="ERROR: Please check the internet connection and try again...")

@app.route('/download')
def download():
    global filepath
    return send_file(filepath, as_attachment=True)

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    global g_email
    name = request.form['name']
    email = request.form['email']
    password = request.form['password']
    confirm_password = request.form['confirm_password']

    if not validate_email(email):
        return render_template('message.html', goback="/signup_link", message='ERROR: Email is in wrong format')

    if password != confirm_password:
        return render_template('message.html', goback="/signup_link", message='ERROR: Password not matched')

    language = request.form['language']

    point = 0
    g_email = email
    friends = []
    update_record(email, name, password, language, point, friends)
    return render_template('index.html')

@app.route('/signin', methods=['GET', 'POST'])
def signin():
    email = request.form['email']
    password = request.form['password']

    if not validate_email(email):
        return render_template('message.html', goback="/signin_link", message='ERROR: Email is in wrong format')

    if not record_exists(email, password):
        return render_template('message.html', goback="/signin_link", message='ERROR: Wrong user or password')

    global g_email
    g_email = email

    return render_template('index.html')

@app.route('/add_friend_link')
def add_friend_link():
    return render_template('add_friend.html')

@app.route('/addfriend', methods=['GET', 'POST'])
def addfriend():
    email = request.form['email']

    if not validate_email(email):
        return render_template('message.html', goback="/add_friend_link", message='ERROR: Email is in wrong format')

    if not user_exists(email):
        return render_template('message.html', goback="/add_friend_link", message='ERROR: Friend is not valid')

    global g_email
    add_friend(g_email, email)
    global selected_friend

    return render_template('chat.html', friend_selected=selected_friend, friends=get_friends_map(get_friends(g_email)))

@app.route('/signin_link')
def signin_link():
    return render_template('signin.html')

@app.route('/signup_link')
def signup_link():
    return render_template('signup.html')

@socketio.on('connect')
def handle_connect():
    connection_id = request.sid
    clients[connection_id] = True
    print(f"Client connected with ID: {connection_id}")
    emit('connection_id', connection_id)

@socketio.on('disconnect')
def handle_disconnect():
    connection_id = request.sid
    del clients[connection_id]
    print(f"Client disconnected with ID: {connection_id}")

if __name__ == '__main__':
    # Configure logging
    logging.basicConfig(filename='output.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

    #app.run(debug=True)
    from waitress import serve
    serve(app, host='0.0.0.0', port=8080)
    #socketio.run(app, allow_unsafe_werkzeug=True, debug=True)
