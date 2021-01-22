// FOLLOWING'20 - hosted by RMI-NITT
// Developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]
// Phase 2 code
// To be uploaded in Arduino UNO
// .ino sketch 3/3

//Header file for communication between arduino and nodemcu
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
int x_current=0,y_current=0;
int count_x=0,count_y=0;

int p=0,q=0;

//motor driver pins
#define ena 11
#define enb 9
#define l1 12
#define l2 13
#define r1 8
#define r2 10

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
    qtr.calibrate(); // initial auto calibration
    }
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
  delay(1000);
}

void PID() //line follwer code
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(r1,HIGH);
  digitalWrite(r2,LOW);
    pos=qtr.readLineBlack(sensorvalues);
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
}

void x_move() // movement along x axis
{
  while(count_x<=p)
    {
      PID();
      if(sensorvalues[0]<500&&sensorvalues[1]<500&&sensorvalues[2]<500&&sensorvalues[3]<500&&sensorvalues[4]<500&&sensorvalues[5]<500)
        count_x++;
    }
      x_current=x_coordinate;
}

void y_move() // movement along y axis
{
  while(count_y<=q)
    {
      PID();
      if(sensorvalues[0]<500&&sensorvalues[1]<500&&sensorvalues[2]<500&&sensorvalues[3]<500&&sensorvalues[4]<500&&sensorvalues[5]<500)
        count_y++;
    }
    y_current=y_coordinate;
}

void loop() //loop
{
  count_x=0; //reseting
  count_y=0;
  while(!pat.available());
  ch=pat.read();
  int data= int(ch);
  x_coordinate=ch/10;
  y_coordinate=ch%10;
  p=x_current-x_coordinate;
  q=y_current-y_coordinate;
  if(p>0&&q>0) //case 1
  {
    if(dir==2)
      left();
    else if(dir==3)
      U_turn();
    else if(dir==4)
      right();
    y_move();
    right();
    x_move();
    dir=2; 
  }
  else if(p<0&&q>0) //case 2
  {
    p=p*(-1);
    if(dir==2)
    left();
    else if(dir==3)
    U_turn();
    else if(dir==4)
    right();
    y_move();
    left();
    x_move();
    dir=4;
  }
  else if(p>0&&q<0) //case 3
  {
    q=q*(-1);
    if(dir==2)
    right();
    else if(dir==1)
    U_turn();
    else if(dir==4)
    left();
    y_move();
    left();
    x_move();
    dir=2;
  }
  else if(p<0&&q<0) //case 4
  {
    p=p*(-1);
    q=q*(-1);
    if(dir==2)
    right();
    else if(dir==1)
    u_turn();
    else if(dir==4)
    left();
    y_move();
    right();
    x_move();
    dir=4;
  }
  else if(p>0&&q==0) //case 5
  {
    if(dir==1)
    right();
    else if(dir==3)
    left();
    else if(dir==4)
    U_turn();
    x_move();
    dir=2;
  }
  else if(p<0&&q==0) //case 6
  {
    p=p*(-1);
    if(dir==1)
    left();
    else if(dir==3)
    right();
    else if(dir==2)
    U_turn();
    x_move();
    dir=4;
  }
  else if(p==0&&q>0) //case 7
  {
    if(dir==2)
    left();
    else if(dir==3)
    U_turn();
    else if(dir==4)
    right();
    y_move();
    dir=1;
  }
  else if(p==0&&q<0) //case 8
  {
    q=q*(-1);
    if(dir==2)
    right();
    else if(dir==1)
    U_turn();
    else if(dir==4)
    left();
    y_move()
    dir=3;
  }
  else // case 9 - target same as current coordinate
  {
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
  }
}

// END OF CODE
