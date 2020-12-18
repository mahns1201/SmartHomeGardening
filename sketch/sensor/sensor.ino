#include <Wire.h>           // 온습도, 조도센서 공동
#include <BH1750FVI.h>      // 조도센서
#include <AM2320.h>         // 온습도센서
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// 선언
Servo myservo ;

#define PIN_led 22
#define NUMPIXELS 8
#define SOIL A0
#define SERVO 9
#define FAN_INPUT A7
#define FAN_OUTPUT 8

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_led, NEO_GRB + NEO_KHZ800);

AM2320 th ;                         // 온도, 습도 동시측정
float NP_factor = 11.2658 ;         // Neopixel 변환인자  ★★★★★★!DO NOT CHANGE THE VALUE!★★★★★★

BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;
BH1750FVI LightSensor(DEVICEMODE );                                         

void change()  // 줄바꿈 정의
{
  Serial.println("*************Good to go next mate*************");
  Serial.println("");
  Serial.println("");
  Serial.println("");
}

int i = 0 ;

void count() 
{
  Serial.print("******************") ;
  Serial.print(i) ;
  Serial.println("th Report******************") ;
}

void Current_PPFD(float a,float b)  // PPFD 환산
{
  Serial.print("Light : ") ;
  Serial.print(a/b) ;
  Serial.print(',');
}

void setup() 
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(9600);  //공동 통신 속도
  pinMode(FAN_INPUT, INPUT) ;
  pinMode(FAN_OUTPUT, OUTPUT) ;
  LightSensor.begin();  //조도 센서 측정 시작

  Serial.println("");
  pinMode(SOIL, INPUT);  //토양수분센서 Pin
  myservo.attach(SERVO);  // ServoMotor's pin number
  pixels.begin();
}

void loop()   
{
  i++;
  if (i >= 6) 
  {
    i = 6;
  }
  Serial.print(i);
  Serial.print("//");
  
  // 조도센서
  uint16_t lux = LightSensor.GetLightIntensity();

  Serial.print("Light : ");
  Serial.print(lux);
  Serial.print(',');
  // Serial.println(" lux");  // 조도센서 측정 값 (단위 Lux) LCD에는 여기만 나오면 될 듯
  Current_PPFD(lux,NP_factor);

  // 온습도센서

  th.Read();
  Serial.print("Humidity : ");  // 서랍 속 습도 값 단위 (%)        
  Serial.print(th.h);
  Serial.print(',');                            
  Serial.print("Temperature : ");  // 온도 값, 단위 (C,도)
  Serial.print(th.t);       
  Serial.print(',');


  // fan 동작
  if (th.t >= 26)
  {
    digitalWrite(FAN_OUTPUT, HIGH);
  }
  else
  {
    digitalWrite(FAN_OUTPUT, LOW);
  }

  // 토양수분센서
  int Moisture = analogRead(SOIL);
  int Mois = map( Moisture, 0, 684, 0, 100);
  
  myservo.write(130); // Servo Motor 130도 (Close)
  Serial.print("Soil_Moisture : ");
  Serial.println( Mois );                                                                                      
  
  // LED
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 255));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 255));
  pixels.setPixelColor(4, pixels.Color(255, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 255));
  pixels.setPixelColor(6, pixels.Color(255, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 255));
  pixels.show();
  
  // delay(180000);
  delay(1000);
}
