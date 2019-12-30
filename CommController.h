#ifndef COMMCONTROLLER_H
#define COMMCONTROLLER_H

#include <AbstractTask.h>
#include "Pins.h"

//#define SERIAL_SPEED 9600

#define COMM_SERIAL Serial

#define DATA_PACKAGE_SIZE_MIN 3

#define DATAGRAM_START '@'
#define DATAGRAM_SEP ','
#define DATAGRAM_END ';'

class CommController : public AbstractTask {
public:
  CommController();

  enum PAction { ACTION_NONE, ACTION_SET_COLOR, ACTION_TRIGGER_ANIMATION };

  void init();

  void update();

  void sendPackage(PAction cmd, int param);

  void handlePackage();

private:
  String currentData;
};


#endif // COMMCONTROLLER_H
