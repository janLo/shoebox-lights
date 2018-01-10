#ifndef BUTTON_H
#define BUTTON_H


#include <Arduino.h>


#define DEBOUNCE_TIME 500

class Button {
public:
    using Callback = void (*)();

    Button(uint8_t pin) : _pin(pin), _cb(nullptr) {}

    void connect(Callback const cb) {
        _cb = cb;
        pinMode(_pin, INPUT_PULLUP);
    };

    void loop() {
        if (millis() - _down_time < DEBOUNCE_TIME) {
            return;
        }

        bool down = digitalRead(_pin) == 0;

        if (down && _cb) {
            _down_time = millis();
            _cb();
        }
    }

private:
    uint8_t _pin;
    Callback _cb;
    unsigned long _down_time;
};


#endif //SHOEBOX_LIGHTS_BUTTON_H
