// This code 2 is for SKILLZ light Trumpet workshop. button1 button2 and button3 presses 
//and combination presses are mapped to musical notes to replicate a digital trumpet and 
//we have a LDR to modulate the note to give each press a little personalization.
// We will be making a function at the bottom of the code for calibrating the LDR 
//so it gives us a baseline for the light value once we start the device up


// INSTANTATION --> where we collect the elements we need for the equipement and code to work together
// Pin definitions
const int buzzerPin = 10;  // Buzzer connected to digital pin 10
const int button1Pin = 2;  // Button 1 connected to digital pin 2
const int button2Pin = 3;  // Button 2 connected to digital pin 3
const int button3Pin = 4;  // Button 3 connected to digital pin 4


// LDR pin set to an analog pin 
int ldrPin = A0;
int ldrBaseline; //baseline value for the ldr
bool isCalibrated = false; //flagging that the calibration needs to take place for the ldr

void setup() {
  Serial.begin(9600);
  // Initialize pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  //start calibration process for the LDR
  calibrateLDR();
}

void loop() {
// check the calibration process is sucessful
if (!isCalibrated){
  Serial.println("LDR calibrated!");
  // If not calibrated, skip the rest of the loop and do it again
  return;
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
  int ldrAdjustment = ldrValue -ldrBaseline;

  // frequencies to notes for each button
  int baseFreq1 = 493;  //B4
  int baseFreq2 = 440;  //A4
  int baseFreq3 = 392;  //G4
  int baseFreq4 = 349;  //F4
  int baseFreq5 = 329;  //E4
  int baseFreq6 = 293;  //D4
  int baseFreq7 = 261;  //C4


  // Set tone on button pressed 
  if (button1State && !button2State && !button3State) {  // button 1 pressed _ T T -->   B4 493 baseFreq1
    tone(buzzerPin, baseFreq1 + ldrAdjustment);
    Serial.println("button1 pressed! note B4");

  } else if (!button1State && button2State && !button3State) {  // button 2 pressed T _ T --> A4 440 baseFreq2
    tone(buzzerPin, baseFreq2 + ldrAdjustment);
    Serial.println("button2 pressed! note A4");

  } else if (!button1State && !button2State && button3State) {  //button 3 pressed T T _ --> G4 392 baseFreq3
    tone(buzzerPin, baseFreq3 + ldrAdjustment);
    Serial.println("button3 pressed! note G4");

  } else if (!button1State && button2State && button3State) {  //buttons 2 and 3 pressed T _ _ --> F4 349 baseFreq4
    tone(buzzerPin, baseFreq4 + ldrAdjustment);
    Serial.println("button2 and 3 pressed! note F4");

  } else if (button1State && button2State && !button3State) {  //buttons 1 and 2 pressed _ _ T --> D4 293 baseFreq5
    tone(buzzerPin, baseFreq5 + ldrAdjustment);
    Serial.println("button1 and 2 pressed! note D4");


  } else if (button1State && !button2State && button3State) {  //buttons 1 and 3 pressed _ T _ --> E4 329 baseFreq6
    tone(buzzerPin, baseFreq6 + ldrAdjustment);
    Serial.println("button1 and 3 pressed! note E4");

  } else if (button1State && button2State && button3State) {  //all buttons pressed _ _ _ --> C4 261 baseFreq7
    tone(buzzerPin, baseFreq7 + ldrAdjustment);
    Serial.println("all buttons pressed! note C4");

  } else {
    noTone(buzzerPin); // No buttons pressed T T T --> no sound
    Serial.println("No buttons pressed");
  }
  delay(10);      // Short delay for stability
}


// This is our function for calibrating the LDR 

void calibrateLDR(){
  long total = 0;
  const int calibrationReadings = 100;

  //Indicate calibartion start
  Serial.println("LDR calibration begin");

//Take multiple readings
for( int i =0; i< calibrationReadings; i ++) {
  total += analogRead(ldrPin);
  delay(10);
}

// Calculate the average
ldrBaseline = total / calibrationReadings;

//Mark calibartion as done
isCalibrated = true;

}

