void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.write('A');
  delay(3000);
  Serial.write('B');
  delay(3000);
}

/*
#include <ESP8266WiFi.h>                                                
#include <FirebaseArduino.h>

// wifi
#define FIREBASE_HOST "fir-please-edec2.firebaseio.com" // http달린거 빼고 적어야 됩니다.
#define FIREBASE_AUTH "YM1pJNDozV21pY4Tfj6IDSQF0LnTTx1tI1ARDNSf" // 데이터베이스 비밀번호
#define WIFI_SSID "iarslab" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "iarslab0"


String fireStatus = "";                                                   
                                                         
void setup() {
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
  Firebase.setString("LED_STATUS", "OFF");
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);    // builtin led ON
  fireStatus = Firebase.getString("LED_STATUS");    

  char* led_status;
  fireStatus.toCharArray(led_status, fireStatus.length()+1);
  
  Serial.write(led_status);
  Serial.println(led_status);
  // Serial.println(fireStatus.length());
  delay(1000); 
}
*/
