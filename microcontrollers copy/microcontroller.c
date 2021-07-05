#include <18f1320.h>
#fuses INTRC_IO,NOLVP,NOWDT,PUT
#use delay (clock=4000000)

#define GREEN_LED PIN_A3
#define YELLOW_LED PIN_B0
#define RED_LED PIN_B1

#define TOP_LEFT_N PIN_A4
#define TOP_RIGHT_N PIN_A0
#define BOTTOM_LEFT_N PIN_A2
#define BOTTOM_MID_N PIN_B3
#define BOTTOM_RIGHT_N PIN_A1

void runForward(int16 time) {
   int16 counter = 0;
   while(counter < 500) {
      Output_high(TOP_LEFT_N);
      Output_high(BOTTOM_RIGHT_N);
      Output_high(BOTTOM_MID_N);
      Output_low(TOP_RIGHT_N);
      Output_low(BOTTOM_LEFT_N);
      Delay_ms(time);
      Output_low(BOTTOM_MID_N);
      Delay_ms(10 - time);
      counter = counter + 1;
   }
}

void runBackward(int16 time) {
   int16 counter = 0;
   while(counter < 500) {
      Output_high(TOP_RIGHT_N);
      Output_high(BOTTOM_LEFT_N);
      Output_high(BOTTOM_MID_N);
      Output_low(TOP_LEFT_N);
      Output_low(BOTTOM_RIGHT_N);
      Delay_ms(time);
      Output_low(BOTTOM_MID_N);
      Delay_ms(10 - time);
      counter = counter + 1;
   }
}

void electronicStop(int16 time) {
   Output_high(BOTTOM_LEFT_N);
   Output_high(BOTTOM_MID_N);
   Output_high(BOTTOM_RIGHT_N);
   Delay_ms(time);
   Output_low(BOTTOM_LEFT_N);
   Output_low(BOTTOM_MID_N);
   Output_low(BOTTOM_RIGHT_N);
}

void main() {
   // Local variable Declarations
   Int Reading;
   int ONE_FOURTH = 63.75;
   int TWO_FOURTH = 127.5;
   int THREE_FOURTH = 191.25;
   
   // Setup for the Analog to Digital Converter
   Setup_adc_ports(sAN6);
   Setup_adc(ADC_CLOCK_INTERNAL);
   Set_adc_channel(6); 
   
   // Main Loop
   while(TRUE) {
      reading = read_adc();
      
      If(reading < ONE_FOURTH) {
         Output_low(GREEN_LED);
         runForward(2.5);
         Output_low(TOP_LEFT_N);
         Output_low(BOTTOM_RIGHT_N);
         electronicStop(2000);
         Output_high(GREEN_LED);
      }Else if(reading < TWO_FOURTH) {
         Output_low(GREEN_LED);
         Output_low(YELLOW_LED);
         runForward(5);
         Output_low(TOP_LEFT_N);
         Output_low(BOTTOM_RIGHT_N);
         electronicStop(2000);
         Output_high(GREEN_LED);
         Output_high(YELLOW_LED);
      }Else if(reading < THREE_FOURTH) {
         Output_low(YELLOW_LED);
         Output_low(RED_LED);
         runForward(7.5);
         Output_low(TOP_LEFT_N);
         Output_low(BOTTOM_RIGHT_N);
         electronicStop(2000);
         Output_high(YELLOW_LED);
         Output_high(RED_LED);
      }Else {
         Output_low(RED_LED);
         runForward(10);
         Output_low(TOP_LEFT_N);
         Output_low(BOTTOM_RIGHT_N);
         electronicStop(2000);
         Output_high(RED_LED);
      }
      
      reading = read_adc();
      
      If(reading < ONE_FOURTH) {
         Output_low(GREEN_LED);
         runBackward(2.5);
         Output_low(TOP_RIGHT_N);
         Output_low(BOTTOM_LEFT_N);
         electronicStop(1000);
         Output_high(GREEN_LED);
      }Else if(reading < TWO_FOURTH) {
         Output_low(GREEN_LED);
         Output_low(YELLOW_LED);
         runBackward(5);
         Output_low(TOP_RIGHT_N);
         Output_low(BOTTOM_LEFT_N);
         electronicStop(1000);
         Output_high(GREEN_LED);
         Output_high(YELLOW_LED);
      }Else if(reading < THREE_FOURTH) {
         Output_low(YELLOW_LED);
         Output_low(RED_LED);
         runBackward(7.5);
         Output_low(TOP_RIGHT_N);
         Output_low(BOTTOM_LEFT_N);
         electronicStop(1000);
         Output_high(YELLOW_LED);
         Output_high(RED_LED);
      }Else {
         Output_low(RED_LED);
         runBackward(10);
         Output_low(TOP_RIGHT_N);
         Output_low(BOTTOM_LEFT_N);
         electronicStop(1000);
         Output_high(RED_LED);
      }
   }
}
