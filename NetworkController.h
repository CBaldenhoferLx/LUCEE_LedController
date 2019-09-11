#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "AbstractTask.h"
#include <SPI.h>
#include <Ethernet.h>
#include <FastLED.h>

#define DHCP_TIMEOUT_MS 120000

#define DB_PING_INTERVAL 4000

#define HOST_NAME "FAWControl"

class NetworkController : public AbstractTask {
public:
  NetworkController();

  void init();

  void update();

  bool useInitWDT() {
    return false;
  }

  static NetworkController* instance();

private:
  static NetworkController* mInstance;

  EthernetServer* ethernetServer;

  uint64_t last_dhcp = 0;

  CRGB parseGET(String data);

};

#endif    // NETWORKCONTROLLER_H
