#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include "AbstractIntervalTask.h"
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#include "Pins.h"

#define LED_TYPE    WS2812B
#define LED_COLOR_ORDER GRB
#define LED_NUM_LEDS    288  // 2x144

#define LED_BASE_BRIGHTNESS         60
#define LED_BRIGHTNESS_SPEED 1
#define LED_BRIGHTNESS_SPAN 50

class LedController : public AbstractIntervalTask {
public:
  LedController();

  void init();

  void update();

  bool useInitWDT() {
    return false;
  }


  //void setColor(uint8_t r, uint8_t g, uint8_t b);
  void setColor(CRGB c);

  void setColorFromPalette(uint8_t index);

  void setBrightness(uint8_t value);

  void triggerAnimation();

private:
  CRGB currentColor;
  CRGB leds[LED_NUM_LEDS];

  float currentBrightness = 0;
  int baseBrightness = LED_BASE_BRIGHTNESS;
  bool brightnessUp = true;  

  void playDefault();

};


#endif    //LEDCONTROLLER_H
