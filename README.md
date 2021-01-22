# following_20
Repo for Following'20, annual flagship event, conducted by RMI-NITT

## GA-one bot by *TEAM GiriAs*

- *Girish. K @girish-2001*
- *Aswin Sreekumar @aswin-sreekumar*

The repo consists of

### Arduino codes for the Arduino UNO used
  a. Phase 1
  b. Phase 2
  c. Sensor calibration
        Arduino code to calibrate the fabricated IR sensor array. 
  d. Line follower code
        Bot follows black line of width >3 cm over white/reflective surface.
    
### NodeMCU codes
   Consists of NodeMCU code for communication gateway between controller and Arduino using LAN (WiFi).
   NodeMCU configured as Server and sends the webpages scripts to client upon request.
   Protected using server-side set password.

### Webpages
   Webpages scripted in HTML+CSS for communication interface between controller and bot.
   NodeMCU acts as server.
   The webpages are integrated into the NodeMCU code as strings.

### Image Processing
   Python scripts for image processing according to problem statement and communicating with LAN
   Contains final script and a shape calibration script.

### Bot images
   Major images of self-fabricated sensors, chassis, final version of the bot and the webpages designed.

### Line follower video
   GA-one Line follower video [link](https://drive.google.com/file/d/158Cxl4eY8iHhrx6XS4xw1NNQDg3edp1A/view?usp=sharing/).
   
#### Mode of communication with bot : WiFi through LAN
