#include <Arduino.h>

#include "Debug.hpp"
#include "Constants.hpp"
#include "painlessMesh.h"
#include "Facilities_MeshNetwork.hpp"
#include "Tasks_ExampleTransmitTask.hpp"
#include "Tasks_ExampleDisplayTask.hpp"
#include "MeshControl.hpp"


using namespace std;

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

  Serial.setTimeout(100);
  
}

//! Called repeatedly after setup().
void loop()
{
    //mesh.setPixel(0,0,255);
    char recv[4097];
    //int nbytes = Serial.readBytes(recv, 10); // This crashes
    recv[10]=0;
    //MY_DEBUG_PRINTF("Received %d bytes : %s\n", nbytes, recv);
    //Serial.writeBytes(recv, 10);
   //taskScheduler.execute();
   //meshNetwork.update();
}
