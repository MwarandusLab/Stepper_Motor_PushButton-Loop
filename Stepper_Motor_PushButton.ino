#include <AccelStepper.h>

const int ledPin = 28;

const int stepsPerRevolution = 200;

#define stepPin 2
#define dirPin 5
#define buttonPin1 51
#define buttonPin2 53

int ledState = LOW;
bool button1Pressed = false;
bool button2Pressed = false;

// Create an instance of the AccelStepper class
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Set the maximum speed and acceleration of the stepper motor
  stepper.setMaxSpeed(1000);      // Adjust the maximum speed as needed
  stepper.setAcceleration(500);   // Adjust the acceleration as needed
  
  stepper.setCurrentPosition(0);

  stepper.setPinsInverted(true);
}

void loop() {
  // Button 1 pressed
  if (digitalRead(buttonPin1) == LOW && !button1Pressed) {
    button1Pressed = true;
    if (ledState == LOW) {
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
      // Calculate the number of steps for a 90-degree rotation (with full stepping)
    }
  }else if (digitalRead(buttonPin1) == HIGH && button1Pressed) {
    button1Pressed = false;
  }
  
  // Button 2 pressed
  if (digitalRead(buttonPin2) == LOW && !button2Pressed) {
    button2Pressed = true;
    if (ledState == HIGH) {
      ledState = LOW;
      digitalWrite(ledPin, ledState);
      
    }
  }
  else if (digitalRead(buttonPin2) == HIGH && button2Pressed) {
    button2Pressed = false;
  }

  if(digitalRead(ledPin) == HIGH){
    int steps = (90 * stepsPerRevolution) / 360;

      // Rotate the stepper motor 90 degrees in one direction
    stepper.move(-steps);
    
    // Wait until the stepper motor reaches the target position
    while (stepper.distanceToGo() != 0) {
      stepper.runSpeedToPosition();
    }

    // Pause for 5 seconds
    delay(5000);
  }else if(digitalRead(ledPin) == LOW){
    int steps = (162 * stepsPerRevolution) / 360;

      // Rotate the stepper motor 90 degrees in one direction
    stepper.move(steps);
    
    // Wait until the stepper motor reaches the target position
    while (stepper.distanceToGo() != 0) {
      stepper.runSpeedToPosition();
    }

    // Pause for 5 seconds
    delay(5000);
  }
}
