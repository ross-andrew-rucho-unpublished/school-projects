/*  This is template code that I generated that will accomplish the first objective of your first "Hello World" project.   You should be able to map this into your first draft of your source code, but please be sure to check your device (microcontroller) type and pin-out to make sure it is correct.
//          uC-test-1.c      RGD 7/14/2012//
//
//  First sample template program for the PIC16F1829 microcontroller for BMME580 class
//
//
//  Use PCM 14 bit compiler
//  Circuit configuration:
//  Internal Oscillator with I/O on PGM and PGD, osc speed = 4.0 MHz, 1 us instruction cycle

                                                                     PIC16F1829  8SOIC Pinout:
                                                          __________            __________
                                                         |                      [___]              |
                                    +5V power     1-   | +5V                       GND    |-20 - Ground
                                                         |                                  |
                                                            2-   | RA5           RA0,AN0,PGD,DAC    |-19  - Programming Port "PGD"
                                                         |                                  |
                                                            3-   | RA4, AN3          RA1,AN1,PGC    |-18  - Programming Port "PGC"
                                                         |                                  |
      Programming Port "/MCLR"    4-   | /MCLR, RA3      RA2,AN2,CCP3    |-17  - GREEN LED
                                                         |                                  |
          SD-Card module  Rxi  >>>    5-   | RC5, CCP1, Rx                       RC0    |-16 - potentiometer (analog INPUT)
                                                         |                                  |
           SD-Card module Txo <<<    6-   | RC4, Tx                           RC1    |-15
                                                         |                                  |
                                                           7-   | RC3, CCP2                         RC2    |-14 - OLED - SA0
                                                         |                                  |
                                                           8-   | RC6, CCP4                           RB4    |-13 - OLED - SDA
                                                         |                                  |
                                                           9-   | RC7                            RB5    |-12 - OLED - RES
                                                         |                                  |
                                                         10-   | RB7                            RB6    |-11 - OLED - SCL
                                                         |_________________________|
*/
//  SAMPLE SOURCE CODE from Bob Dennis
  
//  SIMPLE Hello World demonstration, with ability to flash an LED if the microcontroller is programmed properly

#include <16F1829.h>   //  you have to tell the compiler which microcontroller device you are programming
#include <MATH.H>      //  look in the PIC C User Manual to see what this library contains.  Do you need this?
#use delay (clock=4000000) //  4 MHz, 1 us instruction cycle, CHECK TIMING DELAYS!
#fuses INTRC_IO, NOWDT, NOMCLR, PUT  
            //  Set for internal oscillator operation with RA6 and RA7 as digital I/O,
            //  Disable the WDT.  Later setup WDT = 2048 ms WDT,  ref 16F1829.h to find syntax
            //  Disable the /MCLR pin so that it can be used as general I/O
            //  Enable the Power-Up Timer, allows power supply to stabilize at start-up

#define green_LED 98        //  RA2, a.k.a pin #17 on the PIC16F1829 device is in memory location 98
            //  the 16F1829.h file is where you find all of the pin locations in memory
             //  also note that RC0 (pin #17) has another function:  CCP3.  You will use this later.

///////////////////////////////////////
// SUBROUTINES,  Here is where you set up your I/O ports and other features of the microcontroller
//  This is where it is very handy to have a *.txt copy of the *.h file for the microcontroller:    16F1829.h

void init_ports(void) {
   SETUP_OSCILLATOR(OSC_4MHZ);  
         //  Look for this syntax in the *-h.txt file under  "Constants used in setup_oscillator() are:"
         //   also note that for this microcontroller the internal oscillator can be changed 
         //   on the fly as needed during program execution.   
}

///////////////////////////////////////
// PIC16F1829 goes here at RESET

void main() {
   init_ports();              //  Initialize ports

CYCLE:
   OUTPUT_BIT(green_LED, 1);      //  start by turning the green LED ON
      delay_ms(250);              //  delay for 250 ms, basically the microcontroller sits there doing nothing
   OUTPUT_BIT(green_LED, 0);      //  then turn the green LED OFF after 1/4 second delay
      delay_ms(250);              //  delay another 250 ms
goto CYCLE;                     //  execute this loop without stopping

} // main

