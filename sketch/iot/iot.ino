#include <ESP8266WiFi.h>                                                
#include <FirebaseArduino.h>  
#include <Adafruit_NeoPixel.h>
#include <Servo.h>  

Servo myservo;

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define FIREBASE_HOST "fir-please-edec2.firebaseio.com" // http달린거 빼고 적어야 됩니다.
#define FIREBASE_AUTH "YM1pJNDozV21pY4Tfj6IDSQF0LnTTx1tI1ARDNSf" // 데이터베이스 비밀번호
#define WIFI_SSID "iarslab" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "iarslab0"

#define PIN_led 0
#define PIN_watering 16
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_led, NEO_GRB + NEO_KHZ800);

// String LED = "";       
String watering = "";                                            
                                                         
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
  Serial.println(WiFi.localIP());                                                 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     
  
  // pixels.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(PIN_watering);
}

void loop() {
  // LED = Firebase.getString("LED_STATUS");     
  watering = Firebase.getString("WATERING_STATUS");

  /*
  if (LED == "ON") {                                                        
    Serial.println("Led Turned ON");                         
    
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 255));
    pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 255));
    pixels.setPixelColor(4, pixels.Color(255, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 255));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 0, 255));
    pixels.show();

    digitalWrite(LED_BUILTIN, LOW);
  }                                                  
  else if (LED == "OFF") {                                                
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                               
    pixels.clear();
    pixels.show();
  }
  */
  
  if (watering == "ON")
  {
    myservo.write(60);
  }
  
  else if (watering == "OFF")
  {
    myservo.write(15);
  }
}
