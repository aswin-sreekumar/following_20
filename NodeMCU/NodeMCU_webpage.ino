// NodeMCU code for sending webpage scripts and acting as communication gateway for data exchange between user and Arduino
// Developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]

// The bot uses WiFi as commnunication medium. The NodeMCU connects to LAN by mobile hotsopt and gets a local IP.
// Using the IP, the server can be accessed. Upon request, the server sends webpage script.
// LOGIN - password : 7246 [ To avoid network traffic in case the LAN gets compromised ]

// Main concept : URL manipulation.
// URL is custom made and read by client and server to understand about the process required and data sent and received.
// From the entire code, its evident that the URL manipulation runs the entire communication smoothly

// We chose this method because we didnt know basics of Javascript and local client memory needed for the project at the time of development.


// required headerfiles
#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>

//global variables for overall webpage
const char* ssid="Asw1n Sreekumar"; // name of LAN created
const char* pswd="ask12345"; // password of LAN created

unsigned long currentTime=millis(); // used for timeout calculation : in case of connection closing and errors in requests
unsigned long previousTime=0;
const long timeoutTime=2000;

String header;

//Global variables for login check
int login_z=0;
String login_pass="Z";

//Initialising Web Server and Arduino Serial
// Please note: the NodeMCU is a gateway of communication.
// So, channel to Arduino is pat.
//      Channel to user is client
//      Channel to serial port for error debugging and local IP is Serial

WiFiServer server(80); // use port 80
SoftwareSerial pat(D5,D6);

//Global variables for sensor calibration
int sc_sensormin[6],sc_sensormax[6];

//Global variables for Phase 2/3 data communication
String ph23_x="",ph23_y="";

//Global variables for phase 1 data communication
int ph1_x=-1,ph1_y=-1;

//Global variables for PID initiating and terminating
int pid_z=0;

//Setup - Initialises server and serial and displays IP address
void setup()
{
  pat.begin(9600);
  Serial.begin(9600);
  Serial.print("Connecting to :");
  Serial.println(ssid);
  WiFi.begin(ssid,pswd);
  while(WiFi.status()!=WL_CONNECTED) // wait till server connects to LAN
  {
    delay(500);
    Serial.print('.');
  }
  Serial.println("");
  Serial.println("IP ADDRESS :");
  Serial.println(WiFi.localIP()); //prints local IP assigned to NodeMCU from LAN
  server.begin();
}


//loop
void loop()
{
  //initialising and setting up webpage
  WiFiClient client=server.available(); // client is the object of user
  if(client)
  {
    Serial.println("NEW CLIENT");
    String currentLine="";
    currentTime=millis();
    previousTime=currentTime;
    while(client.connected()&&currentTime-previousTime<timeoutTime) // client connected and timeout doesnt occur
    {
      currentTime=millis();
      if(client.available())
      {
        char c=client.read();
        Serial.write(c);
        header+=c;
        if(c=='\n')
        {
          if(currentLine.length()==0)
          { 
            //Webpage begins
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            //Front end Scripting begins
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            //Title
            client.println("<title>GA_one/FOLLOWING'20</title>");

            //CSS styling script begins
           client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
           client.println(".button{ background-color: rgb(1, 86, 143); border: none; color: white; padding: 10px 17px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}");
           client.println(".button2{background-color: green; border: none; color: white; padding: 10px 17px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}");
           client.println(".button3 button{background-color: rgb(1, 86, 143);border: none; color: white; padding: 10px 17px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}");
           client.println(".button4 button{background-color: rgb(25, 25, 221);border: none; color: white; padding: 10px 17px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}");
           client.println(".button5 button{background-color: rgb(255,0,0)    ;border: none; color: white; padding: 10px 20px;text-decoration: none; font-size: 10px; margin: 5px; cursor: pointer}");
           client.println(".pin{color: rgb(255,0,0); text-align: center;font-size: 20px;}");
           client.println(".main {color:red;font-size: 17px;}.end{color:red;}.content{color:rgb(0, 255, 34) ;font-size: 18px;}");
           client.println(".panel{ color: white ; text-align: center; font-size: 15px;}.bg{background-color: black;}</style></head>");
           //CSS styling script ends

           client.println("<body class=\"bg\" ><h1 class=\"main\"> GA-ONE  CONTROL  INTERFACE </h1>");
           
           //login page display on loading
            if(login_z==0) // check for password using URL manipulation and algos
            {
              if(header.indexOf("GET /lp7")>=0&&login_pass=="Z") // 7
              login_pass="ZA";
              else if(header.indexOf("GET /lp4")>=0&&login_pass=="ZA") // 4
              login_pass="ZAB";
              else if(header.indexOf("GET /lp2")>=0&&login_pass=="ZAB") // 2
              login_pass="ZABC";
              else if(header.indexOf("GET /lp6")>=0&&login_pass=="ZABC") // 6
              login_pass="ZABCD";

              if(login_pass=="ZABCD") // password enterred correct
              {
                login_z=1;
                login_pass="Z";
                client.println(" <p class=\"end\">Designed and Developed by<br>TEAM GiriAs</p>");
                break;
              }
               //script for number pad in login page
              client.write("<p class=\"panel\">LOGIN</p>");
              client.write("<p class=\"pin\">ENTER PIN</p>");
              client.write("<div class=\"button4\">");
              client.write("<a href=\"/lp1\"><button>1</button></a>");
              client.write("<a href=\"/lp2\"><button>2</button></a>");
              client.write("<a href=\"/lp3\"><button>3</button></a>");
              client.write("</div><div class=\"button4\">");
              client.write("<a href=\"/lp4\"><button>4</button></a>");
              client.write("<a href=\"/lp5\"><button>5</button></a>");
              client.write("<a href=\"/lp6\"><button>6</button></a>");
              client.write("</div><div class=\"button4\">");
              client.write("<a href=\"/lp7\"><button>7</button></a>");
              client.write("<a href=\"/lp8\"><button>8</button></a>");
              client.write("<a href=\"/lp9\"><button>9</button></a>");
              client.write("</div><div class=\"button4\">");
              client.write("<a href=\"/lp*\"><button>*</button></a>");
              client.write("<a href=\"/lp0\"><button>0</button></a>");
              client.write("<a href=\"/lp#\"><button>#</button></a>");
              client.write("</div>");
            }
           else
           {
           //common body script begins after login
           client.println("<div class=\"button5\"><a href=\"/act\"><button>ACT</button></a>)");
           client.println("<a href=\"/sc\"><button>SC</button></a><a href=\"/ph1\"><button>PH-1</button></a>");
           client.println("<a href=\"/ph2\"><button>PH-2/3</button></a><a href=\"/lfb\"><button>PID</button></a><a href=\"/lg\"><button>LG</button></a></div>");
           //common body script ends

           //split up for each window based on URL 
           
           //Action window script starts - used for simple control of bot on arena
           if(header.indexOf("GET /act")>=0)
           {
            pat.write('z');
            if(header.indexOf("GET /act/1")>=0)
            {
              pat.write('1');
            }
            else if(header.indexOf("GET /act/2")>=0)
            {
              pat.write('2');
            }
            else if(header.indexOf("GET /act/3")>=0)
            {
              pat.write('3');
            }
            else if(header.indexOf("GET /act/4")>=0)
            {
              pat.write('4');
            }
            else if(header.indexOf("GET /act/0")>=0)
            {
              pat.write('0');
            }
            else if(header.indexOf("GET /act/s1")>=0)
            {
              pat.write('a');
            }
            else if(header.indexOf("GET /act/s2")>=0)
            {
              pat.write('b');
            }
            else if(header.indexOf("GET /act/s3")>=0)
            {
              pat.write('c');
            }
            else if(header.indexOf("GET /act/s4")>=0)
            {
              pat.write('d');
            }
            else if(header.indexOf("GET /act/s5")>=0)
            {
              pat.write('e');
            }
            client.println(" </div><p class=\"panel\">ACTION PANEL</p><div class=\"button4\">");
            client.println("<a href=\"/act/s1\"><button>1</button></a><a href=\"/act/s2\"><button>2</button></a><a href=\"/act/s3\"><button>3</button></a>");
            client.println("<a href=\"/act/s4\"><button>4</button></a><a href=\"/act/s5\"><button>5</button></a></div>");
            client.println("<p><a href=\"/act/1\"><button class=\"button\">FORWARD</button></a></p><div class=\"button3\"><a href=\"/act/4\"><button>LEFT</button></a> <a href=\"/act/2\"><button>RIGHT</button></a>");
            client.println("</div><p><a href=\"/act/3\"><button class=\"button\">REVERSE</button></a></p><p><a href=\"/act/0\"><button class=\"button\">BRAKE</button></a></p>");
           }
           //Action window script ends
           
           //Sensor Calibration window script begins - sends calibration request to Arduino and reads and displays values on webpage
           else if(header.indexOf("GET /sc")>=0)
           {
            pat.write('y');
            if(header.indexOf("GET /sc/sd1")>=0)
            {
              pat.write('1');
              delay(7000);
              for(int i=0;i<6;i++)
              sc_sensormax[i]=(pat.read()*5);
              for(int i=0;i<6;i++)
              sc_sensormin[i]=(pat.read()*5);
            }
            client.println("<p class=\"panel\">SENSOR CALIBRATION PANEL</p> ");
            client.println("<p><a href=\"/sc/sd1\"><button class=\"button\">CALIBRATE</button></a></p>");
            client.println("<p style=\"font-size: 15px;\" class=\"end\">SENSOR DATA</p>");
            client.println("<p class=\"content\">Sensor 0 :");
            client.println(int(sc_sensormin[0]));
            client.println(" ");
            client.println(int(sc_sensormax[0]));
            client.println("<br>Sensor 1 :");
            client.println(int(sc_sensormin[1]));
            client.println(" ");
            client.println(int(sc_sensormax[1]));
            client.println("<br>Sensor 2 :");
            client.println(int(sc_sensormin[2]));
            client.println(" ");
            client.println(int(sc_sensormax[2]));
            client.println("<br>Sensor 3 :");
            client.println(int(sc_sensormin[3]));
            client.println(" ");
            client.println(int(sc_sensormax[3]));
            client.println("<br>Sensor 4 :");
            client.println(int(sc_sensormin[4]));
            client.println(" ");
            client.println(int(sc_sensormax[4]));
            client.println("<br>Sensor 5 :");
            client.println(int(sc_sensormin[5]));
            client.println(" ");
            client.println(int(sc_sensormax[5]));
            client.println("</p>");
           }
           //Sensor calibration script ends

           //Phase 1 window Script begins - based on button clicked, the x and y coordinates are stored in NodeMCU and sent to Arduino upon request
           else if(header.indexOf("GET /ph1")>=0)
           {
            int data=0;
            if(header.indexOf("GET /ph1/x0")>=0)
            ph1_x=0;
            else if(header.indexOf("GET /ph1/x1")>=0)
            ph1_x=1;
            else if(header.indexOf("GET /ph1/x2")>=0)
            ph1_x=2;
            else if(header.indexOf("GET /ph1/x3")>=0)
            ph1_x=3;
            else if(header.indexOf("GET /ph1/x4")>=0)
            ph1_x=4;
            else if(header.indexOf("GET /ph1/y1")>=0)
            ph1_y=1;
            else if(header.indexOf("GET /ph1/y2")>=0)
            ph1_y=2;
            else if(header.indexOf("GET /ph1/y3")>=0)
            ph1_y=3;
            else if(header.indexOf("GET /ph1/y4")>=0)
            ph1_y=4;
            else if(header.indexOf("GET /ph1/y0")>=0)
            ph1_y=0;
            if(ph1_x!=-1&&ph1_y!=-1)
            {
              data=(ph1_x*10)+(ph1_y);
              pat.write(String(data));
              ph1_x=-1;
              ph1_y=-1;
            }
            client.println("<p class=\"panel\">PHASE - I</p>");
            client.println("<p class=\"content\">X COORDINATE : ");
            client.println(String(ph1_x));
            client.println("</p>");
            client.println("<div class=\"button4\">");
            client.println("<a href=\"/ph1/x0\"><button>0</button></a>");
            client.println("<a href=\"/ph1/x1\"><button>1</button></a>");
            client.println("<a href=\"/ph1/x2\"><button>2</button></a>");
            client.println("<a href=\"/ph1/x3\"><button>3</button></a>");
            client.println("<a href=\"/ph1/x4\"><button>4</button></a>");
            client.println("</div><p class=\"content\">Y COORDINATE : ");
            client.println(String(ph1_y));
            client.println("</p>");
            client.println("<div class=\"button4\">");
            client.println("<a href=\"/ph1/y0\"><button>0</button></a>");
            client.println("<a href=\"/ph1/y1\"><button>1</button></a>");
            client.println("<a href=\"/ph1/y2\"><button>2</button></a>");
            client.println("<a href=\"/ph1/y3\"><button>3</button></a>");
            client.println("<a href=\"/ph1/y4\"><button>4</button></a>");
            client.println("</div>");
           }
           //phase 1 window script ends

           //Phase 2 and 3 window script begins - coordinates received as opened URL through Following - IP python program
           // as communication process is same, same window is used for both Phase 2 and Phase 3
           else if(header.indexOf("GET /ph2")>=0)
           {
            int data=0;
            pat.write('w');
            if(header.indexOf("GET /ph2/00")>=0)
            {ph23_x=0;ph23_y=0;}
            else if(header.indexOf("GET /ph2/01")>=0)
            {ph23_x=0;ph23_y=1;}
            else if(header.indexOf("GET /ph2/02")>=0)
            {ph23_x=0;ph23_y=2;}
            else if(header.indexOf("GET /ph2/03")>=0)
            {ph23_x=0;ph23_y=3;}
            else if(header.indexOf("GET /ph2/04")>=0)
            {ph23_x=0;ph23_y=4;}
            else if(header.indexOf("GET /ph2/10")>=0)
            {ph23_x=1;ph23_y=0;}
            else if(header.indexOf("GET /ph2/11")>=0)
            {ph23_x=1;ph23_y=1;}
            else if(header.indexOf("GET /ph2/12")>=0)
            {ph23_x=1;ph23_y=2;}
            else if(header.indexOf("GET /ph2/13")>=0)
            {ph23_x=1;ph23_y=3;}
            else if(header.indexOf("GET /ph2/14")>=0)
            {ph23_x=1;ph23_y=4;}
            else if(header.indexOf("GET /ph2/20")>=0)
            {ph23_x=2;ph23_y=0;}
            else if(header.indexOf("GET /ph2/21")>=0)
            {ph23_x=2;ph23_y=1;}
            else if(header.indexOf("GET /ph2/22")>=0)
            {ph23_x=2;ph23_y=2;}
            else if(header.indexOf("GET /ph2/23")>=0)
            {ph23_x=2;ph23_y=3;}
            else if(header.indexOf("GET /ph2/24")>=0)
            {ph23_x=2;ph23_y=4;}
            else if(header.indexOf("GET /ph2/30")>=0)
            {ph23_x=3;ph23_y=0;}
            else if(header.indexOf("GET /ph2/31")>=0)
            {ph23_x=3;ph23_y=1;}
            else if(header.indexOf("GET /ph2/32")>=0)
            {ph23_x=3;ph23_y=2;}
            else if(header.indexOf("GET /ph2/33")>=0)
            {ph23_x=3;ph23_y=3;}
            else if(header.indexOf("GET /ph2/34")>=0)
            {ph23_x=3;ph23_y=4;}
            else if(header.indexOf("GET /ph2/40")>=0)
            {ph23_x=4;ph23_y=0;}
            else if(header.indexOf("GET /ph2/41")>=0)
            {ph23_x=4;ph23_y=1;}
            else if(header.indexOf("GET /ph2/42")>=0)
            {ph23_x=4;ph23_y=2;}
            else if(header.indexOf("GET /ph2/43")>=0)
            {ph23_x=4;ph23_y=3;}
            else if(header.indexOf("GET /ph2/44")>=0)
            {ph23_x=4;ph23_y=4;}
            client.println("<p class=\"panel\">Phase-II/III</p>");
            client.println("<p class=\"content\">X Coordinate :");
            client.println(String(ph23_x));
            client.println("</p>");
            client.println("<p class=\"content\">Y Coordinate :");
            client.println(String(ph23_y));
            client.println("</p>");
            if(ph23_x!=-1&&ph_23_y!=-1)
            {
              data=(ph23_x*10)+ph23_y;
              pat.write(String(data));
              ph23_x=-1;
              ph23_y=-1;
            }
           }
           //phase 2 window script ends

           // logout button clicked
           else if(header.indexOf("GET /lg")>=0)
           {
            login_z=0;
            client.println(" <p class=\"end\">Designed and Developed by<br>TEAM GiriAs</p>");
            break;
           }
           // log out window ends

           //PID line follower window script begins
           else if(header.indexOf("GET /lfb")>=0)
           {  
            if(header.indexOf("GET /lfb/in")>=0)
            pat.write('3');
            else if(header.indexOf("GET /lfb/st")>=0)
            pat.write('2');
              client.println("<p class=\"panel\">PID INTERFACE</p>");
              client.println("<p><a href=\"/lfb/in\"><button class=\"button\">I N I T I A T E</button></a></p>");
              client.println("<p><a href=\"/lfb/st\"><button class=\"button\">T E R M I N A T E</button></a></p>");
           }
          }
           //PID line follower window script ends
           
           //split window scripts end

           client.println(" <p class=\"end\">Designed and Developed by<br>TEAM GiriAs</p>    </body></html>");
           client.println();
           //user interface scripts end
           
           break;
          }
          else currentLine="";
        }
        else if(c!='\r') currentLine+=c;
      }
    }
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

// END OF CODE
