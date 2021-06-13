
#include <Servo.h>
 


Servo bottom_Spin;
Servo bottom_Rotate;
Servo sec_Rotate;
Servo sec_Spin;
Servo arm_Spin;
Servo arm_Rotate;
Servo jaw_Contral;
Servo jaw_Rotate;

 
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

}

int jawr=90; //馬達角度
int jawc=90;
int armr=90;
int arms=90;
int secs=90;
int secr=90;
int botr=90;
int bots=90;


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
  bottom_Spin.write(0);
  bottom_Rotate.write(0);
  sec_Rotate.write(0);
  sec_Spin.write(0);
  arm_Spin.write(0);
  arm_Rotate.write(0);
  jaw_Rotate.write(0);
  jaw_Contral.write(0);
  delay (1000);
  bottom_Spin.write(180);
  bottom_Rotate.write(180);
  sec_Rotate.write(180);
  sec_Spin.write(180);
  arm_Spin.write(180);
  arm_Rotate.write(180);
  jaw_Rotate.write(180);
  jaw_Contral.write(180);
  delay (1000); 
    
}
