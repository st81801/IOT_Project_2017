#include<Bridge.h>
#include <Servo.h> // 引用 Servo Library

Servo servoLeft; // 建立一個 Servo 物件 左輪
Servo servoRight;//右輪

const int irD1=A0; //中(center)紅外線循跡模組。 
const int irD2=A1; //左(left)紅外線循跡模組。
const int irD3=A2;//右(right)紅外線循跡模組。

int BuzzerPin = 2;

int light;

byte IRstatus=0;//紅外線循跡模組感應值

const int trig = 5;
const int echo = 6;
const int inter_time = 1000;
int time = 0;

void setup() {
  Bridge.begin();
  Console.begin();
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  
  servoLeft.attach(10);	             
  servoRight.attach(11);
  
  
  pinMode(irD1,INPUT_PULLUP); 
  pinMode(irD2,INPUT_PULLUP); 
  pinMode(irD3,INPUT_PULLUP);
  
}

void loop() {
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration/2)/29;
  int x;
  Console.println(distance);
  light=analogRead(A0);
  if(light>=500)
  {
    x=10;
  }
  else{
    x=0;
  }
    
  if(distance<=10)
  {
    servoLeft.writeMicroseconds(1500); 
    servoRight.writeMicroseconds(1500); 
     tone(BuzzerPin,523,500);  
    delay(500);    
    tone(BuzzerPin,587,500);  
    delay(500);    
    tone(BuzzerPin,659,500);
   }
  else{
        int val;
        IRstatus=0;
        val=analogRead(irD1);
        if(val<=500)
          IRstatus=(IRstatus+2);
          Console.print("irD1: ");
          Console.println(val);
          
         val=analogRead(irD2);
         if(val<=500)
          IRstatus=(IRstatus+4);
           Console.print("irD2: ");
          Console.println(val);
          
         val=analogRead(irD3);
         if(val<=500)
          IRstatus=(IRstatus+1);
           Console.print("irD3: ");
          Console.println(val);
          
           Console.print("IRstatus: ");
         Console.println(IRstatus);
        
        if(IRstatus==7 )  //前進
        {
          servoLeft.writeMicroseconds(1550-x); 
          servoRight.writeMicroseconds(1450+x); 
        }
        
         else if(IRstatus==1)  //快速右轉
        {
          servoLeft.writeMicroseconds(1550); 
          servoRight.writeMicroseconds(1550); 
        }
        else if(IRstatus==3)  //慢速右轉
        {
          servoLeft.writeMicroseconds(1550); 
          servoRight.writeMicroseconds(1550); 
        }
        else if(IRstatus==4)  //快速左轉
        {
          servoLeft.writeMicroseconds(1450); 
          servoRight.writeMicroseconds(1450); 
        }
        else if(IRstatus==6)  //慢速左轉
        {
          servoLeft.writeMicroseconds(1450); 
          servoRight.writeMicroseconds(1450); 
        }
        
        else if(IRstatus==5 ||IRstatus==0 || IRstatus==2)  //停止
        {
          servoLeft.writeMicroseconds(1500); 
          servoRight.writeMicroseconds(1500); 
        }
  }
}
