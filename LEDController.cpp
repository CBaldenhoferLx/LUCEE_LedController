#include "LedController.h"

#include <LogHelper.h>

#include "TaskIDs.h"

LedController::LedController() : AbstractIntervalTask(20) {
  
}

void LedController::init() {
  FastLED.addLeds<LED_TYPE, PIN_LED_DATA, LED_COLOR_ORDER>(leds, LED_NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(LED_BRIGHTNESS);
}

void LedController::update() {
  sinus+=1;

  for (byte i = 0; i < LED_NUM_LEDS; i++) {
    leds[i].fadeLightBy(sin8(sinus + i * LED_NUM_LEDS));
  }
  FastLED.show();

}

void LedController::setColor(CRGB c) {
  fill_solid(leds, LED_NUM_LEDS, c);
}
