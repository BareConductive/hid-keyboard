/*******************************************************************************

 Bare Conductive HID keyboard demo
 ---------------------------------
 
 HID_Keyboard.ino - simple MPR121 touch detection to faked keyboard output
 
 Bare Conductive code written by Stefan Dzisiewski-Smith and Peter Krige.
 
 This work is licensed under a MIT license https://opensource.org/licenses/MIT
 
 Copyright (c) 2016, Bare Conductive
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

// compiler error handling
#include "Compiler_Errors.h"

// touch  includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

#include <Keyboard.h>

// these keys map from E0 to E11 on the Touch Board - in GarageBand they map to a 
// full chromatic scale (like a piano) from C to C - you can replace them with any
// keys you like - they don't even have to be letters
//
// take a look at http://arduino.cc/en/Reference/KeyboardModifiers for more keys
const char keyMap[12] = {'J', 'U', 'H', 'Y', 'G', 'T', 'F', 'D', 'E', 'S', 'W', 'A'};
//const char keyMap[12] = {KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW, ' ', KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_PAGE_UP, KEY_PAGE_DOWN};

#define holdKey true  // set this to false if you want to have a single quick keystroke
                      // true means the key is pressed and released when you press and release the electrode respectively

// touch behaviour definitions
#define firstPin 0
#define lastPin 11

// define LED_BUILTIN for older versions of Arduino
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

void setup(){ 
  Serial.begin(57600);
  
  pinMode(LED_BUILTIN, OUTPUT);
   
  //while (!Serial) ; {} //uncomment when using the serial monitor 
  Serial.println("Bare Conductive HID keyboard demo");

  if(!MPR121.begin(MPR121_ADDR)){ 
    Serial.println("error setting up MPR121");  
    switch(MPR121.getError()){
      case NO_ERROR:
        Serial.println("no error");
        break;  
      case ADDRESS_UNKNOWN:
        Serial.println("incorrect address");
        break;
      case READBACK_FAIL:
        Serial.println("readback failure");
        break;
      case OVERCURRENT_FLAG:
        Serial.println("overcurrent on REXT pin");
        break;      
      case OUT_OF_RANGE:
        Serial.println("electrode out of range");
        break;
      case NOT_INITED:
        Serial.println("not initialised");
        break;
      default:
        Serial.println("unknown error");
        break;      
    }
    while(1);
  }
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(40);    // lower numbers make the board more sensitive
  MPR121.setReleaseThreshold(20);  // make sure that the release threshold is always 
                                   // lower than the touch threshold

  MPR121.updateAll();
  
  Keyboard.begin();
}

void loop(){
  // this is where we do all the real work
  // only do anything if the overall touch status has changed
  if(MPR121.touchStatusChanged()){
    // update our touch data to ensure it is valid
    MPR121.updateTouchData();  
      // run through all electrodes
      for(int i=firstPin; i<=lastPin; i++){
        if(MPR121.isNewTouch(i)){
          // if we have a new touch on this electrode...
          // turn the onboard LED on, and press
          // the appropriate key on the "keyboard" output
          digitalWrite(LED_BUILTIN, HIGH);
          Keyboard.press(keyMap[i]);
          // if we don't want to hold the key, immediately release it
          if(!holdKey) Keyboard.release(keyMap[i]);
        } else if(MPR121.isNewRelease(i)){
          // if we have a new release and we were holding a key, release it 
          if(holdKey) Keyboard.release(keyMap[i]);
          // turn the onboard LED off
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
  }
