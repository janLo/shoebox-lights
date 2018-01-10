#include <Arduino.h>

#include <FastLED.h>

#include <Shoebox.h>
#include <Effects.h>
#include <Button.h>
#include <Wheel.h>

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


ShoeBox box;


UnicolorEffect uni_red(CRGB::Red);
UnicolorEffect uni_white(CRGB::Wheat);
UnicolorEffect uni_yellow(CRGB::Yellow);
UnicolorEffect uni_lightSkyBlue(CRGB::SkyBlue);

UnicolorEffect uni_select(CRGB::Black);

DiscoEffect disco;

//Effect *current_effect = new UnicolorEffect(CRGB::Red);
Effect *current_effect = &disco;

Button btn_red(2);
Button btn_white(3);
Button btn_yellow(4);
Button btn_skyblue(5);

Button btn_selecthue(6);

Button btn_disco(7);

Wheel whl_brightness(A0);
Wheel whl_hue(A1);


void changeEffect(Effect &effect) {
    current_effect = &effect;
    effect.restart();
}

uint8_t fixAnalogValue(const int val) {
    return (uint8_t) ((val >> 2) & 0xff);
}

void setup() {
    Serial.begin(115200);

    btn_red.connect([]() { changeEffect(uni_red); });
    btn_white.connect([]() { changeEffect(uni_white); });
    btn_yellow.connect([]() { changeEffect(uni_yellow); });
    btn_skyblue.connect([]() { changeEffect(uni_lightSkyBlue); });

    btn_selecthue.connect([]() { changeEffect(uni_select); });

    btn_disco.connect([]() { changeEffect(disco); });

    whl_brightness.connect([](const int brightness) {
        box.brightness(fixAnalogValue(brightness));
    });

    whl_hue.connect([](const int hue) {
        uni_select.changeHue(fixAnalogValue(hue));
    });

    box.setup();
}


void loop() {

    whl_brightness.loop();
    whl_hue.loop();

    btn_red.loop();
    btn_white.loop();
    btn_yellow.loop();
    btn_skyblue.loop();
    btn_selecthue.loop();
    btn_disco.loop();

    current_effect->loop(box);

    box.loop();
}
