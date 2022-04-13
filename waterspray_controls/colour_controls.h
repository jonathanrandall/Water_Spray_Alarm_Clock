#ifndef COLOUR_CONTORLS_H
#define COLOUR_CONTORLS_H

#include "helpers.h"
//code for the light stuff

#define white 255
#define red 22672
#define orange 15661
#define yellow 14746
#define green 1638
#define blue 45875
#define cyan 38502
#define pink 27034
#define purple 31949

bool change_right = true;


void init_light(){
   stripl.begin();
   stripl.setBrightness(brightness);
   stripr.begin();
   stripr.setBrightness(brightness);
   stripl.fill(stripl.gamma32(stripl.ColorHSV(pink)));//strip.gamma32(strip.ColorHSV(16000)));
   stripr.fill(stripr.gamma32(stripr.ColorHSV(blue)));//strip.gamma32(strip.ColorHSV(16000)));
   r_colour = blue;
   l_colour = pink;
//   strip.setPixelColor(1,strip.gamma32(strip.ColorHSV(pink)));
//   strip.show();
}




button_info light_set_button[12] = 
{
  "white",GREEN,green,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*4/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height(),0,
  "c_change",RED,red,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*4/5,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height(),0,
  "c_change",ORANGE,orange,1,my_lcd.Get_Display_Height()*4/5,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height(),0,
  "c_change",YELLOW,yellow,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*4/5,0,
  "c_change",PURPLE,purple,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*4/5,0,
  "c_change",BLUE,blue,1,my_lcd.Get_Display_Height()*3/5,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*4/5,0,
  "c_change",CYAN,cyan,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*3/5,0,
  "c_change",WHITE,white,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width()*2/3,my_lcd.Get_Display_Height()*3/5,1,
  "c_change",PINK,pink,1,my_lcd.Get_Display_Height()*2/5,my_lcd.Get_Display_Width()*1/3,my_lcd.Get_Display_Height()*3/5,0,
  
  "Dim", DARKGREY, white,1,my_lcd.Get_Display_Height()*1/5,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*2/5,2,
  "bright",LIGHTGREY, white,my_lcd.Get_Display_Width()*1/2,my_lcd.Get_Display_Height()*1/5,my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*2/5,3,
  "Done",NAVY, white, 1, 1, my_lcd.Get_Display_Width(),my_lcd.Get_Display_Height()*1/5,4,
};

void select_colour(TSPoint p){
      for(int i=0;i<sizeof(light_set_button)/sizeof(button_info);i++)
    {
         //press the button
         if(is_pressed(light_set_button[i].button_x1,light_set_button[i].button_y1,light_set_button[i].button_x2,light_set_button[i].button_y2,p.x,p.y))
         {
          switch(light_set_button[i].button_do){
          case 0:
            if(change_right){
            stripr.fill(stripr.gamma32(stripr.ColorHSV(light_set_button[i].led_colour)));
            r_colour = light_set_button[i].led_colour;
            stripr.show();
          } else {
            stripl.fill(stripl.gamma32(stripl.ColorHSV(light_set_button[i].led_colour)));
            l_colour = light_set_button[i].led_colour;
            stripl.show();
          }
            break;
          case 1:
          if(change_right){
            stripr.fill(stripr.Color(255,255,255));
            stripr.show();
          } else {
            stripl.fill(stripl.Color(255,255,255));
            stripl.show();
          }
            break;
          case 2:
            //if(brightness >32) brightness -=21; else brightness = 1;
            change_right = false;
            stripl.setBrightness(brightness);
            stripl.show();
            break;
          case 3:
            // if(brightness <224) brightness +=20; else brightness = 255;
            change_right = true;
            stripr.setBrightness(brightness);
            stripr.show();
            break;
          case 4:
            show_home_screen();
            break;
          }
     } //for  
  }
}

//display the main menu
void show_colour_menu()
{
    uint16_t i;
    on_colour_change_screen = set_to_screen();
    if(change_right){
      light_set_button[9].button_colour=DARKGREY;
      light_set_button[10].button_colour=GREEN;
    } else {
      light_set_button[9].button_colour=GREEN;
      light_set_button[10].button_colour=LIGHTGREY;
    }
   for(i = 0;i < sizeof(light_set_button)/sizeof(button_info);i++)
   {
      my_lcd.Set_Draw_color(light_set_button[i].button_colour);
      my_lcd.Fill_Rectangle(light_set_button[i].button_x1,light_set_button[i].button_y1,light_set_button[i].button_x2,light_set_button[i].button_y2);
    }
   for(i = 0;i < sizeof(light_set_button)/sizeof(button_info);i++)
      switch(light_set_button[i].button_do){

        case 2: //dim
          show_string("L",light_set_button[i].button_x1+40,light_set_button[i].button_y1+16,4,BLACK,light_set_button[i].button_colour,1);
          break;
        case 3: //bright
          show_string("R",light_set_button[i].button_x1+40,light_set_button[i].button_y1+16,4,BLACK,light_set_button[i].button_colour,1);
          break;
        case 4:
          show_string(light_set_button[i].button_function,light_set_button[i].button_x1+60,light_set_button[i].button_y1+17,4,BLACK,BLACK,1);
          break;
        default:
          break;
      }
}

#endif
