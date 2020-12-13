/* This application is a test of the nRF24L01 wireless radio device. This code is for the transmitter side.
 */

#include <SPI.h>                                          // Include the SPI communication protocol library
#include <nRF24L01.h>                                     // Include the nRF24L01 transciever library
#include <RF24.h>                                         // Include the RF24 radio driver library

RF24 radio(9, 10);                                        // Setup CE, CSN pins
const byte address[6] = "00001";                          // Byte of array representing the address
char puffer[32];                                          // A buffer to send data over the nRF24L01 transciever
String text_to_send = "";                                 // The received string from the serial port

void setup()
{
  Serial.begin(9600);                                     // Open serial port, set data rate to 9600 bps
  radio.begin();                                          // Starting the Wireless communication
  radio.openWritingPipe(address);                         // Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);                          // You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();                                  // This sets the module as transmitter
}

void loop()
{
  if (Serial.available() > 0)                             // Send data only when you receive data
  {
    text_to_send = Serial.readString();                   // Read the incoming string
    text_to_send.trim();                                  // Remove whitespaces from the string
  }
  
  if ((text_to_send == "ON") || (text_to_send == "OFF"))  // If the received string is "ON" or "OFF"
  {
    text_to_send.toCharArray(puffer, 32);                 // Convert string to char array
    radio.write(&puffer, sizeof(puffer));                 // Sending the message to receiver
    Serial.print("Sent message: ");                       // Send feedback to the serial port
    Serial.println(text_to_send);
    text_to_send = "";                                    // Empty the string variable
  }
  
  delay(1000);                                            // Wait for 1 second
}
