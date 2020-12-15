/* This application receives temperature and humidity data over a wireless mesh network from another NodeMCU device.
 * This node is connected to a Linux-based device (Raspberry Pi in my case) that can also receive the data over
 * the serial port if requested.
 */

#include "painlessMesh.h"                                               // include the painlessMesh library

#define MESH_PREFIX     "whateverYouLike"                               // define wireless mesh credentials
#define MESH_PASSWORD   "somethingSneaky"
#define MESH_PORT       5555
Scheduler userScheduler;                                                // an instance of the scheduler
painlessMesh mesh;                                                      // an instance of the painlessMesh object
float temp = 0;                                                         // a variable to store temperature data
float hum = 0;                                                          // a variable to store humidity data
char userInput;                                                         // a variable to store user input


// Function declarations
void receivedCallback( uint32_t from, String &msg )
{
  String json;                                                          // read data and store in JSON format
  DynamicJsonDocument doc(1024);
  json = msg.c_str();
  DeserializationError error = deserializeJson(doc, json);              // deserialize JSON
  
  if (!error)                                                           // if the deserialization is successful
  {
    String Temp = doc["TEMP"];                                          // store the received data separately
    String Hum = doc["HUM"];
    temp = Temp.toFloat();
    hum = Hum.toFloat();
    digitalWrite(LED_BUILTIN, LOW);                                     // visual feedback using the built-in LED
    delay(25);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}


void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);                                         // open serial port, speed set to 9600 bps
  mesh.setDebugMsgTypes( ERROR | STARTUP );                             // setup the mesh network messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );   // setup the mesh network
  mesh.onReceive(&receivedCallback);                                    // setup the callback function
}


void loop()
{
  mesh.update();                                                        // update mesh network

  if(Serial.available()> 0)                                             // waiting for user input
  {
    userInput = Serial.read();                                          // read user input

    if(userInput == 'g')                                                // if we get expected value
    {
      // Serializing in JSON Format
      DynamicJsonDocument doc(1024);                                    // gather the data in JSON format
      doc["TEMP"] = temp;
      doc["HUM"] = hum;
      String msg;
      serializeJson(doc, msg);                                          // serialize JSON to prepare for sending
      Serial.println(msg);                                              // send data to the serial port
    }
  }
}
