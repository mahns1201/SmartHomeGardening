import time
import from_arduino
import to_firebase

def main():
    while True:
        from_arduino.make_file()
        print('update file')
        time.sleep(5)

        to_firebase.upload_to_realtime()
        print("update realtime database")
        time.sleep(5)

        to_firebase.upload_to_firestore()
        print('upload to firestore')
        time.sleep(30)

main()
