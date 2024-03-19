// This code 4 is for SKILLZ light Trumpet workshop. button1 button2 and button3 presses
//and combination presses are mapped to musical notes to replicate a digital trumpet and
//we have a LDR to modulate the note to give each press a little personalization.
// we will be making a state machine to organize our code and add a linear pot to
//the device to slide our notes high and we now also add a neopixel to
//the device to do different light colors when we play certian notes

// INSTANTATION --> where we collect the elements we need for the equipement and code to work together

// For the neo pixel to work we need to include the NeoPixel library
#include <Adafruit_NeoPixel.h>

// Pin definitions
const int buzzerPin = 10;  // Buzzer connected to digital pin 10
const int button1Pin = 2;  // Button 1 connected to digital pin 2
const int button2Pin = 3;  // Button 2 connected to digital pin 3
const int button3Pin = 4;  // Button 3 connected to digital pin 4

// LDR pin set to an analog pin
int ldrPin = A0;
int ldrBaseline;            //baseline value for the ldr
bool isCalibrated = false;  //flagging that the calibration needs to take place for the ldr

//setup for the linear slide to slide notes up and down
const int potPin = A1;

//Define the neopixel pin and the number of leds/pixels
const int neoPixelPin = 6;  // pin number
const int numPixels = 1;    // number of leds or pixels
Adafruit_NeoPixel pixels(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

void setup() {  // this is where we start to identify all the elements we need through out the code

  Serial.begin(9600);  // speed at which we are speaking to the serial monitor

  // Initialize pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  //start calibration process for the LDR
  calibrateLDR();

  // Initialize the potentiometer pin
  pinMode(potPin, INPUT);

  // Initialize NeoPixel Strip
  pixels.begin();
  pixels.show();  // Initialize all pixels to "off"
}

void loop() {  // tjis is where the code runs over and over and over.....

  if (!isCalibrated) {  // check the calibration process is sucessful
    Serial.println("LDR calibrated!");
  }

  // Read the state of the buttons
  int button1State = digitalRead(button1Pin) == LOW;
  int button2State = digitalRead(button2Pin) == LOW;
  int button3State = digitalRead(button3Pin) == LOW;

  // Read the value of the LDR
  int ldrValue = analogRead(ldrPin);
  Serial.print("ldrValue- ");
  Serial.println(ldrValue);

  // Calculate the LDR adjustment based on the baseline
  int ldrAdjustment = ldrValue - ldrBaseline;

  // read the value of the potentiometer
  int potValue = analogRead(potPin);

  //Setup for the LDR to adjust pixel brightness
  int brightness = map(ldrAdjustment, 500, 1023, 100, 255);  //map values from the LDR to the brightness of the neo pixel led
  pixels.setBrightness(brightness);                          // use the brightness mapping in the setBrightness function


  // frequencies to notes for each button
  int baseFreq1 = 493;  //B4
  int baseFreq2 = 440;  //A4
  int baseFreq3 = 392;  //G4
  int baseFreq4 = 349;  //F4
  int baseFreq5 = 329;  //E4
  int baseFreq6 = 293;  //D4
  int baseFreq7 = 261;  //C4

  // Modification of the base frequencies with the linear potentiometer value
  int modFreq1 = baseFreq1 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the B4 note by 50 in the positive and negtative direction
  int modFreq2 = baseFreq2 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the A4 note by 50 in the positive and negtative direction
  int modFreq3 = baseFreq3 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the G4 note by 50 in the positive and negtative direction
  int modFreq4 = baseFreq4 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the F4 note by 50 in the positive and negtative direction
  int modFreq5 = baseFreq5 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the E4 note by 50 in the positive and negtative direction
  int modFreq6 = baseFreq6 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the D4 note by 50 in the positive and negtative direction
  int modFreq7 = baseFreq7 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the C4 note by 50 in the positive and negtative direction


  // Set tone on button pressed and Set color for the tone pixel.Color is
  // where you sent the color  of the neo pixel = pixel.color(red,green,blue) or RGB

  if (button1State && !button2State && !button3State) {  // button 1 pressed _ T T -->   B4 493 baseFreq1
    tone(buzzerPin, modFreq1 + ldrAdjustment);
    pixels.setBrightness(brightness);                  // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));  //change the color to RED
    Serial.println("button1 pressed! note B4 Color is RED");

  } else if (!button1State && button2State && !button3State) {  // button 2 pressed T _ T --> A4 440 baseFreq2 Orange
    tone(buzzerPin, modFreq2 + ldrAdjustment);
    pixels.setBrightness(brightness);                   // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(255, 50, 0));  // Change color to Orange
    Serial.println("button2 pressed! note A4 Color is Orange");

  } else if (!button1State && !button2State && button3State) {  //button 3 pressed T T _ --> G4 392 baseFreq3 Yellow
    tone(buzzerPin, modFreq3 + ldrAdjustment);
    pixels.setBrightness(brightness);                    // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(150, 100, 0));  // Change color to yellow
    Serial.println("button3 pressed! note G4 Color is Yellow");

  } else if (!button1State && button2State && button3State) {  //buttons 2 and 3 pressed T _ _ --> F4 349 baseFreq4 Purple
    tone(buzzerPin, modFreq4 + ldrAdjustment);
    pixels.setBrightness(brightness);                    // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(255, 0, 255));  // Change color to Purple
    Serial.println("button2 and 3 pressed! note F4 Color is Purple");

  } else if (button1State && button2State && !button3State) {  //buttons 1 and 2 pressed _ _ T --> D4 293 baseFreq5 Green
    tone(buzzerPin, modFreq5 + ldrAdjustment);
    pixels.setBrightness(brightness);                  // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));  // Change color to Green
    Serial.println("button1 and 2 pressed! note D4 Color is Green");


  } else if (button1State && !button2State && button3State) {  //buttons 1 and 3 pressed _ T _ --> E4 329 baseFreq6 Torquiose
    tone(buzzerPin, modFreq6 + ldrAdjustment);
    pixels.setBrightness(brightness);                    // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(0, 100, 255));  // Change color to Torquiose
    Serial.println("button1 and 3 pressed! note E4 Color is Troquiose");

  } else if (button1State && button2State && button3State) {  //all buttons pressed _ _ _ --> C4 261 baseFreq7 Blue
    tone(buzzerPin, modFreq7 + ldrAdjustment);
    pixels.setBrightness(brightness);                  // changes the brightness of the pixel due to ldr mapping
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));  // Change color to Blue
    Serial.println("all buttons pressed! note C4 color is Blue");
  } else {
    noTone(buzzerPin);  // No buttons pressed T T T --> no sound
    pixels.clear();     // turns off the neo pixel
    Serial.println("No buttons pressed");
  }
  pixels.show();  //update the NeoPixel color to note that is played
  delay(10);      // Short delay for stability
}


// This is our function for calibrating the LDR

void calibrateLDR() {
  long total = 0;
  const int calibrationReadings = 100;

  //Indicate calibartion start
  Serial.println("LDR calibration begin");

  //Take multiple readings
  for (int i = 0; i < calibrationReadings; i++) {
    total += analogRead(ldrPin);
    delay(10);
  }

  // Calculate the average
  ldrBaseline = total / calibrationReadings;

  //Mark calibartion as done
  isCalibrated = true;
}
