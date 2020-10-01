#include <Wire.h>                 // Include I2C library
#include <Adafruit_GFX.h>         // Include Adafruit core graphics library
#include <Adafruit_SSD1306.h>     // Include the OLED driver library

#define SCREEN_WIDTH 128          // OLED display width, in pixels
#define SCREEN_HEIGHT 64          // OLED display height, in pixels

// Create an instance of the display driver object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(9600);             // Open serial port for debug
  
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


void loop() {
}
