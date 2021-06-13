#include "PS2X_lib.h"
#include <Servo.h>

PS2X ps2x;
Servo bottomSpin;
Servo bottomRotate;
Servo secRotate;
Servo secSpin;
Servo armSpin;
Servo armRotate;
Servo jawcon;
Servo jawrot;

 int error=0;
 byte type=0;
 byte vibrate=0;

void setup() {
  
  bottomSpin.attach(9);
  bottomRotate.attach(8);
  secRotate.attach(7);
  secSpin.attach(6);
  armSpin.attach(5);
  armRotate.attach(4);
  jawcon.attach(3);
  jawrot.attach(2);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);

 

 Serial.begin(57600);
  // 控制器接腳設置並驗證是否有錯誤:  GamePad(時脈腳位, 命令腳位, 選取腳位, 資料腳位, 是否支援類比按鍵, 是否支援震動) 
  error = ps2x.config_gamepad(13,11,10,12, true, true);
 
 if(error == 0) { // 如果控制器連接沒有問題，就顯示底下的訊息。
   digitalWrite(22,HIGH);
 }
   
  else if(error == 1){ // 找不到控制器，顯示底下的錯誤訊息。
   digitalWrite(23,HIGH);
  }
  else if(error == 2)  // 發現控制器，但不接受命令，請參閱程式作者網站的除錯說明。
   digitalWrite(24,HIGH);
   
  else if(error == 3){ // 控制器拒絕進入類比感測壓力模式，或許是此控制器不支援的緣故。
   digitalWrite(25,LOW);;
  }
}

int jawr=90;
int jawc=90;
int armr=90;
int arms=90;
int secs=90;
int secr=90;
int botr=90;
int bots=90;
int ss=analogRead(PSS_RX);
int sr=analogRead(PSS_RY);
int bs=analogRead(PSS_LX);
int br=analogRead(PSS_LY);


void loop() {
  if(error == 1) // 如果沒發現任何控制器，則跳出迴圈。
  return;

  if(ps2x.Button(PSB_START)){          // 查看「開始」鍵是否被按住,系統歸零
      bottomSpin.write(90);
      bottomRotate.write(90);
      secRotate.write(90);
      secSpin.write(90);
      armSpin.write(90);
      armRotate.write(90);
      jawcon.write(90);
      jawrot.write(90);

      jawc=90;
      jawr=90;
      armr=90;
      arms=90;
      secs=90;
      secr=90;
      botr=90;
      bots=90;
    }

   if(ps2x.Button(PSB_R2)){ //夾爪合，待確認
      if(jawc<180){
        jawc=jawc+5;
        jawcon.write(jawc);
      }
   }
   if(ps2x.Button(PSB_L2)){ //夾爪開，待確認
      if(jawc>0){
        jawc=jawc-5;
        jawcon.write(jawc);
      }
   }
   if(ps2x.Button(PSB_PAD_LEFT)){ //手腕旋轉
      if(arms>0){
        arms=arms-5;
        armSpin.write(arms);
      }
   }
    if(ps2x.Button(PSB_PAD_RIGHT)){ 
       if(arms<180){
          arms=arms+5;
         armSpin.write(arms);
      }
   }
   if(ps2x.Button(PSB_PAD_UP)){ //手腕上下擺動
       if(armr<180){
          armr=armr+5;
         armRotate.write(armr);
      }
   }
   if(ps2x.Button(PSB_PAD_DOWN)){ 
       if(armr>0){
          armr=armr-5;
         armRotate.write(armr);
      }
   }
   if(ps2x.Button(PSB_R1)){
    if(jawr<180){
      jawr=jawr+5;
      jawrot.write(jawr);
    }
   }
   if(ps2x.Button(PSB_L1)){
    if(jawr>0){
      jawr=jawr-5;
      jawrot.write(jawr);
    }
   }




   
   secs=map(ss, 0, 255,0,180);
   secSpin.write(secs);
   secr=map(sr, 0, 255,0,180);
   secRotate.write(secr);

   bots=map(bs, 0, 255,0,180);
   bottomSpin.write(bots);
   botr=map(br, 0, 255,0,180);
   bottomRotate.write(botr);
}
