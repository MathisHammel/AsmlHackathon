//
//! \file
//
// Created by Sander van Woensel / Umut Uyumaz
// Copyright (c) 2018 ASML Netherlands B.V. All rights reserved.
//
//! Example Task to output something to the LED Matrix.
#include "Tasks_ExampleDisplayTask.hpp"

#include "Debug.hpp"
#include "Constants.hpp"
#include "Shapes.hpp"
#include "MeshControl.hpp"


#include "Facilities_MeshNetwork.hpp"

#include <LEDMatrixDriver.hpp>

#include <functional>

namespace Tasks {


const int ExampleDisplayTask::LEDMATRIX_WIDTH = 31;
const int ExampleDisplayTask::LEDMATRIX_HEIGHT = 7;
const int ExampleDisplayTask::LEDMATRIX_SEGMENTS = 4;
const int ExampleDisplayTask::LEDMATRIX_INTENSITY = 5;
const int ExampleDisplayTask::LEDMATRIX_CS_PIN = 16;
const unsigned long ExampleDisplayTask::POLL_DELAY_MS = 20;

//! Initializes the LED Matrix display.
ExampleDisplayTask::ExampleDisplayTask(Facilities::MeshNetwork& mesh) :
   Task(POLL_DELAY_MS , TASK_FOREVER, std::bind(&ExampleDisplayTask::execute, this)),
   meshctl(mesh),
   m_mesh(mesh),
   m_lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN),
   m_x(0)
{
   m_lmd.setEnabled(true);
   m_lmd.setIntensity(LEDMATRIX_INTENSITY);
    m_mesh.onReceive(std::bind(&ExampleDisplayTask::receivedCb, this, std::placeholders::_1, std::placeholders::_2));
    MY_DEBUG_PRINTLN("Mesh bound.");
}

//! Update display
void ExampleDisplayTask::execute()
{

}

void ExampleDisplayTask::receivedCb(Facilities::MeshNetwork::NodeId nodeId, String& msg)
{
   MY_DEBUG_PRINTF("Received ");
   MY_DEBUG_PRINTLN(msg);
   Shapes::Shape obj;
   Shapes::Type t;

   if (msg.equals("Large")) {
     t = Shapes::LARGE_OPAQUE;
   }
   else if (msg.equals("Small")) {
     t = Shapes::SMALL_OPAQUE;
   }
   else if (msg.equals("Annular")) {
     t = Shapes::ROUND;
   }
   else if (msg.equals("Reset")) {
       char img[8][32] = {0};
        meshctl.localDisplayImage(img);
        MY_DEBUG_PRINTLN("Image update done.");
        return;
   } else { return;}

   char** fullimage = obj.get(t, 4, 1);
    int x,y;
   if(NODE_ID == 1) {
    char image[8][32];
    for (x = 0; x < 8; x++) {
      for(y = 0; y < 32; y++) {
        image[x][y] = fullimage[x][y];
      }
    }
    meshctl.localDisplayImage(image);

  } else if (NODE_ID == 2) {
        char image[8][32];
        for (x = 0; x < 8; x++) {
            for(y = 0; y < 32; y++) {
                image[x][y] = fullimage[x+8][y];
            }
        }  
        meshctl.localDisplayImage(image);
    } else if (NODE_ID == 3) {
        char image[8][32];
        for (x = 0; x < 8; x++) {
            for(y = 0; y < 32; y++) {
                image[x][y] = fullimage[x+16][y];
            }
        }
        meshctl.localDisplayImage(image);
    } else if (NODE_ID == 4) {
        char image[8][32];
        for (x = 0; x < 8; x++) {
            for(y = 0; y < 32; y++) {
                image[x][y] = fullimage[x+24][y];
            }
        }        
        meshctl.localDisplayImage(image);
    }
    MY_DEBUG_PRINTLN("Image update done.");
}

void ExampleDisplayTask::receivedJsonPacket(Facilities::MeshNetwork::NodeId nodeId, String& msg)
{
    //parse json packet
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(msg);
    
    if (root.containsKey("type")) {
        if (String(MSG_TYPE_IMG).equals(root["type"].as<String>())) {
            // check for on: true or false
            size_t nodeId = root["nodeId"];
            if(1) //check if destined to this nodeId == mesh.getNodeId(); 
            {
                //TODO: call local interface
            }
        }
        
    }
}
} // namespace Tasks
