#include <Arduino.h>

#include "Debug.hpp"
#include "Constants.hpp"
#include "painlessMesh.h"
#include "Facilities_MeshNetwork.hpp"
#include "Tasks_ExampleTransmitTask.hpp"
#include "Tasks_ExampleDisplayTask.hpp"
#include "MeshControl.hpp"
#include "../algorithms/shapes.hpp"


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
   taskScheduler.addTask( exampleDisplayTask );
   exampleTransmitTask.enable();
   exampleDisplayTask.enable();


   MY_DEBUG_PRINTLN(F("Setup completed"));
   */
  Shapes::Shape * shapes = new Shapes::Shape();
  char** fullimage = shapes->get(Shapes::TRIANGLE, 4, 1);
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

//! Called repeatedly after setup().
void loop()
{
    mesh.setPixel(0,0,255);
   //taskScheduler.execute();
   //meshNetwork.update();
}
