#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 8

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN1 2
#define DATA_PIN2 3
#define DATA_PIN3 4

#define COLOR_ON_1 CRGB( 32, 0, 32)
#define COLOR_ON_2 CRGB( 32, 16, 0)
#define COLOR_ON_3 CRGB( 0, 32, 0)
#define COLOR_OFF CRGB::Black


// Define the array of leds
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

void setup() {

  Serial.begin(9600);
  // while the serial stream is not open, do nothing:
  while (!Serial) ;

  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds2, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS);

  // Turn the LED on, then pause
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = COLOR_ON_1;
    leds2[i] = COLOR_ON_2;
    leds3[i] = COLOR_ON_3;
    FastLED.show();
    delay(100);
  }

  // Now turn the LED off, then pause
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = COLOR_OFF;
    leds2[i] = COLOR_OFF;
    leds3[i] = COLOR_OFF;
    FastLED.show();
    delay(100);
  }

}

void loop() {

  if (Serial.available() > 0 ) {
    Serial.println( Serial.available() );

    int b1 = Serial.parseInt();
    char m[5] = {0, 0, 0, 0, 0};
    sprintf(m, "%d", b1);

    Serial.println(b1);
    Serial.println("====");
    Serial.println(m[0]);
    Serial.println(m[1]);
    Serial.println(m[2]);
    Serial.println("====");

    if (Serial.read() == '\n') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds1[i] = (i < m[0] - 48) ? COLOR_ON_1 : COLOR_OFF;
        leds2[i] = (i < m[1] - 48) ? COLOR_ON_2 : COLOR_OFF;
        leds3[i] = (i < m[2] - 48) ? COLOR_ON_3: COLOR_OFF;
      }
    }
  }

  FastLED.show();

}

