from flask import Flask, render_template, request, jsonify
from google.cloud import translate_v3 as tl
import os

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
def split_into_sentences(text):
    # Split the text into sentences using punctuation marks as delimiters
    # This is a simple example and may not cover all cases perfectly
    return [sentence for sentence in text.split('\n') if sentence]

def divide_into_subtexts(sentences):
    subtexts = []
    subtext = ""

    for sentence in sentences:
        if len(subtext) + len(sentence) >= 30000:
            print("subtext = {}".format(subtext))
            subtexts.append(subtext)
            subtext = sentence
        else:
            subtext += '\n' + sentence

    if len(subtext) + len(sentence) >= 30000:
        print("subtext = {}".format(subtext))
        subtexts.append(subtext)
        print("sentence = {}".format(sentence))
        subtexts.append(sentence)
    else:
        subtext += '\n' + sentence
        print("subtext = {}".format(subtext))
        subtexts.append(subtext)

    return subtexts

# Function to translate text from English to Vietnamese using Google Cloud Translation API
def translate(text, source_language_code, target_language_code):
    #print("translate text = {}, source_language_code = {}, target_language_code = {}".format(text, source_language_code, target_language_code))
    client = tl.TranslationServiceClient()

    # The project name is required to make an API call
    project_id = "iconic-nimbus-411516"
    location = "global"
    parent = f"projects/{project_id}/locations/{location}"

    subtexts = split_into_sentences(text)
    #print("sentences = {}".format(sentences))
    #subtexts = divide_into_subtexts(sentences)
    #print("subtexts = {}".format(subtexts))

    translated_text = ""
    for subtext in subtexts:
        # Create a translation request
        print("========================== subtext = {}".format(subtext))

        response = client.translate_text(
            parent=parent,
            contents=[subtext],
            mime_type="text/plain",  # The type of the content, plain text in this case
            source_language_code=source_language_code,
            target_language_code=target_language_code,
        )

        # Extract and return the translated text
        translations = response.translations
        translated_text += '\n' + translations[0].translated_text
        print("========================== translated_text = {}".format(translated_text))

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

        # Handle text file input
        if 'file' in request.files:
            text_file = request.files['file']
            if text_file.filename != '':
                # Save the file temporarily
                temp_file_path = os.path.join(app.root_path, 'temp_file.txt')
                text_file.save(temp_file_path)

                # Read text from the file
                with open(temp_file_path, 'r', encoding='utf-8') as file:
                    text += file.read()

        # Translate the text
        translated_text = translate(text, map_languages[source_language], map_languages[target_language])

        return render_template('result.html', translated_text=translated_text)
    except Exception as e:
        error_message = f"Error: {str(e)}"
        return render_template('error.html', error_message=error_message)


if __name__ == '__main__':
    app.run(debug=True)
