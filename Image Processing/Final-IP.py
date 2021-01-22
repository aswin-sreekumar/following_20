#following'20 IP - Processing image to decode coordinates and open corresponding URL in browser of client.
#developed by TEAM GiriAs [Girish.K && Aswin Sreekumar]
#created for participation in FOLLOWING'20 hosted by RMI-NITT

#program used to detect the shapes in A4 paper and decode the target coordinates
#the processed coordinates are sent to bot by opening corresponding URL in browser. 
#Ensure this device is connected to the LAN of bot

#In case coordinates dont match, run calibration code to calibrate threshold values for semi-circle and circle

#importing required packages
import cv2
import array
import webbrowser

#Empty function
def nothing(x):
    pass

cap=cv2.VideoCapture(0,cv2.CAP_DSHOW) #Object for Video feedback from webcam

cv2.namedWindow("PARAMETER") #window for setting region of interest
cv2.createTrackbar("LIMIT","PARAMETER",0,255,nothing)
cv2.createTrackbar("AREA","PARAMETER",0,2000,nothing)

#Display video from webcam as frames and wait for capture
while(1): #infinite loop for video processing as frames
    if(cv2.waitKey(1)&0xFF==ord('c')): #hit 'c' for capturing the frame and exiting the loop
        break
    _,img0=cap.read() #reading frame
    img1=cv2.cvtColor(img0,cv2.COLOR_BGR2GRAY) #convert frame to grayscale
    t=cv2.getTrackbarPos("LIMIT","PARAMETER") #get trackbar values of PARAMETER
    ret,img2=cv2.threshold(img1,t,255,cv2.THRESH_BINARY_INV) # use PARAMETER-limit value for thresholding frame
    cv2.imshow("THRESH",img2) #display thresholded frame
    cv2.imshow("GRAYSCALE",img1) #display original frame in grayscale
    contours,hierarchy=cv2.findContours(img2,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE) #finding contours in thresholded frame
    for cnt in contours: # looping through contours
        area=cv2.contourArea(cnt) #consider contours only greater than limit area value
        ar=cv2.getTrackbarPos("AREA","PARAMETER")
        if(area>=ar):  #display contour only if area greater than limit set
            cv2.drawContours(img0,cnt,-1,(0,255,0),2) #display contours
    cv2.imshow("IP_FEED",img0) #raw video feed with filtered contours

arr=array.array('i') #initialising array for coordinate manipulation

#Processing captured frame
for cnt in contours: #looping through contours of captured frame
    area=cv2.contourArea(cnt) #consider contours only greater than limit area value
    ar=cv2.getTrackbarPos("AREA","PARAMETER")
    if(area>=ar):
        approx=cv2.approxPolyDP(cnt,0.04*cv2.arcLength(cnt,True),True) #calculate number of sides
        if(len(approx)==3): #triangle detected
           arr.append(2)
        elif(len(approx)==8): #circle detected
           arr.append(0)
        elif(len(approx)==4): #quadrilateral detected
            (x,y,w,h)=cv2.boundingRect(approx)
            ar=w/float(h)
            if(ar>=0.75 and ar<=1.25):
                arr.append(3) #square detected
            else:
                arr.append(4) #rectangle detected
        else:
            arr.append(1) #semi-circle detected

cap.release() #release video stream
cv2.waitKey(0) #wait for key stroke
cv2.destroyAllWindows() #close all windows

#Processing coordinates and determining which is x and y Coordinates
#Logic:
#       The inner shape is filled and will have only one contour.
#       The outer shape will have 2 contours.
#So, whichever coordinate repeats itself in the array is x-coordinate.
#Directly process variables x and y, if non-matching duplicate exists as third element, swap x and y

x=arr[0]
y=arr[1]

if(arr[0]==arr[1] and arr[1]==arr[-1]): #x=y
    pass
elif(x==y and arr[-1]!=x): #third element is y-coordinate
    y=arr[-1]
elif(arr[-1]==y): #swap x and y
    a=x
    x=y
    y=a
elif(arr[-1]==x): # x and y already matched
    pass

print("X coordinate :",x) #display x-coordinate
print("Y coordinate :",y) #display y-coordinate


#sending data to bot and device after confirmation
print("SEND DATA ?")
ch=input() # user checks coordinates and confirms

cv2.waitKey(0) #wait for key stroke
cv2.destroyAllWindows() #close all windows

if(ch=='y'): #coordinates are correct, so open corresponding URL in browser in LAN
    if(x==0 and y==0): # (0,0)
     webbrowser.open("http://192.168.43.15/ph2/00",new=0)
    elif(x==0 and y==1): # (0,1)
     webbrowser.open("http://192.168.43.15/ph2/01",new=0)
    elif(x==0 and y==2): # (0,2)
     webbrowser.open("http://192.168.43.15/ph2/02",new=0)
    elif(x==0 and y==3): # (0,3)
     webbrowser.open("http://192.168.43.15/ph2/03",new=0)
    elif(x==0 and y==4): # (0,4)
     webbrowser.open("http://192.168.43.15/ph2/04",new=0)
    elif(x==1 and y==0): # (1,0)
     webbrowser.open("http://192.168.43.15/ph2/10",new=0)
    elif(x==1 and y==1): # (1,1)
     webbrowser.open("http://192.168.43.15/ph2/11",new=0)
    elif(x==1 and y==2): # (1,2)
     webbrowser.open("http://192.168.43.15/ph2/12",new=0)
    elif(x==1 and y==3): # (1,3)
     webbrowser.open("http://192.168.43.15/ph2/13",new=0)
    elif(x==1 and y==4): # (1,4)
     webbrowser.open("http://192.168.43.15/ph2/14",new=0)
    elif(x==2 and y==0): # (2,0)
     webbrowser.open("http://192.168.43.15/ph2/20",new=0)
    elif(x==2 and y==1): # (2,1)
     webbrowser.open("http://192.168.43.15/ph2/21",new=0)
    elif(x==2 and y==2): # (2,2)
     webbrowser.open("http://192.168.43.15/ph2/22",new=0)
    elif(x==2 and y==3): # (2,3)
     webbrowser.open("http://192.168.43.15/ph2/23",new=0)
    elif(x==2 and y==4): # (2,4)
     webbrowser.open("http://192.168.43.15/ph2/24",new=0)
    elif(x==3 and y==0): # (3,0)
     webbrowser.open("http://192.168.43.15/ph2/30",new=0)
    elif(x==3 and y==1): # (3,1)
     webbrowser.open("http://192.168.43.15/ph2/31",new=0)
    elif(x==3 and y==2): # (3,2)
     webbrowser.open("http://192.168.43.15/ph2/32",new=0)
    elif(x==3 and y==3): # (3,3)
     webbrowser.open("http://192.168.43.15/ph2/33",new=0)
    elif(x==3 and y==4): # (3,4)
     webbrowser.open("http://192.168.43.15/ph2/34",new=0)
    elif(x==4 and y==0): # (4,0)
     webbrowser.open("http://192.168.43.15/ph2/40",new=0)
    elif(x==4 and y==1): # (4,1)
     webbrowser.open("http://192.168.43.15/ph2/41",new=0)
    elif(x==4 and y==2): # (4,2)
     webbrowser.open("http://192.168.43.15/ph2/42",new=0)
    elif(x==4 and y==3): # (4,3)
     webbrowser.open("http://192.168.43.15/ph2/43",new=0)
    elif(x==4 and y==4): # (4,4)
     webbrowser.open("http://192.168.43.15/ph2/44",new=0)
    print("COORDINATES SENT")
else:
    print("COMMAND FAILURE")

# END of program
