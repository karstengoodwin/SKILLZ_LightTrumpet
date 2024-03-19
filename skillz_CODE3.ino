// This code 3 is for SKILLZ light Trumpet workshop. button1 button2 and button3 presses
//and combination presses are mapped to musical notes to replicate a digital trumpet and
//we have a LDR to modulate the note to give each press a little personalization.
// we will be making a state machine to organize our code and add a linear pot to
//the device to slide our notes high and low

// INSTANTATION --> where we collect the elements we need for the equipement and code to work together

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

void setup() {         // this is where we start to identify all the elements we need through out the code
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

  // frequencies to notes for each button
  int baseFreq1 = 493;  //B4
  int baseFreq2 = 440;  //A4
  int baseFreq3 = 392;  //G4
  int baseFreq4 = 349;  //F4
  int baseFreq5 = 329;  //E4
  int baseFreq6 = 293;  //D4
  int baseFreq7 = 261;  //C4

  // Modification of the base frequencies with the linear potentiometer value
  int modFreq1 = baseFreq1 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the B4 note in the positive and negtative direction
  int modFreq2 = baseFreq2 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the A4 note in the positive and negtative direction
  int modFreq3 = baseFreq3 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the G4 note in the positive and negtative direction
  int modFreq4 = baseFreq4 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the F4 note in the positive and negtative direction
  int modFreq5 = baseFreq5 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the E4 note in the positive and negtative direction
  int modFreq6 = baseFreq6 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the D4 note in the positive and negtative direction
  int modFreq7 = baseFreq7 + map(potValue, 0, 1023, -50, 50);  // linear pot will slide the C4 note in the positive and negtative direction


  // Set tone on button pressed linear pot slides the note up and down

  if (button1State && !button2State && !button3State) {
    tone(buzzerPin, modFreq1 + ldrAdjustment);  // button 1 pressed _ T T -->   B4 493 baseFreq1
    Serial.println("button1 pressed! note B4");

  } else if (!button1State && button2State && !button3State) {  // button 2 pressed T _ T --> A4 440 baseFreq2
    tone(buzzerPin, modFreq2 + ldrAdjustment);
    Serial.println("button2 pressed! note A4");

  } else if (!button1State && !button2State && button3State) {  //button 3 pressed T T _ --> G4 392 baseFreq3
    tone(buzzerPin, modFreq3 + ldrAdjustment);
    Serial.println("button3 pressed! note G4");

  } else if (!button1State && button2State && button3State) {  //buttons 2 and 3 pressed T _ _ --> F4 349 baseFreq4
    tone(buzzerPin, modFreq4 + ldrAdjustment);
    Serial.println("button2 and 3 pressed! note F4");

  } else if (button1State && button2State && !button3State) {  //buttons 1 and 2 pressed _ _ T --> D4 293 baseFreq5
    tone(buzzerPin, modFreq5 + ldrAdjustment);
    Serial.println("button1 and 2 pressed! note D4");

  } else if (button1State && !button2State && button3State) {  //buttons 1 and 3 pressed _ T _ --> E4 329 baseFreq6
    tone(buzzerPin, modFreq6 + ldrAdjustment);
    Serial.println("button1 and 3 pressed! note E4");

  } else if (button1State && button2State && button3State) {  //all buttons pressed _ _ _ --> C4 261 baseFreq7
    tone(buzzerPin, modFreq7 + ldrAdjustment);
    Serial.println("all buttons pressed! note C4");

  } else {
    noTone(buzzerPin);  // No buttons pressed T T T --> no sound
    Serial.println("No buttons pressed");
  }
  delay(10);  // Short delay for stability
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
