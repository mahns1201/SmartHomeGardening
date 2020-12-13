import time
import from_arduino
import to_firebase

def main():
    split = '='

    while True:
        from_arduino.make_file()
        print('update local txt file')
        time.sleep(5)

        to_firebase.upload_to_realtime()
        print("upload to realtime database")
        time.sleep(5)

        to_firebase.upload_to_firestore()
        print('upload to firestore')
        print(split * 105)
        time.sleep(300)

main()
