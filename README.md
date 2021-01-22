# following_20
Repo for Following'20, annual flagship event, conducted by RMI-NITT

GA-one bot by TEAM GiriAs

Girish. K
Aswin Sreekumar

The repo consists of

1. Arduino codes for the Arduino UNO used
a. Phase 1
b. Phase 2
c. Sensor calibration
        Arduino code to calibrate the fabricated IR sensor array. 
d. Line follower code
        Bot follows black line of width >3 cm over white/reflective surface.
    
2. NodeMCU codes
        Consists of NodeMCU code for communication gateway between controller and Arduino using LAN (WiFi).
        NodeMCU configured as Server and sends the webpages scripts to client upon request.
        Protected using server-side set password.

3. Webpages
        Webpages scripted in HTML+CSS for communication interface between controller and bot.
        NodeMCU acts as server.
        The webpages are integrated into the NodeMCU code as strings script.
        
4. Bot images
        Major images of self-fabricated sensors

5. Line follower video



Mode of communication with bot : WiFi through LAN
