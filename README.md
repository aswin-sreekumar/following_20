# following_20
Repo for Following'20, annual flagship event conducted by RMI-NITT. Involves designing and developing a line follower bot combined with algorithms to perform a series of tasks involving multiple domains of robotics like Image processing, Embedded systems, Electronics and Communication.

## GA-one bot by *TEAM GiriAs*

- [*Girish. K*](https://github.com/girish-2001)
- [*Aswin Sreekumar*](https://github.com/aswin-sreekumar)

## About the project
### Chassis
- 5mm transparent acrylic sheet used to build the chassis.
- Designed based on minimal component spacing.
- 2W drive bot based on differential steering supported by a castor wheel.

### Master controller
- Arduino UNO used as master microcontroller.
- Outputs of IR sensor array fed into ADC port of UNO.
- Implemented PD control using the Pololu's library for line follower.
- SoftwareSerial library used to communicate with NodeMCU through GPIO pins.
- Automatic calibration and position feedback using Pololu's library.
 
### 6-pin IR sensor array
- Self fabricated 6-pin IR sensor array for position feedback.
- Uses TCRT5000 IR emiiter-phototransistor pair biased using appropriate resistor network.
- Outputs analog signal proportional to amount of reflected IR waves received and is converted to digital using ADC of the Arduino UNO.
- Biasing voltage obtained from +5V output of Arduino considering the low current requirements of the same.
  
### NodeMCU as communication gateway
   - Consists of NodeMCU code for communication gateway between controller and Arduino using LAN (WiFi).
   - NodeMCU configured as Server and sends the webpages scripts to client upon request.
   - Protected using server-side set password.

### Webpages
   - Webpages scripted in HTML+CSS for communication interface between controller and bot.
   - NodeMCU acts as server.
   - The webpages are integrated into the NodeMCU code as strings for access upon client request using local IP address.
   - Unique URL manupilation algorithm for data communication between client and server (NodeMCU).

### Image Processing
   - Python scripts for image processing according to problem statement and communicating with LAN.
   - Uses contouring and approxPolyDP() to detect shapes and open corresponding webpage URL, thereby indirectly communicating the deciphered coordinates to the UNO through NodeMCU. 
   
#### Mode of communication with bot : WiFi through LAN

## Contents of repository
1. Arduino
    - Sensor calibration code
    - Line follower mode code
    - Phase 1 code for coordinate navigation
    - Phase 2 outline algorithm
    - Phase 2 code for coordinate navigation using IP coordinates

2. NodeMCU
    - Main program for server side scripting of webpage and serial communication

3. Webpages
    - Login page
    - Sensor calibration page
    - Phase 1 and Phase 2 page

4. Image processing
    - Shape calibration script
    - Main code for coordinates decoding using shape detection and communication using URL manipulation. 

5. Bot images

## Gallery
### Chassis
![chassis](https://user-images.githubusercontent.com/63254914/118474260-81409400-b728-11eb-9b8b-2b3224040e17.png)

### IR sensor array
![IR_sensors](https://user-images.githubusercontent.com/63254914/118474270-86054800-b728-11eb-811c-19457ad77e05.jpg)

### Bot images
![final_bot_1](https://user-images.githubusercontent.com/63254914/118474288-8a316580-b728-11eb-995f-98dda4e6f262.png)
![final_bot_2](https://user-images.githubusercontent.com/63254914/118474299-8bfb2900-b728-11eb-8fb4-d1b7a2a395e3.png)
![final_bot_3](https://user-images.githubusercontent.com/63254914/118474309-8e5d8300-b728-11eb-80b6-6e186668bf76.png)

### Mobile login webpage
![mobile_webpage](https://user-images.githubusercontent.com/63254914/118474325-91587380-b728-11eb-85b9-80e29162f715.jpg)
![webpage_login](https://user-images.githubusercontent.com/63254914/118474337-95849100-b728-11eb-9632-abc8c7cd28ec.png)

### Calibration webpage
![sensor_calib_webpage](https://user-images.githubusercontent.com/63254914/118474381-a03f2600-b728-11eb-9e18-d2927b9ef1d0.png)

### Phase 1 webpage
![webpage_phase1](https://user-images.githubusercontent.com/63254914/118474397-a503da00-b728-11eb-86f1-4101ada16c84.png)

### Line follower video
https://user-images.githubusercontent.com/63254914/118473475-a7196900-b727-11eb-8c75-08cda1952363.mp4
