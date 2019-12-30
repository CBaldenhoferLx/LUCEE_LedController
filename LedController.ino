#include <LogHelper.h>
#include <TaskManager.h>

#include "LEDController.h"
#include "CommController.h"

TaskManager taskManager;

LedController ledController;
CommController commController;

void setup() {
  LOG_INIT();

  taskManager.registerTask(&ledController);  
  taskManager.registerTask(&commController);  
  
  taskManager.init();

  LOG_PRINTLN(F("Init complete"));
}

void loop() {
  taskManager.update();
  delay(10);
}
