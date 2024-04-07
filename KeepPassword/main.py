from flask import Flask, request, render_template, send_file
from pymongo import MongoClient
from bson import ObjectId
import base64
import os

app = Flask(__name__)

# Connect to MongoDB
client = MongoClient('mongodb://localhost:27017/')
db = client['image_database']
collection = db['images']


# Route to render the HTML form
@app.route('/')
def index():
    if request.method == 'POST':
        if 'image' not in request.files:
            return render_template('upload.html', error='No image part')

        image_file = request.files['image']
        if image_file.filename == '':
            return render_template('upload.html', error='No selected image')

        # Read the image file
        image_data = image_file.read()

        # Convert image data to base64 string
        encoded_image = base64.b64encode(image_data).decode('utf-8')

        # Insert into MongoDB
        inserted_image = collection.insert_one({'image': encoded_image})

        return render_template('upload.html', message='Image uploaded successfully')

    return render_template('upload.html')


@app.route('/image/<image_id>')
def get_image(image_id):
    image_data = collection.find_one({'_id': ObjectId(image_id)})
    if image_data:
        # Decode base64 string to image data
        decoded_image = base64.b64decode(image_data['image'])

        # Save the image to a temporary file
        with open('temp_image.jpg', 'wb') as f:
            f.write(decoded_image)

        # Return the temporary image file
        return send_file('temp_image.jpg', mimetype='image/jpeg')

    return 'Image not found'


if __name__ == '__main__':
    app.run(debug=True)
