#include "NetworkController.h"

#include "LEDController.h"

#include <LogHelper.h>

#include "TaskIDs.h"
#include "Debug.h"

NetworkController* NetworkController::mInstance;

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

  LOG_PRINTLN(F("Ethernet start"));

  Ethernet.begin(mac/*, ip*/);
  LOG_PRINTLN(F("Ethernet started"));

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    LOG_PRINTLN(F("Ethernet HW missing"));
  }

  while (Ethernet.linkStatus() != LinkON) {
    LOG_PRINT(Ethernet.linkStatus());
    LOG_PRINTLN(F("Ethernet cable is not connected."));
    delay(500);
  }

  instance()->ethernetServer = new EthernetServer(8080);
  LOG_PRINT(F("Local IP: "));
  LOG_PRINTLN(Ethernet.localIP());
}

void NetworkController::update() {
  if (last_dhcp==0 || millis() - last_dhcp>DHCP_TIMEOUT_MS) {
    LOG_PRINTLN(F("DHCP maintain"));
    Ethernet.maintain();
    last_dhcp = millis();
  }

  EthernetClient client = ethernetServer->available();
  if (client) {
    if (client.connected() && client.available()) {
      String line = client.readStringUntil('\r');
      if (line.startsWith("GET")) {
        CRGB c = parseGET(line);
        instance()->getTaskManager()->getTask<LedController*>(LED_CONTROLLER)->setColor(c);

        client.println("HTTP/1.1 200 OK");
        client.println("Content-length: 0");
        client.println("Connection: close");

        delay(10);
        
        LOG_PRINTLN(F("Response sent"));
      } else {
        LOG_PRINT(F("Unsupported method: "));
        LOG_PRINTLN(line);
      }
    }
    
    client.stop();
  }
}

CRGB NetworkController::parseGET(String data) {
  CRGB returnC;
  
  String getReq = data.substring(4);

  if (getReq.startsWith("/color")) {
    int r = getReq.indexOf("r=");
    int rEnd = getReq.indexOf("&", r);
    int g = getReq.indexOf("g=");
    int gEnd = getReq.indexOf("&", g);
    int b = getReq.indexOf("b=");
    int bEnd = getReq.indexOf("&", b);
    
    if (r>=0 && g>=0 && b>=0) {
      returnC.r = getReq.substring(r+2, rEnd).toInt();
      returnC.g = getReq.substring(g+2, gEnd).toInt();
      returnC.b = getReq.substring(b+2, bEnd).toInt();
    } else {
      LOG_PRINTLN(F("Invalid color"));
    }
  } else {
    LOG_PRINTLN(F("Unknown path"));
  }

  return returnC;
} 
