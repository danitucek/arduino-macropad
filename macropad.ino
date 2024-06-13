#include <Keyboard.h>

//pins declaration, 3x buttons, 1x LED
const int switch1 = 14;
const int switch2 = 15;
const int switch3 = 16;
const int activityLED = 10;

//set the keypress repeat delay is ms to simulate human interaction
int repDelay = 200;

//declare strings for easy manipulation in code (example: various login forms for different servers)
char dell[] = "yourlogin@dellserver"; 
char hp[] = "hpserver\\yourlogin"; 
char text[] = ""; 

void setup() {
  //set the correct pin usage
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(activityLED, OUTPUT);

  //initialize the USB keyboard library
  Keyboard.begin();
}

//REMEMBER: INPUT_PULLUP has reverse logic, therefore we are waiting for a logical 0 to take action
void loop() {
  if (!digitalRead(switch1)) { 		//first key pressed,
    Keyboard.print(dell);	   		//print the string from above,
    digitalWrite(activityLED,HIGH);	//turn on the activity LED,
    delay(repDelay);				//wait a little so you macropad won't repeat itself multiple times
    Keyboard.releaseAll();			//don't forget to release any keys
    digitalWrite(activityLED,LOW);	//activity LED off
  } 

  if (!digitalRead(switch2)) {		//same for second key
    Keyboard.print(hp);
    digitalWrite(activityLED,HIGH);
    delay(repDelay);
    Keyboard.releaseAll();
    digitalWrite(activityLED,LOW);
  } 

  if (!digitalRead(switch3)) {		//third key pressed for Windows lock
    Keyboard.press(KEY_LEFT_GUI);	//the left WIN key
    Keyboard.print("l");			//the letter l
    digitalWrite(activityLED,HIGH);
    delay(repDelay);
    Keyboard.releaseAll();
    digitalWrite(activityLED,LOW);
  } 
}
