/*********************************************************************
This sketch uses example for Adafruit Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

// Button Pin Setup
const int l_up_button = 2; //Left player up button pin
const int l_down_button = 9; //Left player down button pin
const int r_up_button = 3; //Right player up button pin
const int r_down_button = 5; //Right player down button pin


//Screen Size Parameters
int x_pixels = 128;
int y_pixels = 32;

//Paddle Parameters
int paddle_height = 10;
int paddle_width = 3;

int speakerPin = 8;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Ball velocities:
int x_vel = 1;
int y_vel = 1;

// Ball position:
int x_pos = 5;
int y_pos = 32;

// Paddle positions:
int l_pos = 0;
int r_pos = 0;

// Player scores
int l_score = 0;
int r_score = 0;


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {

  pinMode(l_up_button, INPUT);
  pinMode(l_down_button, INPUT);
  pinMode(r_up_button, INPUT);
  pinMode(r_down_button, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  // Clear the buffer.
  display.clearDisplay();
  // Display Arduino Pong splashscreen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(display.width()/2-20,0);
  display.println("Ardunio");
  display.setCursor(display.width()/2-20/2,8);
  display.println("Pong");
  display.display();
  delay(2000);


}

void loop() {

  // Update position of left paddle:
  if (digitalRead(l_up_button) && l_pos < (y_pixels - paddle_height)){l_pos += 1;}
  else if (digitalRead(l_down_button) && l_pos > 0){l_pos -= 1;}
  
  // Update position of right paddle:
  if (digitalRead(r_up_button) && r_pos < (y_pixels - paddle_height)){r_pos += 1;}
  else if (digitalRead(r_down_button) && r_pos > 0){r_pos -= 1;}

  // Check for ball hitting a wall:
  
  if (x_pos > x_pixels-1){
    ball_reset(false);
    l_score += 1;
    tone(speakerPin, 50, 100);
    delay(50);
    tone(speakerPin, 50, 100);
    }  
  
  else if(x_pos < 0){
    ball_reset(true);
    r_score +=1;
    tone(speakerPin, 50, 100);
    delay(50);
    tone(speakerPin, 50, 100);
    }

  // Check for ball bouncing off ceiling:
    
  if (y_pos > y_pixels-1 || y_pos < 0){y_vel = -y_vel;}

  // Check for ball bouncing off paddle:

  // Update ball position:
  x_pos+=x_vel;
  y_pos+=y_vel;

  // Draw pong elements to display:
  display.clearDisplay();
  display.drawPixel(x_pos, y_pos, WHITE);
  display.fillRect(0, l_pos, paddle_width, paddle_height, WHITE);
  display.fillRect(x_pixels-paddle_width ,r_pos, paddle_width, paddle_height, WHITE);

  // Display scores
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(display.width()/4,0);
  display.println(l_score);
  display.setCursor(display.width()*3/4,0);
  display.println(r_score);

  // Display all elements
  display.display();

   // Check for ball bouncing off paddles:
  if (ball_on_right_paddle()){
    x_vel = -x_vel;
    tone(speakerPin, 300, 100);
  }
  else if (ball_on_left_paddle()){
    x_vel = -x_vel;
    tone(speakerPin, 250, 100);
  }
}

bool ball_on_right_paddle(){
// If ball is heading towards paddle and is at the surface of paddle between the top and bottom of the paddle, then it's a hit
return(x_pos == x_pixels-paddle_width-1 && y_pos >= r_pos && y_pos <= (r_pos + paddle_height) && x_vel == 1);
}

bool ball_on_left_paddle(){
return(x_pos == paddle_width-1 && y_pos >= l_pos && y_pos <= (l_pos + paddle_height) && x_vel == -1);
}

void ball_reset(bool left){
//If left is true, then ball should launch from the left, otherwise launch from the right
//Ball should launch at a random Y location and at a random Y velocity

  y_pos = random(display.height());
  if (random(2)>0){
    y_vel = 1;
  }
  else{
    y_vel = -1;
  }

  if (left){
  x_vel = 1;
  x_pos = paddle_width-1;
  }
  
  else{
  x_vel = -1;
  x_pos = display.width()-paddle_width;  
  }

}



