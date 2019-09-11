#include "NetworkController.h"

#include "LEDController.h"

#include <LogHelper.h>

#include "TaskIDs.h"

#include "Debug.h"

NetworkController* NetworkController::mInstance;
//WebSocketsServer* NetworkController::wsServer;
//EthernetClient NetworkController::activeClient;
//uint64_t NetworkController::lastDBPing = 0;

NetworkController::NetworkController() : AbstractTask() {
  mInstance = this;
}

NetworkController* NetworkController::instance() {
  return mInstance;
}

void NetworkController::init() {
  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  //IPAddress ip(192, 168, 0, 1);

  CRGB tc = parseGET("GET /color/set?r=111&g=105&b=229&a=0 HTTP/1.1\r\nHost: 172.30.90.117:8080");
  LOG_PRINTLN(tc);

  return;

  LOG_PRINTLN(F("Ethernet start"));
  
  Ethernet.begin(mac/*, ip*/);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    LOG_PRINTLN(F("Ethernet HW fail"));
  }

  while (Ethernet.linkStatus() != LinkON) {
    LOG_PRINTLN(F("Ethernet cable is not connected."));
    delay(500);
  }

  instance()->ethernetServer = new EthernetServer(8080);
  LOG_PRINT(F("Local IP: "));
  LOG_PRINTLN(Ethernet.localIP());
}

void NetworkController::update() {

  return;
  
  if (last_dhcp==0 || millis() - last_dhcp>DHCP_TIMEOUT_MS) {
    LOG_PRINTLN(F("DHCP maintain"));
    Ethernet.maintain();
    last_dhcp = millis();
  }

  EthernetClient client = ethernetServer->available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        if (line.startsWith("GET")) {
          CRGB c = parseGET(line);
          instance()->getTaskManager()->getTask<LedController*>(LED_CONTROLLER)->setColor(c);
        }
      }
    }
  }
}

CRGB NetworkController::parseGET(String data) {
  CRGB returnC;
  
  String getReq = data.substring(4);
  int r = getReq.indexOf("r=");
  int rEnd = getReq.indexOf("&", r);
  int g = getReq.indexOf("g=");
  int gEnd = getReq.indexOf("&", g);
  int b = getReq.indexOf("b=");
  int bEnd = getReq.indexOf("&", b);
  
  if (r>=0 && g>=0 && b>=0) {
    returnC.r = getReq.substring(r, rEnd).toInt();
    returnC.g = getReq.substring(g, gEnd).toInt();
    returnC.b = getReq.substring(b, bEnd).toInt();
  }

  return returnC;
} 
