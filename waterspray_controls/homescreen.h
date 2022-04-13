#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "helpers.h"
//this is the home screen.

//Squirt  button
//info button including countdown

//next screen button

//next screen has settings, light on/off, buzzer on/off, colour settings.

button_info home_screen_button[5] = 
{
  "squirt",RED,white,1,1,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*2/5,6,
  "next_squirt",PURPLE,white,1,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*3/5,7,
  "light",YELLOW,orange,1,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*4/5,8,
  "buzzer",DARKGREY,orange,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*4/5,13,
  "Settings",CYAN,purple,1,my_lcd.Get_Display_Height()*4/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height(),11,
};


void show_home_screen()
{
  turn_off_screen = millis();
  on_home_screen = set_to_screen();
  
   for(uint16_t i = 0;i < sizeof(home_screen_button)/sizeof(button_info);i++)
   {
      my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
      my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);
      switch(home_screen_button[i].button_do){
        case 6: //squirt
          show_string("Squirt",home_screen_button[i].button_x1+5,home_screen_button[i].button_y1+28,6,BLUE,home_screen_button[i].button_colour,1);
          
          break;
        case 7: //Input
          sprintf(buffer1, "Next: %lds",(unsigned long)(time_to_start));
          show_string(buffer1,home_screen_button[i].button_x1+1,home_screen_button[i].button_y1+1,3,BLACK,home_screen_button[i].button_colour,1);
          sprintf(buffer2, "Info: %ldX %ldmin", num_activations, intervals);
          show_string(buffer2,home_screen_button[i].button_x1+1,home_screen_button[i].button_y1+32,3,BLACK,home_screen_button[i].button_colour,1);
          break;
        case 8:
          if(!light_on) {
//              stripl.setBrightness(10);
//              stripr.setBrightness(10);
              home_screen_button[i].button_colour = LIGHTGREY;
             }
             else { 
              stripl.setBrightness(brightness);
              stripr.setBrightness(brightness);
              home_screen_button[i].button_colour = YELLOW;
             }
          stripl.show();
          stripr.show();
          my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
          my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);
          show_string("Light",home_screen_button[i].button_x1+5,home_screen_button[i].button_y1+5,3,RED,home_screen_button[i].button_colour,1);
          show_string(light_on?"ON":"OFF",home_screen_button[i].button_x1+40,home_screen_button[i].button_y1+40,2,RED,home_screen_button[i].button_colour,1);
          break;
        case 13:
          if(buzzer_on){
                home_screen_button[i].button_colour = GREEN;
              } else {
                home_screen_button[i].button_colour = DARKGREY;
              }
           my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
           my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);
           show_string("Buzzer",home_screen_button[i].button_x1+5,home_screen_button[i].button_y1+5,3,RED,home_screen_button[i].button_colour,1);
           show_string(buzzer_on?"ON":"OFF",home_screen_button[i].button_x1+40,home_screen_button[i].button_y1+40,2,RED,home_screen_button[i].button_colour,1);
          break;
        case 11:
          show_string("Settings",home_screen_button[i].button_x1+10,home_screen_button[i].button_y1+16,4,GREEN,home_screen_button[i].button_colour,1);
          break;
        default:
          break;
      }
      
  }
   
}


void home_buttons(TSPoint p){
      for(int i=0;i<sizeof(home_screen_button)/sizeof(button_info);i++)
    {
         //press the button
         if(is_pressed(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2,p.x,p.y))
         {
          switch(home_screen_button[i].button_do){
            case 6:
             squirt();  
             show_current_screen();         
            break;
            case 8:
             light_on = !light_on;
             if(!light_on) {
              turn_light_off();
              home_screen_button[i].button_colour = LIGHTGREY;
             }
             else { 
              turn_light_on();
              home_screen_button[i].button_colour = YELLOW;
             }
             my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
             my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);
             show_string("Light",home_screen_button[i].button_x1+5,home_screen_button[i].button_y1+5,3,RED,home_screen_button[i].button_colour,1);
             show_string(light_on?"ON":"OFF",home_screen_button[i].button_x1+40,home_screen_button[i].button_y1+40,2,RED,home_screen_button[i].button_colour,1);
             
             delay(100);          
            break;
            
            case 11://timer
              show_timer_settings_screen();
            break;
            
            
            case 13: //buzzer
              //turn_on_buzzer();
              buzzer_on = !buzzer_on;
              if(buzzer_on){
                home_screen_button[i].button_colour = GREEN;
                
              } else {
                home_screen_button[i].button_colour = DARKGREY;
                
              }
           my_lcd.Set_Draw_color(home_screen_button[i].button_colour);
           my_lcd.Fill_Rectangle(home_screen_button[i].button_x1,home_screen_button[i].button_y1,home_screen_button[i].button_x2,home_screen_button[i].button_y2);
           show_string("Buzzer",home_screen_button[i].button_x1+5,home_screen_button[i].button_y1+3,3,RED,home_screen_button[i].button_colour,1);
           show_string(buzzer_on?"ON":"OFF",home_screen_button[i].button_x1+40,home_screen_button[i].button_y1+36,2,RED,home_screen_button[i].button_colour,1);
           break;
          default:
            break;
          }

     } //for  
  }
}



#endif
