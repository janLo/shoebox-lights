#include "Effects.h"


void UnicolorEffect::loop(ShoeBox &shoeBox) {
    if (_state == NORMAL) {
        return;
    }

    long passed = millis() - _start;

    if (passed < CHANGE_DELAY) {
        float coeff = float(passed - HALF_DELAY) / HALF_DELAY;

        if (coeff > 0 && _state == DOWN) {
            _state = UP;
            shoeBox.all_leds() = _color;
        }

        FastLED.setBrightness(uint8_t (shoeBox.brightness() * abs(coeff)));
    } else {
        _state = NORMAL;
        FastLED.setBrightness(shoeBox.brightness());
    }
    shoeBox.markDirty();
}

void UnicolorEffect::restart() {
    _start = millis();
    _state = DOWN;
}

void DiscoEffect::loop(ShoeBox &shoeBox) {
    shoeBox.markDirty();

    if (_state == FADE) {
        unsigned long duration = millis() - _start;

        if (millis() - _start > HALF_DELAY) {
            _state = NORMAL;
            FastLED.setBrightness(shoeBox.brightness());
            return;
        }

        FastLED.setBrightness((uint8_t) (shoeBox.brightness() * float(HALF_DELAY - duration) / HALF_DELAY));
    } else {
        for (uint8_t i = 0; i < NUM_LEDS; ++i) {
            _pixels[i].loop(shoeBox.all_leds()[i]);
        }

    }
}

void DiscoEffect::restart() {
    for (auto &_pixel : _pixels) {
        _pixel.reset();
    }
    _start = millis();
    _state = FADE;
}

void DiscoPixel::loop(CRGB &pixel) {
    unsigned long duration = millis() - _start;

    float half_duration = _duration / 2.0;
    float tmp = float(duration - half_duration) / half_duration;
    float coeff = min(1.0, max(0.0, (1.0 - abs(tmp * tmp))));

    pixel = _color;
    pixel.nscale8(uint8_t(0xff * coeff));

    if (duration > _duration + 100) {
        reset();
    }
}

CRGB disco_colors[] = {CRGB::Red, CRGB::Blue, CRGB::Yellow, CRGB::Green, CRGB::Cyan, CRGB::Violet};

void DiscoPixel::reset() {
    _start = millis();
    _color = disco_colors[random8(6)];
    _duration = random16(500) + 400;
}
