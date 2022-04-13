
#include "colour_controls.h"
#include "homescreen.h"
#include "numbers_input.h"
#include "servo_stuff.h"
#include "timer_settings_screen.h"


                            
void setup(void) 
{
  Serial.begin(9600);
   my_lcd.Init_LCD();
   init_serov();
   init_light(); 
   turn_light_on();
   pinMode(buzzer, OUTPUT);
//   Serial.println(my_lcd.Read_ID(), HEX);

   my_lcd.Fill_Screen(GREENYELLOW); 
   show_home_screen();
//   init_light();
   turn_off_screen = millis();
   next_spray = millis();
   if(light_on){
     stripl.show();
     stripr.show();
   }
}

//uint16_t text_x=10,text_y=6,text_x_add = 6*light_set_button[0].button_name_size,text_y_add = 8*light_set_button[0].button_name_size;
int update_home_screen(){

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  uint16_t i = 1;
  my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
  my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);

  sprintf(buffer1, "Next: %lds",(unsigned long)(time_to_start));
  show_string(buffer1,home_screen_button[1].button_x1+1,home_screen_button[1].button_y1+1,3,BLACK,home_screen_button[1].button_colour,1);

  sprintf(buffer2, "Info: %ldX %ldmin", num_activations, intervals);
  show_string(buffer2,home_screen_button[1].button_x1+1,home_screen_button[1].button_y1+32,3,BLACK,home_screen_button[1].button_colour,1);

  return 1;
}

int waitOneTouch() {
  //when screen is off
  // Get a touch in the required button area (or anywhere if flag set)
  my_lcd.Fill_Screen(BLACK); 
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);  // Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while (p.z < MINPRESSURE || p.z > MAXPRESSURE );
  
  // All done, return the touch coordinates object
  if(on_home_screen){
      show_home_screen();
      p.x = 0; p.y = 0;
    }

   if(on_numbers_input_screen){
      show_numbers_input_screen();
      p.x = 0; p.y = 0;
    }
    if(on_colour_change_screen){
      show_colour_menu();
      p.x = 0; p.y = 0;
    }
    if(on_timer_settings_screen){
      show_timer_settings_screen();
      p.x = 0; p.y = 0;
    }
  is_screen_on = true;
  turn_off_screen = millis();
  return 1;
  
}

void loop(void)
{

  uint16_t i;
  TSPoint p = ts.getPoint();
  if((millis() >= turn_off_screen + turn_off_screen_t)&&!on_blank_screen){
    on_blank_screen = true;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    my_lcd.Fill_Screen(BLACK); 
    turn_off_screen = millis();
  }
  if((millis() >= next_spray + 5000) && num_activations > 0 ){
    
    if(time_to_start>5) time_to_start -= 5;
    else time_to_start = 0;
    
    next_spray = millis();
    
    if(time_to_start <= 0){
      
      squirt();
      delay(1300);
      squirt();
      delay(1300);
      squirt();
      delay(1300);
      squirt();
      time_to_start = intervals*60; //seconds
      num_activations--;
      next_spray = millis();
      if(!on_blank_screen) show_current_screen();
    }
    
    if(on_home_screen && !on_blank_screen) update_home_screen();
    
  }
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (is_screen_on)
  {
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  //if button pressed
  {
    turn_off_screen = millis();
    is_screen_on = true;
     //reset counter from last button press
    //p.x = my_lcd.Get_Display_Width()-map(p.x, TS_MINX, TS_MAXX, my_lcd.Get_Display_Width(), 0);
    //p.y = my_lcd.Get_Display_Height()-map(p.y, TS_MINY, TS_MAXY, my_lcd.Get_Display_Height(), 0);
//    Serial.println(p.x);
//    Serial.println(p.y);
    //print statements to find max and min. Touch edges
//    Serial.print("before mapping: p.x = "); Serial.print(p.x); Serial.print(", p.y = "); Serial.println(p.y);
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, my_lcd.Get_Display_Width());
    
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, my_lcd.Get_Display_Height());
//    Serial.print("after mapping: p.x = "); Serial.print(p.x); Serial.print(", p.y = "); Serial.println(p.y);
//    p.y = map(p.y, TS_MINY, TS_MAXY, my_lcd.Get_Display_Height(),0);
    if(on_blank_screen){ //exit screensaver
      show_current_screen();
      on_blank_screen = false;
      p.x = 0; p.y = 0;
    }
    
    if(on_home_screen){
      home_buttons(p);
      p.x = 0; p.y = 0;
    }

   if(on_numbers_input_screen){
      numbers_input_buttons(p);
      p.x = 0; p.y = 0;
    }
    if(on_colour_change_screen){
      select_colour(p);
      p.x = 0; p.y = 0;
    }
    if(on_timer_settings_screen){
      timer_settings_buttons(p);
      p.x = 0; p.y = 0;
    }
      }//if p.x
  }//if is screen on
 
  else{
    waitOneTouch();
  }
}
