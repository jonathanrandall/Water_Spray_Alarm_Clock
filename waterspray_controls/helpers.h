#ifndef HELPERS_H
#define HELPERS_H

//#include <cmath>
#include <TouchScreen.h> //touch library
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
//#include <Adafruit_GFX.h>
//#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define MAGENTA      0xF81F  /* 255,   0, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x785F  /* 128,   0, 128 */ // 0x780F
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xBB20  /* 255, 165,   0 */ //0xFD20
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF80D  /* 255,   0, 255 */

#define LED_PINr   42
#define LED_PINl   43
#define LED_COUNT 1

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin


//touch sensitivity for X
#define TS_MINX 178
#define TS_MAXX 916

//touch sensitivity for Y
#define TS_MINY 143
#define TS_MAXY 913

// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65

//touch sensitivity for press
#define MINPRESSURE 10
#define MAXPRESSURE 1000

bool s1 = false; //time to start
bool s2 = false; //num activations
bool s3 = false; //intervals

uint32_t r_colour;
uint32_t l_colour;

bool set_to_return(){
  s1 = false;
  s2 = false;
  s3 = false;
  return true;
}

void show_numbers_input_screen();
//void show_home_screen1();
//void show_home_screen2();
void show_colour_menu();
void show_timer_settings_screen();
void squirt();
void show_home_screen();

Adafruit_NeoPixel stripl(LED_COUNT, LED_PINl, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripr(LED_COUNT, LED_PINr, NEO_GRB + NEO_KHZ800);

int buzzer = 26;

bool light_on = true;
bool buzzer_on = false;
uint16_t brightness = 210;

char buffer1[28];
char buffer2[28];

//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_KBV my_lcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV my_lcd(240,320,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset
uint16_t n=0;

const int numplaces = 6;

uint8_t timer_inputs[numplaces] = {0,0,0,0,0,0};

typedef struct _defaults_ {
  unsigned long time_to_start = 45; //seconds
  unsigned long num_activations = 4;
  unsigned long intervals = 3; //minuts
} defaults_;

unsigned long time_to_start = 45;
unsigned long num_activations = 4;
unsigned long intervals = 3; //minuts

void set_defaults(){
  time_to_start = 45;
  num_activations = 4;
  intervals = 3; //minuts
}

void insert_into_timer(uint8_t num){
  for(int i =numplaces-1 ; i>0; i--){
    timer_inputs[i] = timer_inputs[i-1];
  }
  timer_inputs[0] = num;
}

void delet_lsb_timer(){
  for(int i = 0; i<numplaces-1; i++){
    timer_inputs[i] = timer_inputs[i+1];
  }
  timer_inputs[numplaces-1]=0;
}

void reset_timer_inputs(){
  for(int i=0; i<numplaces;i++){
    timer_inputs[i]=0;
  }
}

unsigned long get_num_from_timer_inputs(){
  double gtts=0;
  for(int i =0; i<numplaces; i++){
    gtts+=((double) timer_inputs[i])*((double) pow(10,i));
    
  }
  return (unsigned long) round(gtts+0.2);
}

bool is_screen_on = true;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


bool on_home_screen = false;
//bool on_settings_screen = false;
bool on_colour_change_screen = false;
bool on_timer_settings_screen = false;
bool on_numbers_input_screen = false;
bool on_blank_screen = false;

unsigned long turn_off_screen;
unsigned long turn_off_screen_t = 120000; //turn off screen after 15 seconds of no buttons.

unsigned long next_spray;


bool set_to_screen(){

  on_home_screen = false;
  on_colour_change_screen = false;
  on_timer_settings_screen = false;
  on_numbers_input_screen = false;
  on_blank_screen = false;
  turn_off_screen = millis(); //reset counter when we change screens
  return true;
}

typedef struct _button_info
{
     uint8_t button_function[17];
     uint16_t button_colour; //can also used to input other informations
     uint16_t led_colour;
     uint16_t button_x1;
     uint16_t button_y1;
     uint16_t button_x2;
     uint16_t button_y2;
     uint8_t button_do;          
 }button_info;

typedef struct _button_info_round
{
     uint8_t button_name[10];
     uint8_t button_name_size;
     uint16_t button_name_colour;
     uint16_t button_colour;
     uint16_t button_x;
     uint16_t button_y;     
 }button_info_round;
 

//the definition of buttons


//display string
//void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
//{
void show_string(String str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
//  my_lcd.setFont();
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_String(str,x,y);
}

//Check whether to press or not
boolean is_pressed(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t px,int16_t py)
{
    if((px > x1 && px < x2) && (py > y1 && py < y2))
    {
        turn_off_screen = millis(); //reset counter when we change screens
        return true;  
    } 
    else
    {
        return false;  
    }
 }

void show_current_screen(){
  if(on_home_screen){
      show_home_screen();
    }

   if(on_numbers_input_screen){
      show_numbers_input_screen();
    }
    if(on_colour_change_screen){
      show_colour_menu();
    }
    if(on_timer_settings_screen){
      show_timer_settings_screen();
    }
  is_screen_on = true;
  turn_off_screen = millis();
}

void turn_light_off(){
  stripl.clear();
  stripr.clear();
  stripl.show();
  stripr.show();
}

void turn_light_on(){
  stripl.fill(stripl.gamma32(stripl.ColorHSV(l_colour)));//strip.gamma32(strip.ColorHSV(16000)));
   stripr.fill(stripr.gamma32(stripr.ColorHSV(r_colour)));//strip.gamma32(strip.ColorHSV(16000)));
   stripl.show();
  stripr.show();
}

#endif
