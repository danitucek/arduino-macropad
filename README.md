# Simple Arduino macropad 

I work as a system engineer, I have admin credentials via Active Directory to use with every server I need to login. I just enter my credentials and I am allowed to diagnose and work on that particular server... Only if it was so easy and I wouldn't need to alter the login credentials for each type of server, whether it's a Dell, HP or a Supermicro.

Dell iDRACs use a form where you type in your credentials in an e-mail address manner: `your.login@domain`  
HP iLOs on the other hand anticipate them in a Windows manner: `domain\your.login`  
You get the point...

I started pulling my hair out after a while since I manage almost 1000 individual servers and typing in the correct form is tiresome. Therefore I created this little macropad which allows me to input my AD credentials in a correct for by the convenience of a single keypress.

## Hardware ##

Arduino is a convenient 8-bit MCU the suits as the brains of this project. I chose the Arduino Pro Micro as the base due to its design allowing it to be used as an emulated keyboard, therefore any computer (PC, Mac, Linux, ...) detects it as a standard keyboard, no need for drivers. The Atmega 32u4 is directly connected to the USB port and emulates the virtual keyboard. I used the version with Type-C USB connector for future proof convenience.

The physical part consists of simple pushbuttons set in INPUT_PULLUP mode so we don't have to use resistors, another great Arduino feature. In this first version I used 3 pushbuttons for three different actions:
- Key 1 -> type in login for iDRAC
- Key 2 -> type in login for iLO
- Key 3 -> a simple lock button that simulates pressing WIN+L
A simple red LED was added just for a visual feedback of the device functioning, this can be omitted completely or swapped for anything else with a cool factor (might add an OLED screen later with company logos when pressing the key).

## Software ##

I wanted to keep my code simple and easy to modify. The USB Keyboard library is available from Arduino and is included in the Arduino IDE. The code operates on observing the reverse logic of the pushbuttons, INPUT_PULLUP mode keeps an active HIGH (logical 1) internally on each pushbutton. When you press the button it shorts the digital pin to ground, creating an active LOW (logical 0). That's when we want to take action. Two of the three buttons input a string, this is done by `Keyboard.print("textHere")` (you can use `.println()` to apply and ENTER at the end). The third one is trickier since we want to use an exact hardware key and a letter, this is done by `Keyboard.press()` and `.print()`. Using `.press()` you must input the name (or hex/bin code) of your selected modifier key from the [Arduino Key Reference List](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/).

A simple delay is added after every keyboard action to eliminate the need of any hardware or software debouncing of the keypresses. For me about 200ms delay was fine for one press, change the `repDelay` variable to repeat faster or slower while holding. 
