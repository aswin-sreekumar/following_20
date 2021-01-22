# Program for Following'20
# Developed by TEAM GiriAs
#Program for Image processing- calibration for circle and semicircle. This program is intended as a precautionary measure.
#The purpose of the program is for calibration. An issue arises when one deals with curved shapes.
#The contour approximation function approximates a shape to a number of finite line segments. So when we are dealing with curved shapes, the approximation depends
#size of the shape. Therefore, we decided to include this program to avoid errors when dealing with the circle and semicircle. Here, the values printed should be
#used in the shape detection program( for circle and semicircle). We have made an assumption that all images will have same-sized circles and semicircles. Of
#course, the values might vary for the x and the y coordinates. Therefore use this program to determine the corresponding values. 

import cv2

cap= cv2.VideoCapture(0)

while True:
    ret, frame= cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    _,thresh= cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    
    cv2.imshow('thresh',thresh)
    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    frame = cv2.drawContours(frame, contours, -1, (0,255,0), 2)
    #press c for capturing the shapes
    if cv2.waitKey(5) & 0xFF== ord('c'):
        cnt_out1= contours[1]
        cnt_out2=contours[2]
        cnt_in= contours[3]
        break
approx_out1 = cv2.approxPolyDP(cnt_out1, 0.01*cv2.arcLength(cnt_out, True), True)
approx_in = cv2.approxPolyDP(cnt_in, 0.01*cv2.arcLength(cnt_in, True), True)
approx_out2=cv2.approxPolyDP(cnt_out2, 0.01*cv2.arcLength(cnt_in, True), True)

 # Note down the values of a and b and use them for circle and semicircle in the final code.
a= len(approx_out1)
b= len(approx_in)
c=len(approx_out2)
print( 'outer contour 1:\t')
print(a)
print('inner contour:\t')
print(b)
print( 'outer contour 1:\t')
print(c)

cap.release()
cv2.destroyAllWindows()