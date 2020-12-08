#include <SPI.h>                                        // Include the SPI communication protocol library
#include <nRF24L01.h>                                   // Include the nRF24L01 transciever library
#include <RF24.h>                                       // Include the RF24 radio driver library

RF24 radio(9, 10);                                      // Setup CE, CSN pins
const byte address[6] = "00001";                        // Byte of array representing the address
int relay_pin = 3;                                      // Setup relay signal pin
char puffer[32];                                        // A buffer to send data over the nRF24L01 transciever
String received_text = "";                              // A string to fetch received buffer data

void setup()
{
  pinMode(relay_pin, OUTPUT);                           // Setup relay signal pin as OUTPUT
  Serial.begin(9600);                                   // Open serial port, set data rate to 9600 bps
  radio.begin();                                        // Starting the Wireless communication
  radio.openReadingPipe(0, address);                    // Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);                        // You can set this as minimum or maximum depending on the distance between the transmitter and receiver
  radio.startListening();                               // This sets the module as receiver
}

void loop()
{
  if (radio.available())                                // Looking for the data
  {
    radio.read(&puffer, sizeof(puffer));                // Reading the data from the nRF24L01 transciever
    received_text = puffer;                             // Convert the char array to string
    received_text.trim();                               // Remove whitespaces from the string
    Serial.print("Incoming text: ");                    // Send feedback to the serial port
    Serial.println(received_text);
    
    if (received_text == "ON")                          // If the received string is "ON"
    {
      digitalWrite(relay_pin, HIGH);                    // Turn on the relay
    }
    if (received_text == "OFF")                         // If the received string is "OFF"
    {
      digitalWrite(relay_pin, LOW);                     // Turn off the relay
    }
  }

  received_text = "";                                   // Empty the string variable
  
  delay(100);
}
