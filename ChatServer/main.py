from flask import Flask, render_template, request, redirect, url_for
from flask_socketio import SocketIO, emit
from pymongo import MongoClient
import logging
import re
import hashlib

app = Flask(__name__)
socketio = SocketIO(app)

# Connect to MongoDB
client = MongoClient('mongodb://localhost:27017/')

# Check if the connection was successful
try:
    # The ismaster command is cheap and does not require auth.
    client.admin.command('ismaster')
    print("MongoDB connection established successfully!")
except pymongo.errors.ConnectionFailure:
    print("ERROR: Failed to connect to MongoDB.")

db = client['chat_server']
users_collection = db['users']

#########################################################################
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
    result = users_collection.find_one(query)
    return result is not None

def record_exists(email, password):
    password = hash_password(password)
    query = {"email": email, "password": password}
    result = users_collection.find_one(query)
    return result is not None

# Function to insert a new document
def insert_record(email, password, point):
    password = hash_password(password)
    record = {"email": email, "password": password, "point": point}
    if user_exists(email):
        update_record(email, password, point)
    else:
        users_collection.insert_one(record)

# Function to update an existing document
def update_record(email, new_password, new_point):
    query = {"email": email}
    new_values = {"$set": {"password": new_password, "point": new_point}}
    users_collection.update_one(query, new_values)

# Function to delete a document
def delete_record(email):
    query = {"email": email}
    users_collection.delete_one(query)

def validate_email(email):
    # Regular expression pattern for validating email addresses
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    return re.match(pattern, email) is not None
#########################################################################
# Temporary storage for connected users
connections = {}

@app.route('/')
def index():
    return render_template('index.html', email='', passed='no')

@app.route('/signin_link')
def signin_link():
    return render_template('signin.html')

@app.route('/signup_link')
def signup_link():
    return render_template('signup.html')

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    email = request.form['email']
    password = request.form['password']
    confirm_password = request.form['confirm_password']

    if not validate_email(email):
        return render_template('message.html', goback="/signup_link", message='ERROR: Email is in wrong format')

    if password != confirm_password:
        return render_template('message.html', goback="/signup_link", message='ERROR: Password not matched')

    point = 0
    insert_record(email, password, point)
    return render_template('index.html', email=email, passed='yes')

@app.route('/signin', methods=['GET', 'POST'])
def signin():
    email = request.form['email']
    password = request.form['password']

    if not validate_email(email):
        return render_template('message.html', goback="/signin_link", message='ERROR: Email is in wrong format')

    if not record_exists(email, password):
        return render_template('message.html', goback="/signin_link", message='ERROR: Wrong user or password')

    return render_template('index.html', email=email, passed='yes')

@app.route('/add_friend', methods=['GET', 'POST'])
def add_friend():
    if request.method == 'POST':
        friend_name = request.form['friend_name']
        users_collection.insert_one({'name': friend_name})
        return redirect(url_for('index'))
    return render_template('add_friend.html')

@socketio.on('connect')
def handle_connect():
    connection_id = request.sid
    connections[connection_id] = {'language': ''}
    emit('update_id', {'connection_id': connection_id})

    # Load user's language preference from MongoDB
    user_data = users_collection.find_one({'connection_id': connection_id})
    if user_data:
        connections[connection_id]['language'] = user_data.get('language', '')

@socketio.on('disconnect')
def handle_disconnect():
    connection_id = request.sid
    connections.pop(connection_id, None)

@socketio.on('send_text')
def handle_send_text(data):
    sender_id = request.sid
    receiver_id = data['receiver_id']
    message = data['message']
    if connections[sender_id]['language'] == '':
        emit('error_message', {'message': 'Please select a language before sending text.'}, room=sender_id)
        return
    emit('receive_message', {'message': message, 'color': 'red'}, room=receiver_id)
    emit('receive_message', {'message': message, 'color': 'blue'}, room=sender_id)

@socketio.on('send_image')
def handle_send_image(data):
    sender_id = request.sid
    receiver_id = data['receiver_id']
    if connections[sender_id]['language'] == '':
        emit('error_message', {'message': 'Please select a language before sending an image.'}, room=sender_id)
        return
    image_url = data['image_url']
    emit('receive_image', {'image_url': image_url}, room=receiver_id)

@socketio.on('update_language')
def handle_update_language(data):
    connection_id = request.sid
    language = data['language']
    connections[connection_id]['language'] = language

    # Store user's language preference in MongoDB
    users_collection.update_one({'connection_id': connection_id}, {'$set': {'language': language}}, upsert=True)

if __name__ == '__main__':
    socketio.run(app, allow_unsafe_werkzeug=True, debug=True)
