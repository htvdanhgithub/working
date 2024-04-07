from flask import Flask, render_template, request, jsonify, send_file
from google.cloud import translate_v3 as tl
import os
import time

from google.oauth2.credentials import Credentials
from googleapiclient.discovery import build
from google.auth.transport.requests import Request
from google_auth_oauthlib.flow import InstalledAppFlow
import base64
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

# Define scopes and credentials file
SCOPES = ['https://www.googleapis.com/auth/gmail.send']
CREDS_FILE = 'client_secret_869150105846-dah25ig6jo1391aoia871b05ort32a1u.apps.googleusercontent.com.json'  # Replace with your credentials file

app = Flask(__name__)
# Set the GOOGLE_APPLICATION_CREDENTIALS environment variable to the path of your JSON key file
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = 'iconic-nimbus-411516-2e62e0e7d871.json'

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

def create_message(sender, to, subject, message_text):
    message = MIMEMultipart()
    message['to'] = to
    message['from'] = sender
    message['subject'] = subject
    msg = MIMEText(message_text)
    message.attach(msg)
    raw_message = base64.urlsafe_b64encode(message.as_bytes())
    raw_message = raw_message.decode()
    return {'raw': raw_message}

def get_credentials():
    creds = None
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json')
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                CREDS_FILE, SCOPES)
            creds = flow.run_local_server(port=0)
        with open('token.json', 'w') as token:
            token.write(creds.to_json())
    return creds

def send_email(sender, to, subject, message_text):
    creds = get_credentials()
    service = build('gmail', 'v1', credentials=creds)
    message = create_message(sender, to, subject, message_text)
    try:
        message = (service.users().messages().send(userId='me', body=message).execute())
        print('Message Id: %s' % message['id'])
    except Exception as error:
        print('An error occurred: %s' % error)

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

def delete_file(file_path):
    while True:
        try:
            os.remove(file_path)
            print(f"File '{file_path}' deleted successfully.")
            break
        except OSError as e:
            print(f"Error deleting file '{file_path}': {e}")

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

# Route to render the HTML form
@app.route('/')
def index():
    return render_template('index.html')

# Route to handle translation
@app.route('/translate', methods=['POST'])
def translate_text():
    try:
        text = request.form['text']

        source_language = request.form['source_language']
        target_language = request.form['target_language']
        file_chosen = False
        # Handle text file input
        if 'file' in request.files:
            text_file = request.files['file']
            if text_file.filename != '':
                file_chosen = True
                # Save the file temporarily
                temp_file_path = os.path.join(app.root_path, 'temp_file.txt')
                text_file.save(temp_file_path)

                # Read text from the file
                with open(temp_file_path, 'r', encoding='utf-8') as file:
                    text += file.read()

        # Translate the text
        #if not file_chosen:
            #text = text.encode("utf-8")

        translated_text = translate(text, map_languages[source_language], map_languages[target_language])
        if file_chosen:
            # Write translated text to a file
            filepath = generate_file_name()
            with open(filepath, 'w', encoding='utf-8') as file:
                file.write(translated_text)

            ## Send an email
            sender = 'htvdanh@gmail.com'
            to = 'htvdanh@gmail.com'
            subject = 'Test Email'
            message_text = 'This is a test email sent using the Gmail API.'

            send_email(sender, to, subject, message_text)

            # Send the file to the client
            return send_file(filepath, as_attachment=True)
        else:
            return render_template('result.html', translated_text=translated_text)

    except Exception as e:
        error_message = f"Error: {str(e)}"
        return render_template('error.html', error_message=error_message)

if __name__ == '__main__':
    app.run(debug=True)
