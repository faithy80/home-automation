/* This is a simple application to test the OLED screen connected to the Arduino board.
 */

#include <Wire.h>                 // Include I2C library
#include <Adafruit_GFX.h>         // Include Adafruit core graphics library
#include <Adafruit_SSD1306.h>     // Include the OLED driver library

#define SCREEN_WIDTH 128          // Define the OLED display width in pixels
#define SCREEN_HEIGHT 64          // Define the OLED display height in pixels

// Create an instance of the display driver object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup()
{
  Serial.begin(9600);             // Open the serial port for debug
  
  // Test if the memory allocation for image buffer fails
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  else
  {
    // Initialize the display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
  
    // Print Hello, world! 8 times to test the whole display
    // (0.96" I2C OLED screen)
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");
    display.println("Hello, world!");

    // Call this method for the changes to make effect
    display.display();
  } 
}


void loop()
{
  // Nothing goes here...
}
