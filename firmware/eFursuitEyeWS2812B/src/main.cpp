#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     5       // The pin connected to the LED strip data line
#define FAN_PIN     21      // The pin connected to the fan (negative side)
#define NUM_LEDS    21      // Number of LEDs in the strip
#define BRIGHTNESS  64      // LED brightness (0-255)
#define LED_TYPE    WS2812B // Type of LED strip
#define COLOR_ORDER GRB     // Color order of the LEDs
#define FAN_SPEED   255     // Fan speed (0-255, where 0 is full speed, 255 is off)

CRGB leds[NUM_LEDS];       // Define the array of LEDs

// Function declarations
void rainbow();
void fadeall();
void setupFan();
void controlFan(uint8_t speed);

void setup() {
    // Initialize FastLED
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    
    // Initialize fan control
    setupFan();
    
    // Initialize serial communication
    Serial.begin(115200);
    Serial.println("WS2812B LED Strip Demo with Fan Control");
}

void loop() {
    rainbow();              // Create a rainbow effect
    controlFan(FAN_SPEED); // Control fan at set speed
    delay(20);             // Small delay to control animation speed
}

void rainbow() {
    static uint8_t hue = 0;
    
    // Fill the LED array with a rainbow
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 255);
    }
    
    // Slowly change the base hue to create movement
    hue++;
    
    FastLED.show();
}

void fadeall() {
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i].nscale8(250); // Fade each LED by a small amount
    }
}

void setupFan() {
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, LOW); // Start with fan off (pin HIGH disconnects ground)
}

void controlFan(uint8_t speed) {
    // Invert the speed value since we're controlling ground
    // 255 (HIGH) = off, 0 (LOW) = full speed
    analogWrite(FAN_PIN, 255 - speed);
}