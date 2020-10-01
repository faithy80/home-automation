/* This is a simple tester application to determine the voltage the connected LiPo battery
 */

#define LiPo_pin A0               // Define the battery measuring pin

void setup()
{
  pinMode(LiPo_pin, INPUT);       // Set the measuring pin to input
  Serial.begin(9600);             // Open the srial port for debug
}

void loop() {
  // Get the analog voltage converted to units (~ 0V - 5V ==> 0 - 1023 units)
  // For example, 4.12V is 905 units while the Arduino Nano is powered from USB
  // The voltages need to be recalibrated when the device is operated from battery
  int reading = analogRead(0);

  // Print reading to the serial port
  Serial.print(reading);
  Serial.println(" units");
  
  // Wait 1 second before the next reading
  delay(1000);
}
