#include <SoftwareSerial.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include <OneWire.h>
#include <DallasTemperature.h>  
#define TRIGPIN A0
#define ECHOPIN A2
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial BT(3,4); //定義分別為 RX4 及 TX3 腳位
const int m1 = 5;
const int m2= 6;
const int leftMotorIn1 = 12;
const int leftMotorIn2 = 11;
const int rightMotorIn3 = 10;
const int rightMotorIn4 = 9;
int speed;
String sendData = "";
void setup()  
{
  speed=130;
  Serial.begin(9600);
  BT.begin(9600); 
  sensors.begin();
  pinMode(leftMotorIn1, OUTPUT); //左馬達
  pinMode(leftMotorIn2, OUTPUT);
  pinMode(rightMotorIn3, OUTPUT); //右馬達
  pinMode(rightMotorIn4, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  long pasttime = millis();
}
int ping(){  //超聲波感測器距離換算
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    return pulseIn(ECHOPIN, HIGH)/58;
}
void loop()
{ 
  long nowtime = millis();
  int temp = sensors.getTempCByIndex(0); //溫度感測 
  redlightleft(); //左側紅外線感測
  ultrasoundstop(); //超聲波防撞偵測
  int news = ping(); //距離參數
  sendData = "";
  sendData = String(news)+":"+String(temp)+":"; //儲存感測數值
  if( BT.available()) { //確認有無藍牙訊息
    char input = BT.read();
    Serial.println(input);  //輸出藍芽訊息
      analogWrite(m1,speed);
      analogWrite(m2,speed);
      if(input=='a') //檢查手機是否有傳指令
    {
      Serial.println("succeed!");
       for(int i=0;i<sendData.length();i++){  //簡易通訊協定
        BT.write(byte(sendData.charAt(i)));
        Serial.println(sendData.charAt(i));
      }
    }
  switch(input){  //移動指令
      case '1' :
        forward();  //前進
      break;
      
      case '2' :
        backward(); //後退
      break;
    
      case '3' :
        left(); //原地左轉
      break;
      
      case '4' :
        right();  //原地右轉
      break;
    
      case '5' :
        motorstop();  //停止
      break;
      
      case '6' :
        rightforward(); //右前
      break;
      
      case '7' :
        leftforward();  //左前
      break;
      
      case '8' :
        rightbackward();  //右後
      break;
      
      case '9' :
        leftbackward(); //左後
      break;
    }
  }
}
