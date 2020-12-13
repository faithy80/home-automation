/* This is a simple application to test the DHT sensor connected to the Arduino board.
 */

#include <DHT.h>              // Include the DHT temperature and humidity sensor library
#define DHTPIN 2              // Define the pin that the sensor is connected to
#define DHTTYPE DHT11         // Define the type of sensor
DHT dht(DHTPIN, DHTTYPE);     // Create an instance of the DHT object


void setup()
{
  Serial.begin(9600);         // Open the serail port for debug
  dht.begin();                // Start the temperature sensor
}


void loop()
{
  // Read the temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Test if the reading was successful
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Incorrect values!");
  }

  else
  // Send the temperature and the humidity data to the serial port
  {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");
  }

  // Set delay for 10 seconds
  delay(10000);
}
