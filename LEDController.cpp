#include "LedController.h"

#include <LogHelper.h>

#include "TaskIDs.h"


DEFINE_GRADIENT_PALETTE( my_palette ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 myPal = my_palette;

LedController::LedController() : AbstractIntervalTask(100) {
  
}

void LedController::init() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, PIN_LED_DATA, LED_COLOR_ORDER>(leds, LED_NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(LED_BASE_BRIGHTNESS);

  //setColor(CRGB(100, 100, 100));
  //setColor(CRGB(250, 158, 84));   // orange
  //setColor(CRGB(111, 105, 229));    // blue
  setColor(CRGB::Amethyst);

  LOG_PRINTLN(F("Init LED"));
}

void LedController::update() {
  for (int i = 0; i < LED_NUM_LEDS; i++) {
    leds[i] = currentColor;
    leds[i].fadeLightBy(random16(100));
    //leds[i].fadeToBlackBy(min(200, sin8(sinus + i * LED_NUM_LEDS)));
  }

  if (currentBrightness>LED_BRIGHTNESS_SPAN) brightnessUp=false;
  if (currentBrightness<0)  brightnessUp=true;

  if (brightnessUp) {
    currentBrightness+=LED_BRIGHTNESS_SPEED;
  } else {
    currentBrightness-=LED_BRIGHTNESS_SPEED;
  }

  FastLED.setBrightness(baseBrightness - currentBrightness);

  LOG_PRINTLN(currentBrightness);

  FastLED.show();
}

void LedController::setColor(CRGB c) {
  currentColor = c;
  fill_solid(leds, LED_NUM_LEDS, c);
  FastLED.show();
}

void LedController::setColorFromPalette(uint8_t index) {
  setColor(ColorFromPalette(myPal, index));
}
