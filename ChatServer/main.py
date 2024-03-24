import os
from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'
socketio = SocketIO(app)

# Dictionary to store the connection ID of each client
clients = {}

# Dictionary to store the selected language of each client
languages = {}

@app.route('/')
def index():
    return render_template('index.html')

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

@socketio.on('set_language')
def handle_set_language(data):
    connection_id = request.sid
    language = data['language']
    languages[connection_id] = language
    print(f"Language set for client {connection_id}: {language}")

@socketio.on('send_text_message')
def handle_send_text_message(data):
    sender_id = request.sid
    recipient_id = data['recipient_id']
    message = data['message']
    print(f"Text message sent from {sender_id} to {recipient_id}: {message}")
    emit('text_message', {'sender_id': "You", 'message': message}, room=recipient_id)

@socketio.on('send_image')
def handle_send_image(data):
    sender_id = request.sid
    recipient_id = data['recipient_id']
    image = data['image']
    print(f"Image sent from {sender_id} to {recipient_id}: {image}")
    emit('image', {'sender_id': sender_id, 'image': image}, room=recipient_id)
    #emit('image', {'sender_id': sender_id, 'image': image}, room=sender_id)  # Echo image back to sender

if __name__ == '__main__':
    socketio.run(app, allow_unsafe_werkzeug=True, debug=True)
