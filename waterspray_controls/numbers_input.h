#ifndef NUMBERS_INPUT_H
#define NUMBERS_INPUT_H

#include "helpers.h"

uint8_t cntr=0;

/******************* UI details */
#define BUTTON_R 25 //the radius of button 
#define BUTTON_SPACING_X 25 //the horizontal distance between button
#define BUTTON_SPACING_Y 5  //the vertical distance between button
#define EDG_Y 5 //lower edge distance 
#define EDG_X 20 //left and right distance

uint16_t text_x=10,text_y=6,text_x_add = 6*3,text_y_add = 8*3;
//uint16_t n=0;

void reset_numbers_input(){
  text_x=10;text_y=6;text_x_add = 6*3;text_y_add = 8*3;n=0;
}

button_info numbers_button[14] = 
{
  "1",CYAN,BLACK,1,my_lcd.Get_Display_Height()*1/6,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*2/6,21,
  "2",YELLOW,BLACK,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*1/6,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*2/6,21,
  "3",MAGENTA,BLACK,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*1/6,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*2/6,21,
  "4",PURPLE,BLACK,1,my_lcd.Get_Display_Height()*2/6,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*3/6,21,
  "5",MAROON,BLACK,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*2/6,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*3/6,21,
  "6",GREEN,BLACK,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*2/6,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*3/6,21,
  "7",OLIVE,BLACK,1,my_lcd.Get_Display_Height()*3/6,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*4/6,21,
  "8",PINK,BLACK,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*3/6,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*4/6,21,
  "9",NAVY,BLACK,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*3/6,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*4/6,21,
  "0",GREENYELLOW,BLACK,1,my_lcd.Get_Display_Height()*4/6,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*5/6,21,
  "dele",DARKGREY,BLACK,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*4/6,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*5/6,22,
  "Dflt",YELLOW,BLACK,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*4/6,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*5/6,23,
  "Cancel",OLIVE,BLACK,1,my_lcd.Get_Display_Height()*5/6,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height(),24,
  "Save",DARKCYAN,BLACK,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*5/6,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height(),25,
};

void show_numbers_input_screen()
{
  turn_off_screen = millis();
  on_numbers_input_screen = set_to_screen();
  my_lcd.Fill_Screen(BLUE);
  cntr=0;
  n=0;
  reset_timer_inputs();
    uint16_t i;
   for(i = 0;i < sizeof(numbers_button)/sizeof(numbers_button[0]);i++)
   {
      my_lcd.Set_Draw_color(numbers_button[i].button_colour);
      my_lcd.Fill_Rectangle(numbers_button[i].button_x1,numbers_button[i].button_y1,numbers_button[i].button_x2,numbers_button[i].button_y2);
      show_string(numbers_button[i].button_function,numbers_button[i].button_x1+5,numbers_button[i].button_y1+15,3,numbers_button[i].led_colour,numbers_button[i].button_colour,1);
//      my_lcd.Fill_Circle(numbers_button[i].button_x, numbers_button[i].button_y, BUTTON_R);
//      show_string(numbers_button[i].button_name,numbers_button[i].button_x-strlen(numbers_button[i].button_name)*numbers_button[i].button_name_size*6/2+1,numbers_button[i].button_y-numbers_button[i].button_name_size*8/2+1,numbers_button[i].button_name_size,numbers_button[i].button_name_colour,BLACK,1);
   }
   my_lcd.Set_Draw_color(BLACK);
   my_lcd.Fill_Rectangle(1, 1, my_lcd.Get_Display_Width()-2, 3);
   my_lcd.Fill_Rectangle(1, my_lcd.Get_Display_Height()*1/6-2, my_lcd.Get_Display_Width()-2, 31);
   my_lcd.Fill_Rectangle(1, 1, 3, my_lcd.Get_Display_Height()*1/6);
   my_lcd.Fill_Rectangle(my_lcd.Get_Display_Width()-4, 1, my_lcd.Get_Display_Width()-2, my_lcd.Get_Display_Height()*1/6);
}

void numbers_input_buttons(TSPoint p){
      for(int i=0;i<sizeof(numbers_button)/sizeof(button_info);i++)
    {
         //press the button
         if(is_pressed(numbers_button[i].button_x1,numbers_button[i].button_y1,numbers_button[i].button_x2,numbers_button[i].button_y2,p.x,p.y))
         {
          switch(numbers_button[i].button_do){
          case 21:
           if(cntr<6){
            
            insert_into_timer(atoi(numbers_button[i].button_function));
            my_lcd.Set_Draw_color(DARKGREY);
            my_lcd.Fill_Circle((numbers_button[i].button_x1+numbers_button[i].button_x2)/2, (numbers_button[i].button_y1+numbers_button[i].button_y2)/2, BUTTON_R);
            delay(100);
            my_lcd.Set_Draw_color(numbers_button[i].button_colour);
            my_lcd.Fill_Circle((numbers_button[i].button_x1+numbers_button[i].button_x2)/2, (numbers_button[i].button_y1+numbers_button[i].button_y2)/2, BUTTON_R);
            show_string(numbers_button[i].button_function,text_x,text_y,3,GREENYELLOW, BLACK,1);
            text_x += text_x_add-1;
            n++;
            cntr++;
           }
            break;
          case 22:
            //delete
            if(n > 0)
              {
                  my_lcd.Set_Draw_color(BLUE);
                  text_x -= (text_x_add-1);  
                  my_lcd.Fill_Rectangle(text_x, text_y, text_x+text_x_add-1, text_y+text_y_add-2);
                  n--; cntr--;
              }
              delet_lsb_timer();
              delay(100);
              //reset_timer_inputs();
            break;
          case 23:
            //default
            reset_timer_inputs();
            set_defaults();
            my_lcd.Set_Draw_color(BLUE);
            while(n>0)
              {
                my_lcd.Set_Draw_color(BLUE);
                  text_x -= (text_x_add-1);  
                  my_lcd.Fill_Rectangle(text_x, text_y, text_x+text_x_add-1, text_y+text_y_add-2);
                  n--;
              }
            cntr = 0;
            show_string("45",text_x,text_y,3,GREENYELLOW, BLACK,1);
            text_x += text_x_add-1; text_x += text_x_add-1;
            n++;n++;
            cntr++;cntr++;
            delay(100);
            break;
          case 24:
            //cancel
            show_timer_settings_screen();
            break;
          case 25:
            //save
            if(s1){
              time_to_start = get_num_from_timer_inputs();
            }
            if(s2){
              num_activations = get_num_from_timer_inputs();
            }
            if(s3){
              intervals = get_num_from_timer_inputs();
            }
            reset_numbers_input();
            show_timer_settings_screen();
            break;
          default:
            break;
          }

     } //for  
  }
}

#endif
