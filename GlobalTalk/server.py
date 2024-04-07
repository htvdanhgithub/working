from flask import Flask, render_template, request, jsonify, send_file
from google.cloud import translate_v3 as tl
import os
import time
import logging
import pymongo
import re
import hashlib

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
def insert_record(email, password, language, point):
    password = hash_password(password)
    record = {"email": email, "password": password, "language": language, "point": point}
    if user_exists(email):
        update_record(email, password, point)
    else:
        collection.insert_one(record)

# Function to update an existing document
def update_record(email, new_password, new_point):
    query = {"email": email}
    new_values = {"$set": {"password": new_password, "point": new_point}}
    collection.update_one(query, new_values)

# Function to delete a document
def delete_record(email):
    query = {"email": email}
    collection.delete_one(query)

def validate_email(email):
    # Regular expression pattern for validating email addresses
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    return re.match(pattern, email) is not None

app = Flask(__name__)
# Set the GOOGLE_APPLICATION_CREDENTIALS environment variable to the path of your JSON key file
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "iconic-nimbus-411516-2e62e0e7d871.json"

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

# Route to render the HTML form
@app.route('/')
def index():
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
    ip_address = request.remote_addr
    logging.info(f"The IP address of the request is: {ip_address}")
    return render_template('chat.html', num_languagues=len(map_languages), passed='no')

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
    email = request.form['email']
    password = request.form['password']
    confirm_password = request.form['confirm_password']

    if not validate_email(email):
        return render_template('message.html', goback="/signup_link", message='ERROR: Email is in wrong format')

    if password != confirm_password:
        return render_template('message.html', goback="/signup_link", message='ERROR: Password not matched')

    language = request.form['language']

    point = 0
    insert_record(email, password, language, point)
    return render_template('index.html')

@app.route('/signin', methods=['GET', 'POST'])
def signin():
    email = request.form['email']
    password = request.form['password']

    if not validate_email(email):
        return render_template('message.html', goback="/signin_link", message='ERROR: Email is in wrong format')

    if not record_exists(email, password):
        return render_template('message.html', goback="/signin_link", message='ERROR: Wrong user or password')

    return render_template('index.html')


@app.route('/signin_link')
def signin_link():
    return render_template('signin.html')

@app.route('/signup_link')
def signup_link():
    return render_template('signup.html')

if __name__ == '__main__':
    # Configure logging
    logging.basicConfig(filename='output.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

    #app.run(debug=True)
    from waitress import serve
    serve(app, host='0.0.0.0', port=8080)
