#include "PS2X_lib.h"

 
PS2X ps2x;


 int error=0;
 byte type=0;
 byte vibrate=0;
 
void setup() {
  
 

 Serial.begin(9600);
  // 控制器接腳設置並驗證是否有錯誤:  GamePad(時脈腳位, 命令腳位, 選取腳位, 資料腳位, 是否支援類比按鍵, 是否支援震動) 
  error = ps2x.config_gamepad(13,11,10,12, true, true);
 
 if(error == 0) { // 如果控制器連接沒有問題，就顯示底下的訊息。
   Serial.print("0");
 }
   
  else if(error == 1){ // 找不到控制器，顯示底下的錯誤訊息。
   Serial.print("1");
  }
  else if(error == 2)  {// 發現控制器，但不接受命令，請參閱程式作者網站的除錯說明。
   Serial.print("2");
  }
  else if(error == 3){ // 控制器拒絕進入類比感測壓力模式，或許是此控制器不支援的緣故。
   Serial.print("3");
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


void loop() { 
    if(error == 1) // 如果沒發現任何控制器，則跳出迴圈。
  return;
  
    ps2x.read_gamepad(false, 0);

  if(ps2x.Button(PSB_START)){          // 系統歸零 *角度代設定*
      Serial.print("START");
  }

   
   if(ps2x.Button(PSB_R2)){ //夾爪合，方向待確認(按鍵
      Serial.print("R2");
      }
   
   if(ps2x.Button(PSB_L2)){ //夾爪開，方向待確認(按鍵
      Serial.print("L2");
      }
   
   if(ps2x.Button(PSB_PAD_LEFT)){ //手腕旋轉，方向待確認(按鍵
     Serial.print("left");
      }
   
    if(ps2x.Button(PSB_PAD_RIGHT)){ 
       Serial.print("right");
      }
   
   if(ps2x.Button(PSB_PAD_UP)){ //手腕上下擺動，方向待確認(按鍵
       Serial.print("up");
      }
   
   if(ps2x.Button(PSB_PAD_DOWN)){ 
       Serial.print("down");
      }
   
   if(ps2x.Button(PSB_R1)){  //手腕轉動，方向待確認(按鍵
    Serial.print("r1");
    }
   
   if(ps2x.Button(PSB_L1)){
    Serial.print("l1");
    }
   

   if(ps2x.Button(PSB_SELECT)){        //連續做動設定
      Serial.print("SELECT");
   }
   if(ps2x.ButtonPressed(PSB_GREEN)){                               //連續做動
    Serial.print("GREEN");
   }
   
}
