#include "PS2X_lib.h"
#include <Servo.h>

PS2X ps2;
Servo bottomSpin;
Servo bottomRotate;
Servo secRotate;
Servo secSpin;
Servo armSpin;
Servo armRotate;
Servo jawcon;

 int error=0;
 byte type=0;
 byte vibrate=0;

void setup() {
  
  bottomSpin.attach(1);
  bottomRotate.attach(2);
  secRotate.attach(3);
  secSpin.attach(4);
  armSpin.attach(5);
  armRotate.attach(6);
  jawcon.attach(7);


 

 Serial.begin(57600);
   
  error = ps2.config_gamepad(13,11,10,12, true, true);
 
 if(error == 0) { 
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1) 
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)  
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3) 
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   type = ps2.readType();  
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");  
       break;
       case 1:
        Serial.println("DualShock Controller Found");  
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");  
       break;
     }

}

void loop() {
  if(error == 1) 
  return;

}
