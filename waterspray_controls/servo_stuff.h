#ifndef SERVO_STUFF_H
#define SERVO_STUFF_H

#include "helpers.h"
#include <Servo.h> 


long int servo1_t;
long int servo2_t;

int servopinr = 46;
int servopinl = 45;


Servo servo_right; // servo object representing the MG 996R servo
Servo servo_left; // servo object representing the MG 996R servo
int posr = 170;
int posl = 10;
void init_serov() {
  
  servo_right.attach(servopinr); // servo is wired to Arduino on digital pin 3
  servo_right.write(posr);
  servo_left.attach(servopinl); // servo is wired to Arduino on digital pin 3
  servo_left.write(posl);
}

void buzz_buzzer(){
  if(buzzer_on){
    tone(buzzer, 3000);
  }
}

void quiet_buzzer(){
  noTone(buzzer);
}

void squirt() {
  buzz_buzzer();
  //turn_light_off();
  pinMode(XM, OUTPUT);  // Pins configures again for TFT control
  pinMode(YP, OUTPUT);
//  my_lcd.Fill_Screen(BLACK); 
  for(int i =1; i<22   ; i++){
  servo_left.write(posl+i*8); // move MG996R's shaft to angle 90°
  delay(25); // wait for one second
  servo_right.write(posr-i*8); 
  delay(25);
  }

  quiet_buzzer();
  delay(900);
  servo_left.write(posl); 
  servo_right.write(posr);
}

#endif
