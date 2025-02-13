#include <Arduino.h>

// Pin definitions for RGB LED
const int RED_PIN = 9;    // PWM pin for red
const int GREEN_PIN = 10; // PWM pin for green
const int BLUE_PIN = 11;  // PWM pin for blue

// Function declarations
void setColor(int red, int green, int blue);
void rainbowEffect(int wait);
void testEdge();
int currValue = 0;

void setup() {
  // Configure pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Initialize all colors off (HIGH for common anode)
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  
  // Start serial for debugging
  Serial.begin(115200);
  Serial.println("RGB LED Test Starting...");
}

void loop() {
  // Test each channel individually with full brightness
  
  // Test RED
  // Serial.println("Testing RED");
  // digitalWrite(RED_PIN, LOW);     // Turn on RED
  // digitalWrite(GREEN_PIN, HIGH);  // Others off
  // digitalWrite(BLUE_PIN, HIGH);
  // delay(2000);
  
  // // Test GREEN
  // Serial.println("Testing GREEN");
  // digitalWrite(RED_PIN, HIGH);
  // digitalWrite(GREEN_PIN, LOW);   // Turn on GREEN
  // digitalWrite(BLUE_PIN, HIGH);
  // delay(2000);
  
  // // Test BLUE
  // Serial.println("Testing BLUE");
  // digitalWrite(RED_PIN, HIGH);
  // digitalWrite(GREEN_PIN, HIGH);
  // digitalWrite(BLUE_PIN, LOW);    // Turn on BLUE
  // delay(2000);
  
  // All off
  // digitalWrite(RED_PIN, HIGH);
  // digitalWrite(GREEN_PIN, HIGH);
  // digitalWrite(BLUE_PIN, HIGH);
  // delay(1000);

  rainbowEffect(10);
  //testEdge();
 }

// Function to set RGB color (values from 0-255)
// Note: Values are inverted for common anode
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, 255 - red);     // Invert value for common anode
  analogWrite(GREEN_PIN, 255 - green); // Invert value for common anode
  analogWrite(BLUE_PIN, 255 - blue);   // Invert value for common anode
}

// Creates a rainbow effect
void rainbowEffect(int wait) {

  for(int i = 0; i < 256; i++) {
    // Red to Yellow
    setColor(255, i, 0);
    delay(wait);
  }
  
  for(int i = 0; i < 256; i++) {
    // Yellow to Green
    setColor(255 - i, 255, 0);
    delay(wait);
  }
  
  for(int i = 0; i < 256; i++) {
    // Green to Cyan
    setColor(0, 255, i);
    delay(wait);
  }
  
  for(int i = 0; i < 256; i++) {
    // Cyan to Blue
    setColor(0, 255 - i, 255);
    delay(wait);
  }
  
  for(int i = 0; i < 256; i++) {
    // Blue to Magenta
    setColor(i, 0, 255);
    delay(wait);
  }
  
  for(int i = 0; i < 256; i++) {
    // Magenta to Red
    setColor(255, 0, 255 - i);
    delay(wait);
  }
}

void testEdge() {
  for(int i = 256; i > 0; i--) {
    setColor(i, 0, 0);
    delay(1000);
    i -= 9;
    if(i <0) {
      break;
    }
    currValue = i;
    Serial.println(currValue);
  }
}
