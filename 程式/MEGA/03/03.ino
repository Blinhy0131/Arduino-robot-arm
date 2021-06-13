#include "PS2X_lib.h"
#include <Servo.h>
 
PS2X ps2x;

Servo bottom_Spin;
Servo bottom_Rotate;
Servo sec_Rotate;
Servo sec_Spin;
Servo arm_Spin;
Servo arm_Rotate;
Servo jaw_Contral;
Servo jaw_Rotate;

 int error=0;
 byte type=0;
 byte vibrate=0;
 
void setup() {
  
  bottom_Spin.attach(9);  //大臂旋轉
  bottom_Rotate.attach(8);//大臂自轉
  sec_Rotate.attach(7);   //二臂旋轉
  sec_Spin.attach(6);     //二臂自轉
  arm_Spin.attach(5);     //手腕自轉
  arm_Rotate.attach(4);   //手腕旋轉
  jaw_Rotate.attach(3);   //夾爪自轉
  jaw_Contral.attach(2);  //夾爪控制

  
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);

 

 Serial.begin(9600);
  // 控制器接腳設置並驗證是否有錯誤:  GamePad(時脈腳位, 命令腳位, 選取腳位, 資料腳位, 是否支援類比按鍵, 是否支援震動) 
  error = ps2x.config_gamepad(13,11,10,12, true, true);
 
 if(error == 0) { // 如果控制器連接沒有問題，就顯示底下的訊息。
   digitalWrite(22,HIGH);
 }
   
  else if(error == 1){ // 找不到控制器，顯示底下的錯誤訊息。
   digitalWrite(23,HIGH);
  }
  else if(error == 2)  {// 發現控制器，但不接受命令，請參閱程式作者網站的除錯說明。
   digitalWrite(24,HIGH);
  }
  else if(error == 3){ // 控制器拒絕進入類比感測壓力模式，或許是此控制器不支援的緣故。
   digitalWrite(25,HIGH);;
  }
    type = ps2x.readType();
  switch(type)
  {
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

int jawr=90; //馬達角度
int jawc=90;
int armr=90;
int arms=90;
int secs=90;
int secr=90;
int botr=90;
int bots=90;

int ss=analogRead(PSS_RX); //搖桿角度設定
int sr=analogRead(PSS_RY);
int bs=analogRead(PSS_LX);
int br=analogRead(PSS_LY);


int set_nember=1; //自動重複次數

int jawr_set[]={1,2,3,4,5,6};  //自動重複設定值
int jawc_set[]={1,2,3,4,5,6};
int armr_set[]={1,2,3,4,5,6};
int arms_set[]={1,2,3,4,5,6};
int secs_set[]={1,2,3,4,5,6};
int secr_set[]={1,2,3,4,5,6};
int botr_set[]={1,2,3,4,5,6};
int bots_set[]={1,2,3,4,5,6};


void loop() { 
    if(error == 1) // 如果沒發現任何控制器，則跳出迴圈。
  return;
  
    ps2x.read_gamepad(false, 0);

  if(ps2x.Button(PSB_START)){          // 系統歸零 *角度代設定*
      bottom_Spin.write(90);
      bottom_Rotate.write(90);
      sec_Rotate.write(90);
      sec_Spin.write(90);
      arm_Spin.write(90);
      arm_Rotate.write(90);
      jaw_Rotate.write(90);
      jaw_Contral.write(90);

      jawc=90;
      jawr=90;
      armr=90;
      arms=90;
      secs=90;
      secr=90;
      botr=90;
      bots=90;

      set_nember=1; //連續作動歸零
    }

   secs=map(ss, 0, 255,0,180); //二臂旋轉(香菇頭
   sec_Spin.write(secs);
   secr=map(sr, 0, 255,0,180); //二臂自轉(香菇頭
   sec_Rotate.write(secr);

   bots=map(bs, 0, 255,0,180); //大臂旋轉(香菇頭
   bottom_Spin.write(bots);
   botr=map(br, 0, 255,0,180); //大臂自轉(香菇頭
   bottom_Rotate.write(botr);

   
   if(ps2x.Button(PSB_R2)){ //夾爪合，方向待確認(按鍵
      if(jawc<180){
        jawc=jawc+1;
        jaw_Contral.write(jawc);
      }
   }
   if(ps2x.Button(PSB_L2)){ //夾爪開，方向待確認(按鍵
      if(jawc>0){
        jawc=jawc-1;
        jaw_Contral.write(jawc);
      }
   }
   if(ps2x.Button(PSB_PAD_LEFT)){ //手腕旋轉，方向待確認(按鍵
      if(arms>0){
        arms=arms-5;
        arm_Spin.write(arms);
      }
   }
    if(ps2x.Button(PSB_PAD_RIGHT)){ 
       if(arms<180){
          arms=arms+5;
         arm_Spin.write(arms);
      }
   }
   if(ps2x.Button(PSB_PAD_UP)){ //手腕上下擺動，方向待確認(按鍵
       if(armr<180){
          armr=armr+5;
         arm_Rotate.write(armr);
      }
   }
   if(ps2x.Button(PSB_PAD_DOWN)){ 
       if(armr>0){
          armr=armr-5;
         arm_Rotate.write(armr);
      }
   }
   if(ps2x.Button(PSB_R1)){  //手腕轉動，方向待確認(按鍵
    if(jawr<180){
      jawr=jawr+5;
      jaw_Rotate.write(jawr);
    }
   }
   if(ps2x.Button(PSB_L1)){
    if(jawr>0){
      jawr=jawr-5;
      jaw_Rotate.write(jawr);
    }
   }

   if(ps2x.Button(PSB_SELECT)){        //連續做動設定
      if (set_nember<=6){
         jawr_set[set_nember]=jawr;
         jawc_set[set_nember]=jawc;
         armr_set[set_nember]=armr;
         arms_set[set_nember]=arms;
         secs_set[set_nember]=secs;
         secr_set[set_nember]=secr;
         bots_set[set_nember]=bots;
         botr_set[set_nember]=botr;
         set_nember++;
    }else{
     for(int setting_error=1;setting_error<=3;setting_error++){ //if 連續做動動作設定超過6次
        digitalWrite(22,HIGH);
        digitalWrite(23,HIGH);
        digitalWrite(24,HIGH);
        digitalWrite(25,HIGH);
        delay(500);
        digitalWrite(22,LOW);
        digitalWrite(23,LOW);
        digitalWrite(24,LOW);
        digitalWrite(25,LOW);
        delay(500);
        }
      }
   }
   if(ps2x.ButtonPressed(PSB_GREEN)){                               //連續做動
    for(int repeat_time=1;repeat_time<=10;repeat_time++)
      for(int repeat_move=1;repeat_move<=set_nember;repeat_move++){
        bottom_Spin.write(bots_set[repeat_move]);
        bottom_Rotate.write(botr_set[repeat_move]);
        sec_Rotate.write(secr_set[repeat_move]);
        sec_Spin.write(secs_set[repeat_move]);
        arm_Spin.write(arms_set[repeat_move]);
        arm_Rotate.write(armr_set[repeat_move]);
        jaw_Rotate.write(jawr_set[repeat_move]);
        jaw_Contral.write(jawc_set[repeat_move]);
        delay(1000);
     }
   }
   
}
