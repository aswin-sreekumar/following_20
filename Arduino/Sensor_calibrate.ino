// FOLLOWING'20 - hosted by RMI-NITT
// Developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]
// Sensor calibration and verification code
// To be uploaded in Arduino UNO
// .ino sketch 1/3

//File for communication between NodeMCU and Arduino
#include<SoftwareSerial.h>

//IR Sensor operations file
#include<QTRSensors.h>

//motor driver pins
#define ena 11
#define enb 9
#define l1 12
#define l2 13
#define r1 8
#define r2 10

//Declaring data communication object
SoftwareSerial pat(5,6);

//Declaring IR sensor object
QTRSensors qtr;

//Global variables
//Sensor values
int sensorvalues[6];
int i=0;

//Input from NodeMCU
char ch,mn;

int a,b,c,d;

//setup
void setup()
{
  Serial.begin(9600);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  digitalWrite(ena,LOW);
  digitalWrite(enb,LOW);
  pat.begin(9600);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5},6);
  delay(500);
  while(!pat.available()&&mn);
  mn=pat.read();
}

void loop()
{
 if(mn=='z') //received from NodeMCU
 {
  while(!pat.available());
  ch=pat.read(); //read incoming byte value as character and change bot parameters accordingly
  //Serial.println(char(a)); //debugging
  if(ch==49) // accelerate
  { 
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(r1,HIGH);
    digitalWrite(r2,LOW);
  }
  else if(ch==50) //left
  {
    analogWrite(ena,100);
    analogWrite(enb,100);
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(r1,HIGH);
    digitalWrite(r2,LOW);
  }
  else if(ch==51) //reverse
  {
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(r1,LOW);
    digitalWrite(r2,HIGH);
  }
  else if(ch==52) //right
  {
    analogWrite(ena,100);
    analogWrite(enb,100);
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,HIGH);
  }
  else if(ch==48) //brake
  {
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
  }
  else if(ch==97) //gear 1
  {
    pwm=100;
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
  }
  else if(ch==98) //gear 2
  {
    pwm=138;
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
  }
  else if(ch==99) //gear 3
  {
    pwm=176;
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
  }
  else if(ch==100) //gear 4
  {
    pwm=214;
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
  }
  else if(ch==101) //gear 5
  {
    pwm=255;
    analogWrite(ena,pwm-2);
    analogWrite(enb,pwm);
  }
  else
    mn=ch;
 }
 else if(mn=='y') // character from bot for sensor calibration initiate
 {
  while(!pat.available());
  ch=pat.read();
  if(ch=='1')
  {
    a=1;b=0;c=1;d=0;
    analogWrite(ena,100);
    analogWrite(enb,100);
    digitalWrite(l1,a);
    digitalWrite(l2,b);
    digitalWrite(r1,c);
    digitalWrite(r2,d);
    for(i=0;i<200;i++) // move bot perendicular to line for calibration
    {
      if(i%30==0)
      {
        a=!a;
        b=!b;
        c=!c;
        d=!d;
      digitalWrite(l1,a);
      digitalWrite(l2,b);
      digitalWrite(r1,c);
      digitalWrite(r2,d);
      }
    qtr.calibrate(); // auto calibrate
    }
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
    for(i=0;i<6;i++)
    pat.write(qtr.calibrationOn.maximum[i]/5); //sending calibrated value to NodeMCU
    for(i=0;i<6;i++)
    pat.write(qtr.calibrationOn.minimum[i]/5); //sending calibrated value to NodeMCu
  }
  else
    mn=ch; //updating command from client
 }
}

// END OF CODE
