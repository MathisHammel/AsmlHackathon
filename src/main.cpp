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
#include <ESP8266WiFi.h>
#include <list>
#include <memory>

// Translation unit local variables
namespace {

Scheduler                  taskScheduler;

Facilities::MeshNetwork    meshNetwork;
Tasks::ExampleTransmitTask exampleTransmitTask(meshNetwork);
Tasks::ExampleDisplayTask  exampleDisplayTask(meshNetwork);
}
MeshControl   mesh(meshNetwork);
WiFiServer server(80);
String header;
char image1[32][32] = {0};
char image2[32][32] = {0};
//! Called once at board startup.
void setup()
{

   MY_DEBUG_BEGIN(115200);

   // Create MeshNetwork
   meshNetwork.initialize(F("RedTeam"), F("passforRed"), taskScheduler);
   WiFi.softAP("ASMR", "asmrasmr");
/*
   // Create and add tasks.
   taskScheduler.addTask( exampleTransmitTask );
   */
   taskScheduler.addTask( exampleDisplayTask );
   //exampleTransmitTask.enable();
   exampleDisplayTask.enable();


   MY_DEBUG_PRINTLN(F("Setup completed"));
  server.begin();
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
   //MY_DEBUG_PRINTLN(WiFi.softAPIP());
   //MY_DEBUG_PRINTLN(WiFi.softAPgetStationNum());
   WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    MY_DEBUG_PRINTLN("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        MY_DEBUG_PRINT(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // The HTTP response ends with another blank line
            char buf[10];
            itoa(meshNetwork.getNetSize(), buf, 10);
            client.println(buf);
            MY_DEBUG_PRINTF("Client update : %s", buf);

            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            if (currentLine[0] == 'G' && currentLine[1] == 'E' && currentLine[2] == 'T') {
              if(currentLine[6] == 'i' && currentLine[7] == 'm' && currentLine[8] == 'g') {
                MY_DEBUG_PRINTLN("Image is here");
                int rid;
                for(rid = 0; rid < 1024; rid++) {
                  image1[rid%32][rid/32]=currentLine[11+rid]-'0';
                  //MY_DEBUG_PRINTF("%d,%d : %d ; ", rid%32, rid/32, image1[rid%32][rid/32]);
                }
                mesh.localDisplayImage(image1);
              }
            }
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
   /*
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
  }*/
  //mesh.setPixel(0,0,255);

}
