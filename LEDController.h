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
#define LED_NUM_LEDS    78

#define LED_BRIGHTNESS         255


class LedController : public AbstractIntervalTask {
public:
  LedController();

  void init();

  void update();

  //void setColor(uint8_t r, uint8_t g, uint8_t b);
  void setColor(CRGB c);

  void setBrightness(uint8_t value);

private:
  CRGB leds[LED_NUM_LEDS];
  byte sinus = 0;

};


#endif    //LEDCONTROLLER_H
