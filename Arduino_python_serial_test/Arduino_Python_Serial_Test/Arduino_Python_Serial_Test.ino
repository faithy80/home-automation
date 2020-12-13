/* This application is a test for the serial communication between an Arduino Nano and a Raspberry Pi or a Linux based computer.
 */

int analogPin = A0;                       // Set analog pin
int data = 0;                             // Set data variable
char userInput;                           // Set variable for serial input


void setup(){
  Serial.begin(9600);                     // Open serial port, set data rate to 9600 bps
}


void loop()
{
  if(Serial.available()> 0)               // Send data only when you receive data
  {
    userInput = Serial.read();            // Read user input

    if(userInput == 'g')                  // If we get expected value
    {
      data = analogRead(analogPin);       // Read the input pin
      Serial.println(data);               // Send feedback to the serial port
    }
  }
}
