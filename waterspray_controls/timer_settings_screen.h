#ifndef TIMER_SETTINGS_SCREEN_H
#define TIMER_SETTINGS_SCREEN_H

#include "helpers.h"


button_info set_timers_buttons[8] = 
{
  "Timer",CYAN,BLACK,1,1,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*1/5,31,
  "Defaults",PURPLE,BLACK,my_lcd.Get_Display_Width()*1/2,1,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*1/5,32,
  "Activations",YELLOW,BLACK,1,my_lcd.Get_Display_Height()*1/5,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*2/5,33,
  "Interval (mins)",GREEN,BLACK,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*1/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*2/5,34,
  "Home",PURPLE,BLACK,1,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*3/5,35,
  "Colour",ORANGE,BLACK,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*3/5,12,
  "Next",LIGHTGREY,BLACK,1,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*4/5,36,
  "Info",DARKGREY,BLACK,1,my_lcd.Get_Display_Height()*4/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height(),37,
};

void show_timer_settings_screen()
{
  turn_off_screen = millis();
  on_timer_settings_screen = set_to_screen();
   char buffer1[28];
   char buffer2[28];
    uint16_t i;
   for(i = 0;i < sizeof(set_timers_buttons)/sizeof(set_timers_buttons[0]);i++)
   {
      my_lcd.Set_Draw_color(set_timers_buttons[i].button_colour);
      my_lcd.Fill_Rectangle(set_timers_buttons[i].button_x1,set_timers_buttons[i].button_y1,set_timers_buttons[i].button_x2,set_timers_buttons[i].button_y2);
      if(i<6){
      show_string(set_timers_buttons[i].button_function,set_timers_buttons[i].button_x1+3,set_timers_buttons[i].button_y1+15,3,set_timers_buttons[i].led_colour,set_timers_buttons[i].button_colour,1);
      }
      if(i==6){
        sprintf(buffer1, "Next:%lds",(unsigned long)(time_to_start));
        show_string(buffer1,set_timers_buttons[i].button_x1+5,set_timers_buttons[i].button_y1+15,3,set_timers_buttons[i].led_colour,set_timers_buttons[i].button_colour,1);
      }
      if(i==7){
        sprintf(buffer2, "Info:%ldX %ldmin", num_activations, intervals);
        show_string(buffer2,set_timers_buttons[i].button_x1+1,set_timers_buttons[i].button_y1+15,3,set_timers_buttons[i].led_colour,set_timers_buttons[i].button_colour,1);
      }
      
//      my_lcd.Fill_Circle(phone_button[i].button_x, phone_button[i].button_y, BUTTON_R);
//      show_string(phone_button[i].button_name,phone_button[i].button_x-strlen(phone_button[i].button_name)*phone_button[i].button_name_size*6/2+1,phone_button[i].button_y-phone_button[i].button_name_size*8/2+1,phone_button[i].button_name_size,phone_button[i].button_name_colour,BLACK,1);
   }
}

void timer_settings_buttons(TSPoint p){
  for(int i=0;i<sizeof(set_timers_buttons)/sizeof(button_info);i++)
    {
         //press the button
         if(is_pressed(set_timers_buttons[i].button_x1,set_timers_buttons[i].button_y1,set_timers_buttons[i].button_x2,set_timers_buttons[i].button_y2,p.x,p.y))
         {
          switch(set_timers_buttons[i].button_do){
            case 31://set timer
              s1 = set_to_return();
              show_numbers_input_screen();
            break;
            
            case 32: //defaults
              set_defaults();
             show_timer_settings_screen();
            break;
            
            case 12: //colour
             show_colour_menu();
            break;
            
            case 33: //activations
              s2 = set_to_return();
              show_numbers_input_screen();
            break;
            
            case 34://interval
              s3 = set_to_return();
              show_numbers_input_screen();
            break;

            case 35://back
              show_home_screen();
            break;
            
            case 36: //Next
             
            break;
            
            case 37: //Info
              
            break;
            
          default:
            break;
          }

     } //if  
  }
}


#endif
