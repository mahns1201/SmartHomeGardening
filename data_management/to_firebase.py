import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
from firebase_admin import db

import datetime

# Use a service account
cred = credentials.Certificate('fir-please-edec2-firebase-adminsdk-c3j0b-b2c872b4e4.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://fir-please-edec2.firebaseio.com/'
    })

def upload_to_firestore():
    db = firestore.client()

    with open("sensor_value.txt", "r", encoding = 'UTF8') as f:
        data = f.readline()
        data = data.replace(" ", '')
        data = data.split(',')

        now = datetime.datetime.now()
        now = str(now)
        now = now[:-7]    # yyyy-mm-dd hh:mm:ss

        doc_ref = db.collection('sensor_value').document(now)
        doc_ref.set({
            u'light': data[0] + ' (lx)', 
            u'ppfd': data[1] + ' (ppfd)',
            u'humidity': data[2]  + ' (%)',
            u'temperature': data[3] + ' (℃)',
            u'soil_moisture': data[4] + ' (%)'
        })

def upload_to_realtime():
    
    

    ref = db.reference('arduino')

    with open("sensor_value.txt", "r", encoding = 'UTF8') as f:
        data = f.readline()
        data = data.replace(" ", '')
        data = data.split(',')

    ref.set({
        'light': {
            'sensor': data[0] + ' (lx)' 
        },
        'ppfd': {
            'sensor': data[1] + ' (ppfd)'
        },
        'humidity': {
            'sensor': data[2]  + ' (%)'
        },
        'temperature': {
            'sensor': data[3] + ' (℃)'
        },
        'soil_moisture': {
            'sensor': data[4] + ' (%)'
        },
    })
