/* This application is a simple thermometer. It displays the temperature and humidity on an OLED screen 
 * and refreshes the data in every 10 seconds.
 */

#include <Wire.h>                 // Include I2C library
#include <Adafruit_GFX.h>         // Include Adafruit core graphics library
#include <Adafruit_SSD1306.h>     // Include the OLED driver library

#define SCREEN_WIDTH 128          // OLED display width, in pixels
#define SCREEN_HEIGHT 64          // OLED display height, in pixels

// Create an instance of the display driver object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include <DHT.h>                  // Include the DHT temperature and humidity sensor library
#define DHTPIN 2                  // Select the pin that the sensor is connected to
#define DHTTYPE DHT11             // Select the type of the sensor
DHT dht(DHTPIN, DHTTYPE);         // Create an instance of the DHT object


void setup()
{
  Serial.begin(9600);             // Open serial port for debug
  dht.begin();                    // Start the temperature sensor
  
  // Test if the memory allocation for image buffer fails
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  else
  {
    // Initialize the display
    display.setTextSize(1);
    display.setTextColor(WHITE);
  } 
}


void loop()
{
  // Read the temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Display data on the OLED screen
  display.clearDisplay();
  display.setCursor(0, 0);
  
  display.println("Temperature:");

  // If the temperature reading is incorrect
  if (isnan(temperature))
  {
    display.println("N/A");
  }

  else
  {
    display.print(temperature);
    display.println(" C");
  }
  
  display.println("Humidity:");
  
  // If the humidity reading is incorrect
  if (isnan(humidity))
  {
    display.println("N/A");
  }

  else
  {
    display.print(humidity);
    display.println(" %");
  }
  
  // Call this method for the changes to make effect
    display.display();
  
  // Set delay for 10 seconds
  delay(10000);
}
