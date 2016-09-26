#include <LedControl.h>

/*
    Copyright (c) 2016 Jeff Luszcz
    https://github.com/jeff-luszcz/Max72xx-Fire-Animation
    License: MIT
    
    Flames sketch for MAX72XX based 8x8 LED Matrix 
    
    This project needs LedControl to work (MIT license)
    See http://playground.arduino.cc/Main/LedControl
    Download and install manually or use the "Sketch->Include Library->Manage Libraries..." menu
    and search for LedControl and install, it should be available for your sketch then

  */

/*
  Create a LedControl
  ** Update the following pin numbers for your hardware **
  
  pin 12 is connected to the DataIn or DIN
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD or CS
  This project only supports a single Max72XX so pass in a "1"
*/
LedControl lc = LedControl(12, 11, 10, 1);

/* delayTime is used to control the speed of the flame's upward movement, lower number is faster
   On a Arduino Uni, a value of 5 gives a natural feeling
*/
unsigned long delaytime = 5;

// This byte array holds the initial values for the 8x8 matrix
// There are 8 rows of 8 LEDs each, bottom starting with the beginning of the array 
// We set the LEDs all off at first
// You can create a initial frame if desired B00000000 = all off, B11111111 = all on, B10101010 = every other LED on
byte eightByEightMatrix[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

}

/*
   The flames are created by randomly setting the 8 LEDs on the bottom row of the 8x8 matrix
   and them moving the line up to the next row on each call to makeFire
   In certain rows the LEDs are randomly tested to make some of them go out, just like in a real flame
   Also, the Intensity of the enture 8x8 matrix is flickered a couple times to give an additional feeling of flame

*/
void animateFire() {
    // copy each row up one row, randomly clearing some of the LEDs in rows 7,6,5,3
    // this gives a feeling of a natural fire
    eightByEightMatrix[7] = eightByEightMatrix[6] & random(0,255);
    eightByEightMatrix[6] = eightByEightMatrix[5] & random(0,255);
    eightByEightMatrix[5] = eightByEightMatrix[4] & random(0,255);
    eightByEightMatrix[4] = eightByEightMatrix[3] ;
    eightByEightMatrix[3] = eightByEightMatrix[2] & random(0,255);
    eightByEightMatrix[2] = eightByEightMatrix[1] ;
    eightByEightMatrix[1] = eightByEightMatrix[0];
    // start the flames by randomly turning on LEDs at the bottom row of the matrix
    eightByEightMatrix[0] = random(0, 255);

    // flicker the entire 8x8 matrix by changing the intensity of the matrix
    lc.setIntensity(0, 8);

    // set the LEDs based on the values found in the byte array
    lc.setRow(0, 0, eightByEightMatrix[0]);
    lc.setRow(0, 1, eightByEightMatrix[1]);
    lc.setRow(0, 2, eightByEightMatrix[2]);
    lc.setRow(0, 3, eightByEightMatrix[3]);
    delay(delaytime);

    // flicker the entire 8x8 matrix by changing the intensity of the matrix
    lc.setIntensity(0, 6);
    
    lc.setRow(0, 4, eightByEightMatrix[4]);
    lc.setRow(0, 5, eightByEightMatrix[5]);
    delay(delaytime);

    // flicker the entire 8x8 matrix by changing the intensity of the matrix
    lc.setIntensity(0, 3);
    
    lc.setRow(0, 6, eightByEightMatrix[6]);
    delay(delaytime);

    // flicker the entire 8x8 matrix by changing the intensity of the matrix
    lc.setIntensity(0, 1);
    
    lc.setRow(0, 7, eightByEightMatrix[7]);
    delay(delaytime);
}


void loop() {
  animateFire();

}
