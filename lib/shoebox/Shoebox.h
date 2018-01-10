#ifndef SHOEBOX_H
#define SHOEBOX_H


#include <FastLED.h>


#define DATA_PIN_TOP 13
#define DATA_PIN_BOTTOM 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 12
#define LED_ROW 6


class ShoeBox {


public:
    using LedArray = CRGBArray<NUM_LEDS>;

    ShoeBox() : _brightness(30) {}

    void setup();

    void loop() {
        if (_dirty) {
            FastLED.show();
        }
        _dirty = false;
    }

    LedArray &all_leds() { return _leds; };

    uint8_t brightness() const { return _brightness; }

    void brightness(const uint8_t brightness) {
        _brightness = brightness;
        FastLED.setBrightness(brightness);
        _dirty = true;
    }

    void markDirty() { _dirty = true; }

private:
    LedArray _leds;
    uint8_t _brightness;

    bool _dirty;
};

#endif