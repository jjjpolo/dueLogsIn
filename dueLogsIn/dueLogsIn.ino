/*
  Name: dueLogsIn.ino

  Description:
  Emulates a USB Keyboard attached to the PC and logs into a Windows session 
  without any human intervention.

  It also performs some other custom additional steps such as open software 
  and minimize all the applications running.

  The circuit:
  This firmware does not need any special connection.
  Just plug it into a USB port of a PC running Windows with the user account
  that you want to log into.

  Created: 2021-05-02
    By José: Juan Jaramillo Polo.
  Modified: 2021-11-07
    By: José Juan Jaramillo Polo
*/

#include "Keyboard.h"

const String password = "Type your password here";
const int notificationLED = 17;
const int buttonPin = 2;

/*
   Runs once at boot up to configure the device
*/
void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  pinMode(notificationLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

/*
  Toggle LED function
  @param pin: pin number of the LED
*/
void toggleLED(int pin) {
  digitalWrite(pin, !digitalRead(pin)); // Toggle the state of the LED
}

/*
  Infinite loop that does the main job.
*/
void loop() {
  int state = 1;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;
  long interval = 500;
  unsigned long blinkCounter = 0;
  unsigned long maxBlinkEvents = 240;  // 2min if interval == 500
  
  Serial.println("State 1 blinking led...");
  
  while (true) {
    switch (state) {
      case 1:  // Idle state with animation, interruption button active.

        // Blink time control
        currentMillis = millis();
        if ((currentMillis - previousMillis) >= interval) {
          previousMillis = currentMillis;
          toggleLED(notificationLED);
          ++blinkCounter;
        }

        // Event counter detection
        if (blinkCounter >= maxBlinkEvents) {
          digitalWrite(notificationLED, LOW);
          state = 2;
          blinkCounter = 0;
          maxBlinkEvents = 20;  // In the next state we only want 10 secs of execution.
          Serial.println("State 2 pressing key-up...");
        }

        // Cancel interruption.
        if (digitalRead(buttonPin) == LOW) {
          state = 5;
        }
        break;

      case 2:  // Key-up pressing while external button interruption enabled.

        // key press every certain secs
        currentMillis = millis();
        if ((currentMillis - previousMillis) >= interval) {
          previousMillis = currentMillis;
          Keyboard.press(KEY_UP_ARROW);
          delay(1);  //3s delay
          Keyboard.releaseAll();
          ++blinkCounter;
        }

        // Event counter detection
        if (blinkCounter >= maxBlinkEvents) {
          digitalWrite(notificationLED, LOW);
          state = 3;
          //blinkCounter = 0;
          //maxBlinkEvents = 10;  // In the next state we only want 10 secs of execution.
        }

        // Cancel interruption.
        if (digitalRead(buttonPin) == LOW) {
          state = 5;
        }
        break;

      case 3:
        Serial.println("State 3 Logging in...");
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(3000);
        Keyboard.println(password);
        delay(3000); 
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        state = 4;
        break;

      case 4:
        digitalWrite(notificationLED, HIGH);
        Serial.println("Done...");
        while (true) {
          delay(1);
        }
        break;

      case 5:
        digitalWrite(notificationLED, LOW);
        Serial.println("Cancelled...");
        while (true) {
          delay(1);
        }
        break;
    }
  }
}
