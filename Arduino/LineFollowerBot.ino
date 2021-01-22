// FOLLOWING'20 - hosted by RMI-NITT
// Developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]
// Line Follower bot - basic code
// To be uploaded in Arduino UNO
// additional .ino sketch

#include<SoftwareSerial.h>

//IR Sensor operations file
#include<QTRSensors.h>

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

//PID
int pos,error,leftmotorspeed,rightmotorspeed,motorspeed,lasterror;
float kp=0.1,kd=0.2;

//motor driver pins
#define ena 11
#define enb 9
#define l1 12
#define l2 13
#define r1 8
#define r2 10

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
  while(!pat.available());
  ch=pat.read();
  ch='1';
  if(ch=='1')
  {
    a=1;b=0;c=1;d=0;
    analogWrite(ena,100);
    analogWrite(enb,100);
    digitalWrite(l1,a);
    digitalWrite(l2,b);
    digitalWrite(r1,c);
    digitalWrite(r2,d);
    for(i=0;i<200;i++)
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
    qtr.calibrate();
    }
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
    for(i=0;i<6;i++)
    pat.write(qtr.calibrationOn.maximum[i]/5);
    for(i=0;i<6;i++)
    pat.write(qtr.calibrationOn.minimum[i]/5);
    ch='0';
  }
}

void loop()
{
    while(!pat.available());
    mn=pat.read();
    if(mn=='3')
    {while(1){
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(r1,HIGH);
    digitalWrite(r2,LOW);
    pos=qtr.readLineBlack(sensorvalues);
   // Serial.println(pos);
    if(sensorvalues[0]>500&&sensorvalues[1]>500&&sensorvalues[2]>500&&sensorvalues[3]>500&&sensorvalues[4]>500&&sensorvalues[5]>500)
    {
      digitalWrite(l1,LOW);
      digitalWrite(l2,HIGH);
      digitalWrite(r1,LOW);
      digitalWrite(r2,HIGH);
    }
    else if(sensorvalues[0]<500&&sensorvalues[1]<500&&sensorvalues[2]<500&&sensorvalues[3]<500&&sensorvalues[4]<500&&sensorvalues[5]<500)
    {
      digitalWrite(l1,LOW);
      digitalWrite(l2,HIGH);
      digitalWrite(r1,LOW);
      digitalWrite(r2,HIGH);
    }
    lasterror=error;
    error=pos-2500;
    motorspeed=(kp*error)+(kd*(error-lasterror));
    rightmotorspeed=175+motorspeed;
    leftmotorspeed=175-motorspeed;
    if(leftmotorspeed>255) leftmotorspeed=255;
    if(rightmotorspeed>255)rightmotorspeed=255;
    if(leftmotorspeed<0) leftmotorspeed=0;
    if(rightmotorspeed<0) rightmotorspeed=0;
    analogWrite(ena,leftmotorspeed);
    analogWrite(enb,rightmotorspeed);
   // Serial.print(leftmotorspeed);
   // Serial.print('\t');
   // Serial.println(rightmotorspeed);
    for(i=0;i<6;i++)
    {
      Serial.print(sensorvalues[i]);
     Serial.print('\t');
    }
    Serial.println(" ");
    mn=pat.read();
    if(mn=='2')
    break;
    }}
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
}

// END OF CODE
