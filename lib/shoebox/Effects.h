#ifndef EFFECTS_H
#define EFFECTS_H

#include <FastLED.h>

#include "Shoebox.h"


#define CHANGE_DELAY  800L
#define HALF_DELAY (CHANGE_DELAY / 2)


class Effect {
public:
    virtual ~Effect() = default;;

    virtual void restart() = 0;

    virtual void loop(ShoeBox &shoeBox) = 0;
};


class UnicolorEffect : public Effect {
public:

    explicit UnicolorEffect(const CRGB &color)
            : _color(color), _start(millis()), _state(DOWN) {
        Serial.println("NEW");
    }

    void restart() override;

    void loop(ShoeBox &shoeBox) override;

    void changeHue(const uint8_t hue) {
        hsv2rgb_rainbow(CHSV(hue, 255, 255), _color);
    }

    ~UnicolorEffect() override = default;

private:

    enum State {
        DOWN, UP, NORMAL
    };
    CRGB _color;
    long _start;
    State _state;
};





class DiscoPixel {
public:
    void reset();

    void loop(CRGB &pixel);

private:
    CRGB _color;
    unsigned long _start;
    unsigned long _duration;
};

class DiscoEffect : public Effect {
public:
    void restart() override;

    void loop(ShoeBox &shoeBox) override;

    ~DiscoEffect() override = default;

private:
    enum State {
        FADE, NORMAL
    };

    DiscoPixel _pixels[NUM_LEDS];
    unsigned long _start;
    State _state;
};


#endif