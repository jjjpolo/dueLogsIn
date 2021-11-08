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

String password = "DemoPassword";
int notificationLED = LED_BUILTIN;

/*
   Runs once at boot up to configure the device
*/
void setup()
{
  Serial.begin(115200);
  Keyboard.begin();
  pinMode(notificationLED, OUTPUT);
}

/*
  Blinks an LED (only one cycle) with a custom delay received by argument.

  @param ledPin: Pin number of the LED.
  @param delayInMs: Delay in ms of the high and low state.
*/
void blinkLED(int ledPin, int delayInMs)
{
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delayInMs);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(delayInMs);
}

/*
   Delays for a certain number of minutes pressing a key every second.

   Additionally, it performs an LED animation using the notificationLED
   to let the user knows that the device is working.

   @param n: The number of minutes that the device will be paused.
   @param key: The key that the device will be emulating (pressing) every minute.
*/
void delayMinutesPressingKey(int n, int keyToBePressed)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 60; j++)
    {
      blinkLED(notificationLED, 500);
      Keyboard.press(keyToBePressed);
      Keyboard.releaseAll();
    }
  }
}

/*
   Waits for a certain number of minutes performing an LED animation every second
   using the notificationLED to let the user that the device is working.

   @param n: The number of minutes that the device will be paused.
*/
void delayMinutes(int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 60; j++)
    {
      blinkLED(notificationLED, 500);
    }
  }
}

/*
  Performs a boot animation using a certain pin that has an LED connected.

  @param ledPin: Pin number of the LED.
*/
void bootAnimation(int ledPin)
{
  for (int i = 0; i < 5; ++i)
  {
    blinkLED(ledPin, 150);
  }
  Serial.println("Starting system...");
}

/*
   Infinite loop that does the main job.
*/
void loop()
{
  bootAnimation(notificationLED);

  /*
    Delaying 5 minutes and 10 seconds (pressing a key that should not hurt) to
    let the system (Windows) gets started.
    This delay has been considered to be big in case there is any update running.
    In case there isn't any updating process running a delay, pressing a key every minute,
    will prevent the PC goes to sleep.
  */
  Serial.println("Waiting a few minutes in case there is any update running...");
  delay(10000); // 10s delay to let the booting process (BIOS) gets done.
  delayMinutesPressingKey(5, KEY_BACKSPACE);

  //Press arrow up key to make widows asks for the user password.
  Serial.println("Pressing the up arrow key to start the logging process...");
  Keyboard.press(KEY_UP_ARROW);
  Keyboard.releaseAll();
  delay(3000); //3s delay

  /*
    Types the password for the default user.
    'password' is a global variable to make this firmware as customizable
    as possible so that the user can updates it easily.

    TODO:
    Look for a way to make the password be changed easier. Keep in mind that
    Arduino Due has not EEPROM so maybe the following github repo could be a solution:
    https://github.com/sebnil/DueFlashStorage
  */
  Serial.println("Logging in...");
  Keyboard.println(password);
  delay(30000); // 30s delay

  // Once the session has started it will send a key combination to start an application.
  Serial.println("Starting an specific application...");
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('9');
  Keyboard.releaseAll();
  delay(30000); // 30s delay

  // Once we have all the needed software started send win+D to show the desktop (minimize all).
  Serial.println("Minimizing all of the applications...");
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  Keyboard.releaseAll();

  // The system is ready, so the device will be blocked infinitely from now.
  Serial.println("Done!");
  while (true)
  {
    delay(1);
  }
}
