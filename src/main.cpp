#include <Arduino.h>

#include <FastLED.h>

/*
red
white
warm
cool

dial

disco


10 led
*/

#define DATA_PIN_TOP 13
#define DATA_PIN_BOTTOM 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 12
#define LED_ROW 6

#define BRIGHTNESS 96

uint8_t pins[] = {2, 3, 4, 5};
CRGB colors[] = {CRGB::Red, CRGB::White, CRGB::Yellow, CRGB::LightSkyBlue};

CRGB currentColor = CRGB::White;
CRGBArray<NUM_LEDS> all_leds; 

void setup() {
  for (uint8_t i = 0; i < 4; ++i) {
    pinMode(pins[i], INPUT);
  }

  FastLED.addLeds<LED_TYPE, DATA_PIN_TOP, COLOR_ORDER>(all_leds,LED_ROW)
      .setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_BOTTOM, COLOR_ORDER>(all_leds+LED_ROW,LED_ROW)
      .setCorrection(TypicalLEDStrip);
}

void fill(CRGB color) {
    all_leds = color;
}


uint8_t i = 0;
void loop() {

  all_leds.fill_rainbow(i++);
  for (uint8_t i = 0; i < 4; ++i) {
    int isPressed = digitalRead(pins[i]);
    if (isPressed) {
      currentColor = colors[i];
      fill(currentColor);
    }
  }

//  uint16_t val = analogRead(14);

//  FastLED.setBrightness(val / 4);

  FastLED.show();
}
