/* This application sends temperature and humidity data over a wireless mesh network using a NodeMCU device and a DHT11 sensor.
 */

#include "painlessMesh.h"                                               // include painlessMesh library
#include <DHTesp.h>                                                     // include the ESP version of DHT sensor library

#define MESH_PREFIX     "whateverYouLike"                               // define wireless mesh credentials
#define MESH_PASSWORD   "somethingSneaky"
#define MESH_PORT       5555
#define DHTPIN          D5                                              // set the DHT sensor pin
DHTesp dht;                                                             // an instance of the DHT sensor object
Scheduler userScheduler;                                                // an instance of the scheduler
painlessMesh  mesh;                                                     // an instance of the painlessMesh object
void sendMessage();                                                     // function prototype
Task taskSendMessage(TASK_SECOND * 1 , TASK_FOREVER, &sendMessage);     // define the message sender task


// Function declarations
void sendMessage()
{
  DynamicJsonDocument doc(1024);                                        // read data and store in JSON format
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  doc["TEMP"] = t;
  doc["HUM"] = h;
  String msg ;
  serializeJson(doc, msg);                                              // serialize JSON to prepare for sending
  mesh.sendBroadcast(msg);                                              // send data over the mesh network
  taskSendMessage.setInterval((TASK_SECOND * 5));                       // repeat sending the data in every 5 seconds
  Serial.print("Temperature: ");                                        // feedback to the serial port
  Serial.print(t);
  Serial.print(", humidity: ");
  Serial.println(h);
  digitalWrite(LED_BUILTIN, LOW);                                       // visual feedback using the built-in LED
  delay(25);
  digitalWrite(LED_BUILTIN, HIGH);
  
}


void setup() {
  Serial.begin(9600);                                                   // open serial port, speed set to 9600 bps
  dht.setup(DHTPIN, DHTesp::DHT11);                                     // setup the DHT sensor
  delay(250);                                                           // a short delay for the DHT sensor
  pinMode(LED_BUILTIN, OUTPUT);                                         // setup the built-in LED
  mesh.setDebugMsgTypes(ERROR | STARTUP);                               // setup the mesh network messages
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);     // setup the mesh network
  userScheduler.addTask(taskSendMessage);                               // setup scheduler to repeat sending the data 
  taskSendMessage.enable();
}


void loop() {
  mesh.update();                                                        // update mesh network
}
