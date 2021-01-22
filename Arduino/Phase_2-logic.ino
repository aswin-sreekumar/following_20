//This code is purely for understanding purposes. It was written for developing the logic/algorithm for phase-2
int x_i,y_i;//variables for initial coordinate values
int x,y;//variables for coordinate values to be recieved through WiFi
int count_x,count_y; //variables for counting
int a,b;
int count=0;
int dir;//direction in which the robot is facing. 1- north, 2-east, 3-south, 4-west

//define all other variables for calibration as in the previous program. This program is to illustrate the algorithm for the robot movement.Include
//necessary libraries

//define functions left(), right(), U_turn() to turn the robot accordingly

void left(){
  //robot turns left
  }
void right(){
  //robot turns right
}
void U_turn(){
  //robot takes a U-turn
}

void PID(){
  //include the PID function from the previous program here. This code makes the robot go along the black line.
}
void stop(){
  //stops the robot
}

void setup() {
  
//Add calibration code here
//define all input and output pins
x_i=0;y_i=0;//Robot starts at the origin
dir=1//initially facing north
}


void loop() {

  //show shapes to camera to get the coordinates
  //coordinates x and y to be sent wirelessly
a= x-x_i;
b=y-y_i;


//case 1
if(a>0&&b>0){
 if(dir==2){
  //facing east
  left();//turn north 
 }
 else if(dir==3){
  //facing south
  U_turn();//turn north
 }
 else if(dir==4){
  //facing west
  right();//turn north
 }
while(count_y<=b){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
  
}
//after the robot reaches the required y-coordinate, it has to turn right.
right(); 
while(count_x<=a){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;}
}
dir=2;
x_i=x;
y_i=y;
}

//case 2
if(a<0&&b>0){
  if(dir==2){
  //facing east
  left();//turn north 
 }
 else if(dir==3){
  //facing south
  U_turn();//turn north
 }
 else if(dir==4){
  //facing west
  right();//turn north
 }
 while(count_y<=b){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
  
}
//after the robot reaches the required y-coordinate, it has to turn left.
left(); 
while(count_x<=(-a)){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;}
}
dir=4;
x_i=x;
y_i=y;
}

//case 3
if(a>0&&b<0){
//robot has to turn south
 if(dir==2){
  //facing east
  right();//turn south 
 }
 else if(dir==1){
  //facing north
  U_turn();//turn south
 }
 else if(dir==4){
  //facing west
  left();//turn south
 }
 while(count_y<=(-b)){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
  
}
//after the robot reaches the required y-coordinate, it has to turn left.
left(); 
while(count_x<=a){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;} 
}
dir=2;
x_i=x;
y_i=y;
}

//case 4
if(a<0 && b<0){
 //robot has to turn south
 if(dir==2){
  //facing east
  right();//turn south 
 }
 else if(dir==1){
  //facing north
  U_turn();//turn south
 }
 else if(dir==4){
  //facing west
  left();//turn south
 }
 while(count_y<=(-b)){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
  
}
//after the robot reaches the required y-coordinate, it has to turn right.
right(); 
while(count_x<=(-a)){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;}
}
dir=4; 
x_i=x;
y_i=y;
}

//case5
if(a==0&&b==0){
  stop();
x_i=x;
y_i=y;  
}
//case 6
if(a>0&&b==0){
//robot has to turn towards east
if(dir==1)
right();
else if(dir==3)
left();
else if(dir==4)
U_turn();
while(count_x<=a){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;}
}
dir=2;
x_i=x;
y_i=y;

}
//case 7
if(a<0&&b==0){
//robot has to turn towards west
if(dir==1)
left();
else if(dir==3)
right();
else if(dir==2)
U_turn();
while(count_x<=(-a)){
  PID();
  if(/*sensors 0 and 5 detect black*/){
  count_x++;}
}
dir=4;
x_i=x;
y_i=y;

}
//case 8
if(a==0&&b>0){
//robot has to turn towards north
if(dir==2){
  //facing east
  left();//turn north 
 }
 else if(dir==3){
  //facing south
  U_turn();//turn north
 }
 else if(dir==4){
  //facing west
  right();//turn north
 }
while(count_y<=b){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
  }
 dir=1;
x_i=x;
y_i=y; 
}

//case 9
if(a==0&&b<0){
//robot has to turn south
 if(dir==2){
  //facing east
  right();//turn south 
 }
 else if(dir==1){
  //facing north
  U_turn();//turn south
 }
 else if(dir==4){
  //facing west
  left();//turn south
 }
 while(count_y<=(-b)){
  PID();//robot goes in a straight line
if(/*sensors 0 and 5 detect black*/){
  count_y++;}
   
}

}
}
