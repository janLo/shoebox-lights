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

#define DATA_PIN 13
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 10

#define BRIGHTNESS 96

uint8_t pins[] = {2, 3, 4, 5};
CRGB colors[] = {CRGB::Red, CRGB::White, CRGB::Yellow, CRGB::LightSkyBlue};

CRGB currentColor = CRGB::White;
CRGB leds[NUM_LEDS];

void setup() {
  for (uint8_t i = 0; i < 4; ++i) {
    pinMode(pins[i], INPUT);
  }

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
}

void fill(CRGB color) {
  for (uint8_t i = 0; i < NUM_LEDS; ++i) {
    leds[i] = color;
  }
}

void loop() {
  for (uint8_t i = 0; i < 4; ++i) {
    int isPressed = digitalRead(pins[i]);
    if (isPressed) {
      currentColor = colors[i];
      fill(currentColor);
    }
  }

  uint16_t val = analogRead(14);

  FastLED.setBrightness(val / 4);

  FastLED.show();
}
