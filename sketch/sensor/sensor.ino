#include <Wire.h>           // 온습도, 조도센서 공동 라이브러리 선언
#include <BH1750FVI.h>      // 조도센서 라이프러리를 포함
#include <AM2320.h>         // 온습도센서 라이브러리를 포함
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Servo myservo ;

//-----------------------------<선언,정의>--------------------------------------
#define PIN_led 22
#define NUMPIXELS 8

#define SOIL A0
#define SERVO 9

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_led, NEO_GRB + NEO_KHZ800);

AM2320 th ;                         // 온도, 습도 동시측정
float NP_factor = 11.2658 ;         // Neopixel 변환인자  ★★★★★★!DO NOT CHANGE THE VALUE!★★★★★★

BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;
BH1750FVI LightSensor(DEVICEMODE );                                         
//-----------------------------------------------------------------------------

//-----------------------------<줄바꿈 정의함수>---------------------------------
void change() {
    Serial.println("*************Good to go next mate*************") ;
    Serial.println("") ;
    Serial.println("") ;
    Serial.println("") ;
}
int i = 0 ;
void count() {
    Serial.print("******************") ;
    Serial.print(i) ;
    Serial.println("th Report******************") ;
    }    
//-----------------------------------------------------------------------------

//-----------------------<현재 PPFD 계산 및 출력 함수 정의>------------------------
void Current_PPFD(float a,float b) {
    Serial.print("Light : ") ;
    Serial.print(a/b) ;
    Serial.print(',');
//    Serial.println(" µmol/m^2s") ;
}
//------------------------------------------------------------------------------

//    Light saturation point
//    Light compensation point


void setup() 
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(9600);           //공동 통신 속도
  LightSensor.begin();          //조도 센서 측정 시작

  Serial.println("") ;
  pinMode(SOIL, INPUT) ;           //토양수분센서 Pin
  myservo.attach(SERVO) ;                     // ServoMotor's pin number
  pixels.begin();
    
}

void loop()   
{
  i++ ;
  if (i >= 6) 
  {
    i = 6 ;
  }
  Serial.print(i);
  Serial.print("//") ;
//    count();
//**********************[조도센서]****************************** 

  // uint16_t lux = LightSensor.GetLightIntensity() ;
  uint16_t lux = light.readLightLevel();


  Serial.print("Light : ");
  Serial.print(lux);
  Serial.print(',');
//    Serial.println(" lux") ;                    //  조도센서 측정 값 (단위 Lux) LCD에는 여기만 나오면 될 듯
  Current_PPFD(lux,NP_factor) ;
  //delay(1) ;

//*************************************************************
//*************************[온습도센서]**************************

  th.Read() ;
  Serial.print("Humidity : ") ;                       // 서랍 속 습도 값 단위 (%)        
  Serial.print(th.h) ;
  Serial.print(',');                            
//    Serial.println("%") ;
  Serial.print("Temperature : ") ;                    // 온도 값, 단위 (C,도)
  Serial.print(th.t) ;       
  Serial.print(',');                    
//    Serial.println("C") ;
  //delay(1) ;

//*************************************************************
//**********[토양수분센서 (A3센서) 및 서보모터 작동]****************
  int Moisture = analogRead(SOIL) ;
  int Mois = map( Moisture, 0, 684, 0, 100) ;


  if (Mois <= 5) {
      myservo.write(30);  // Servo Motor 30도 (Open)  관수 작동
      Serial.print("Soil_Moisture : ") ;              // 토양 수분 습도 값 단위 (%), 일단은 센서 1개만 제어 중
      Serial.print( Mois ); 
      Serial.print(',');
//        Serial.print(" %  ----------");
//        Serial.println(" Not Enough Water") ;
  }
  else {
      myservo.write(130); // Servo Motor 130도 (Close)
      Serial.print("Soil_Moisture : ") ;
      Serial.println( Mois );                                                                                      
//        Serial.print(" %  ----------");
//       Serial.println(" Enough Water") ;
  }
  // delay(180000);
  delay(1000);
}
