#include "Shoebox.h"


void ShoeBox::setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN_TOP, COLOR_ORDER>(_leds, LED_ROW)
            .setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN_BOTTOM, COLOR_ORDER>(_leds + LED_ROW, LED_ROW)
            .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(40);

    FastLED.setDither(false);
}
