#ifndef WHEEL_H
#define WHEEL_H


#include <Arduino.h>

class Wheel {
public:
    using Callback = void (*)(const int);

    Wheel(uint8_t pin) : _pin(pin), _cb(nullptr) {}

    void loop() {
        int new_value = analogRead(_pin);
        if (_value != new_value) {
            _value = new_value;
            if (_cb) {
                _cb(new_value);
            }
        }
    }

    void connect(Callback cb) {
        _cb = cb;
    }

private:
    uint8_t _pin;
    Callback _cb;

    int _value;
};


#endif //WHEEL_H
