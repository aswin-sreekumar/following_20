// FOLLOWING'20 - hosted by RMI-NITT
// Developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]
// Phase 1 code
// To be uploaded in Arduino UNO
// .ino sketch 2/3

// communication between arduino and NodeMCU
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
int a,b,c,d;
int i=0;

//Input from NodeMCU
char ch,mn;

//PD
int pos,error,leftmotorspeed,rightmotorspeed,motorspeed,lasterror;
float kp=0.1,kd=0.2;
int x_coordinate=0,y_coordinate=0,dir=1;
int x_target=0,y_target=0;
int x_cuurent=0,y_current=0;

int flag=0; // for checking completion of route

//motor driver pins
#define ena 11
#define enb 9
#define l1 12
#define l2 13
#define r1 8
#define r2 10

void data_receive() //get coordinates from user
{
  while(!pat.available());
  ch=pat.read();
  int data= int(ch); //reading coordinates from NodeMCU
  x_coordinate=ch/10; // processing coordinates
  y_coordinate=ch%10; // processing coordinates
  y_target=y_coordinate;
  x_target=x_coordinate;
}

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
    qtr.calibrate(); // calibration
    }
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
  delay(1000);
  data_receive();
}

void rotate() // function to turn bot clockwise 90 deg
{
  if(dir!=4)
  dir++;
  else
  dir=1;
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  analogWrite(ena,100);
  analogWrite(enb,100);
  delay(500); // to be calibrated for approx right angle clockwise turn
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);
}

void check_pos() // check on node count/ coordinate count
{
  if(dir==1)
  {
    y_current++;
  }
  else if(dir==2)
  {
    x_current++;
  }
  if(y_current==y_target&&x_current!=x_target)
  rotate(); // y coordinate reached
  if(x_current==x_target&&y_current==y_target) // target reached, return to origin
  {
    if(flag==0)
    {
    rotate();
    delay(1000);
    x_current=0;
    y_current=0;
    x_target=x_coordinate;
    y_target=y_coordinate;
    dir=1;
    flag=1;
    }
    else // returned to origin
    {
     rotate(); // reset direction of bot
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
    data_receive(); //wait for next coordinate
    }
  }
}

void loop()
{
    while(1)
    {
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(r1,HIGH);
    digitalWrite(r2,LOW);
    pos=qtr.readLineBlack(sensorvalues); //PID code for line follower
   // Serial.println(pos); //debugging
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
    if(sensorvalues[0]<500&&sensorvalues[1]<500&&sensorvalues[2]<500&&sensorvalues[3]<500&&sensorvalues[4]<500&&sensorvalues[5]<500)
    { // node reached 
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      check_pos(); // check and keep track of coordinates 
    }
    }
}

// END OF CODE
