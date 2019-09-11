#include <LogHelper.h>
#include <TaskManager.h>

#include "LEDController.h"
#include "NetworkController.h"

TaskManager taskManager;

LedController ledController;
NetworkController networkController;

void setup() {
  LOG_INIT();

  taskManager.registerTask(&ledController);  
  //taskManager.registerTask(&networkController);  
  
  taskManager.init();

  LOG_PRINTLN(F("Init complete"));
}

void loop() {
  taskManager.update();
  delay(10);
}
