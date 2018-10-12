#include <Arduino.h>

#include "Debug.hpp"
#include "Constants.hpp"
#include "painlessMesh.h"
#include "Facilities_MeshNetwork.hpp"
#include "Tasks_ExampleTransmitTask.hpp"
#include "Tasks_ExampleDisplayTask.hpp"
#include "MeshControl.hpp"
#include "shapes.hpp"
#include <functional>
#include <time.h>

// Translation unit local variables
namespace {

Scheduler                  taskScheduler;

Facilities::MeshNetwork    meshNetwork;
Tasks::ExampleTransmitTask exampleTransmitTask(meshNetwork);
Tasks::ExampleDisplayTask  exampleDisplayTask(meshNetwork);
}
MeshControl   mesh(meshNetwork);

//! Called once at board startup.
void setup()
{

   MY_DEBUG_BEGIN(115200);

   // Create MeshNetwork
   meshNetwork.initialize(F("RedTeam"), F("passforRed"), taskScheduler);
/*
   // Create and add tasks.
   taskScheduler.addTask( exampleTransmitTask );
   */
   taskScheduler.addTask( exampleDisplayTask );
   //exampleTransmitTask.enable();
   exampleDisplayTask.enable();


   MY_DEBUG_PRINTLN(F("Setup completed"));
    Shapes::Shape obj;
    Shapes::Type t = Shapes::ROUND;
    char** fullimage = obj.get(t, 4, 1);
  int x, y;

  if(NODE_ID == 1) {
    char image[8][32];
    for (x = 0; x < 8; x++) {
      for(y = 0; y < 32; y++) {
        image[x][y] = fullimage[x][y];
      }
    }
    mesh.localDisplayImage(image);

  } else if (NODE_ID == 2) {
    char image[8][32];
    for (x = 0; x < 8; x++) {
      for(y = 0; y < 32; y++) {
        image[x][y] = fullimage[x+8][y];
      }
    }  
        mesh.localDisplayImage(image);
} else if (NODE_ID == 3) {
      char image[8][32];
    for (x = 0; x < 8; x++) {
      for(y = 0; y < 32; y++) {
        image[x][y] = fullimage[x+16][y];
      }
    }
      mesh.localDisplayImage(image);
} else if (NODE_ID == 4) {
  char image[8][32];
    for (x = 0; x < 8; x++) {
      for(y = 0; y < 32; y++) {
        image[x][y] = fullimage[x+24][y];
      }
    }        
    mesh.localDisplayImage(image);
}
}

void delay2(int x){
  while(--x) {
    taskScheduler.execute();
    meshNetwork.update();
  }
}
//! Called repeatedly after setup().
void loop()
{
  taskScheduler.execute();
   meshNetwork.update();
  if(MASTER) {
    MY_DEBUG_PRINTLN("Sending msg Large");
    String msg = F("Large");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(300000);

    MY_DEBUG_PRINTLN("Sending msg Reset");
    msg = F("Reset");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(100000);

    MY_DEBUG_PRINTLN("Sending msg Small");
    msg = F("Small");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(300000);

    MY_DEBUG_PRINTLN("Sending msg Reset");
    msg = F("Reset");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(100000);

    MY_DEBUG_PRINTLN("Sending msg Annular");
    msg = F("Annular");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(300000);

    MY_DEBUG_PRINTLN("Sending msg Reset");
    msg = F("Reset");
    meshNetwork.sendBroadcastAll(msg);
    taskScheduler.execute();
    meshNetwork.update();
    delay2(100000);
  }
  //mesh.setPixel(0,0,255);

}
