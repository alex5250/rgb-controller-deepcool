/*
 * config using uart 
 * example cpu load 
 * load 065 1 
 * where load is a mode 
 * 065 is value from 0 and 100 
 * 1 -fan rgb 
 * 0 - is tower rgb
 * Custom : 
 * set 000 040 000 008 0
 * where 000 - is red color from 0 -255
 * where 040 is green color from 0 -255
 * 008 is led address from 000-009
 * 1 -fan rgb 
 * 0 - is tower rgb
 * 
 */


#include <FastLED.h>
#define NUM_LEDS 10
#define FAN_PIN 8
#define TOWER_PIN 5


CRGB fan_led[NUM_LEDS];
CRGB tower_led[NUM_LEDS];



unsigned long timer_1;
unsigned long timer_2;


bool proper_delay(int delay_ms) {
  Serial.println(timer_2 - timer_1 );
  timer_2 = millis();
  return false;
  if (timer_2 - timer_1 >= delay_ms) {
    return true;
    timer_1 = millis();
    timer_2 = millis();
  }
}


void boot_animation(int r, int g , int b , int delay_ms) {
  // Turn the LED on, then pause
  for (int z = 0;  z < 10; z++) {
    fan_led[z] = CRGB (r, g, b);
    tower_led[z] =  CRGB (r, g, b);
    delay(delay_ms + z);

    FastLED.show();
  }
  delay(100);


  // Turn the LED on, then pause
  for (int z = 1;  z < 10; z++) {
    fan_led[z] = CRGB::Black;
    tower_led[z] = CRGB::Black;
    delay(delay_ms + z);

    FastLED.show();
  }



  fan_led[0] = CRGB(r - 200, g - 200, b - 200);
  tower_led[0] = CRGB(r - 200, g - 200, b - 200);



}


void display_null() {
  for (int z = 1;  z < 10; z++) {
    fan_led[z] = CRGB::Black;
    FastLED.show();
  }

}
void setup() {
  FastLED.addLeds<NEOPIXEL, FAN_PIN>(fan_led, NUM_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, TOWER_PIN>(tower_led, NUM_LEDS);  // GRB ordering is assumed
  Serial.setTimeout(1000);
  //boot_animation(255, 255, 50, 100);
  Serial.begin(115200);

}

void solid(bool is_fan_led, int r, int g, int b, int leds) {
  if (is_fan_led)  {
    for (int i = 0; i < leds; i++) {
      fan_led[i] = CRGB(r, g, b);
    }
  }
  else {
    for (int i = 0; i < leds; i++) {
      tower_led[i] = CRGB(r, g, b);
    }
  }
  FastLED.show();

}

void pc_controlled(bool is_fan_led, int pc_value) {
  //low = green 0-25
  //mid yellow 25-50
  //high red 50-75
  if (pc_value < 25 ) {
    solid(is_fan_led, pc_value, 255, 0, (int) pc_value / 10);
  }

  if (pc_value > 25 ) {
    solid(is_fan_led, pc_value * 3, 255, 0, (int) pc_value / 10);
  }
  if (pc_value > 60 ) {
    solid(is_fan_led, 255, 255 - pc_value * 2.5, 0, (int) pc_value / 10);
  }

}



void hadle() {
  String input = Serial.readString(); //Read the input

  Serial.println(input); //Repeat the input back
  bool x = true;
  if (input.startsWith("boot")) {
   boot_animation(255, 255, 255, 100);
  }

 
  if (input.startsWith("load")) {
    int cpu_load = input.substring(5, 8).toInt();
    int mode = input.substring(10, 11).toInt();
    Serial.print("set param load =:");
    Serial.println(cpu_load);
    if(mode==0) {
      display_null();
      pc_controlled(true,cpu_load);
    }
    if(mode==1) {
      display_null();
      pc_controlled(false,cpu_load);
    }



  }
  if (input.startsWith("set")) {
    int r = input.substring(4, 7).toInt();
    int g = input.substring(8, 11).toInt();
    int b = input.substring(12, 15).toInt();
    int led = input.substring(16, 19).toInt();
    int mode = input.substring(20, 21).toInt();
    if (mode == 0) {
      solid(true, r, g, b, led);
    }
    else {
      solid(false, r, g, b, led);
    }


  }

}

void loop() {

  if (Serial.available() > 0) {
    hadle();
  }






}
