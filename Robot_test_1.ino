#include <PS2X_lib.h>
#include <Servo.h>

Servo lr;
Servo ud;
Servo rot;
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

PS2X ps2x;
int error = 0;
int type = 0;
byte vibrate = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  lr.attach(9);
  ud.attach(8);
  rot.attach(7);
  error = ps2x.config_gamepad(13,11,10,12, true, true);
  if(error ==0){
    Serial.println("Found Controller");
  }
  else if(error == 1){
    Serial.println("No controller found");
  }
  else if(error == 2){
    Serial.println("Controller found but not accepting comands");
  }
  else if(error == 3){
    Serial.println("Controller refusing to enter pressures mode");
  }
  type = ps2x.readType(); 
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
  ps2x.read_gamepad();
  // put your main code here, to run repeatedly:
  if(error == 1){
    return;
  }
  if(ps2x.Analog(PSS_LY) > 150){
    pos2 -= 2;
    if(pos2 > 180){
      pos2 = 180;
    }
  }
  if(ps2x.Analog(PSS_LY) < 100){
    pos2 += 2;
    if(pos2 < 0){
      pos2 = 0;
    }
  }
  if(ps2x.Analog(PSS_LX) > 160){
    pos1 += 2;
    if(pos1 > 180){
      pos1 = 180;
    }
  }
  if(ps2x.Analog(PSS_LX) < 110){
    pos1 -= 2;
    if(pos1 < 0){
      pos1 = 0;
    }
  }
  if(ps2x.Analog(PSS_RX) > 130){
    pos3 += 2;
    if(pos3 > 180){
      pos3 = 180;
    }
  }
  if(ps2x.Analog(PSS_RX) < 100){
    pos3 -= 2;
    if(pos3 < 0){
      pos3 = 0;
    }
  }
  //Serial.println(ps2x.Analog(PSS_LY));
  //Serial.print(", ");
  Serial.println(ps2x.Analog(PSS_LX));
  //Serial.print(", ");
  //Serial.println(ps2x.Analog(PSS_RY));
  ud.write(pos2);
  lr.write(pos1);
  rot.write(pos3);
  delay(5);
}
