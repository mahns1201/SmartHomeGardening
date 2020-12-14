#include <ESP8266WiFi.h>                                                
#include <FirebaseArduino.h>  
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define FIREBASE_HOST "fir-please-edec2.firebaseio.com" // http달린거 빼고 적어야 됩니다.
#define FIREBASE_AUTH "YM1pJNDozV21pY4Tfj6IDSQF0LnTTx1tI1ARDNSf" // 데이터베이스 비밀번호
#define WIFI_SSID "iarslab" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "iarslab0"

#define PIN 0
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String fireStatus = "";                                                   
                                                         
void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  Serial.begin(115200);
  delay(1000);
  
        
  
                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                             
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Firebase.setString("LED_STATUS", "OFF");
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  fireStatus = Firebase.getString("LED_STATUS");                                      // get ld status input from firebase
  if (fireStatus == "ON") {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    pixels.setPixelColor(1, pixels.Color(0, 150, 0));
    pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    pixels.setPixelColor(3, pixels.Color(0, 150, 0));
    pixels.setPixelColor(4, pixels.Color(0, 150, 0));
    pixels.setPixelColor(5, pixels.Color(0, 150, 0));
    pixels.setPixelColor(6, pixels.Color(0, 150, 0));
    pixels.setPixelColor(7, pixels.Color(0, 150, 0));
    pixels.show();

    digitalWrite(LED_BUILTIN, LOW);
  }                                                  
  else if (fireStatus == "OFF") {                                                  // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                               // make bultin led OFF
    pixels.clear();
    pixels.show();
  }
  
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
}
