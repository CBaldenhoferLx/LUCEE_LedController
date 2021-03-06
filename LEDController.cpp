#include "LedController.h"

#include <LogHelper.h>

#include "TaskIDs.h"

LedController::LedController() : AbstractIntervalTask(20) {
  
}

void LedController::init() {
  FastLED.addLeds<LED_TYPE, PIN_LED_DATA, LED_COLOR_ORDER>(leds, LED_NUM_LEDS).setCorrection(TypicalLEDStrip).setTemperature(Tungsten40W);
  FastLED.setBrightness(LED_BRIGHTNESS);

  //setColor(CRGB(100, 100, 100));
  //setColor(CRGB(250, 158, 84));   // orange
  setColor(CRGB(111, 105, 229));    // blue
  //setColor(CRGB::DarkOrange);
}

void LedController::update() {
  sinus+=1;

  for (byte i = 0; i < LED_NUM_LEDS; i++) {
    leds[i] = currentColor;
    leds[i].fadeLightBy(min(200, sin8(sinus + i * LED_NUM_LEDS)));
    //leds[i].fadeToBlackBy(min(200, sin8(sinus + i * LED_NUM_LEDS)));
  }
  FastLED.show();
}

void LedController::setColor(CRGB c) {
  currentColor = c;
  fill_solid(leds, LED_NUM_LEDS, c);
  FastLED.show();
}
