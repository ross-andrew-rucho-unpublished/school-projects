//          oled_2015_a.c      RGD 9/1/2015
//
//
// 
//
//  Use PCM 14 bit compiler
//  Circuit configuration:
//  Internal Oscillator with I/O on RA6 and RA7, osc speed = 4 MHz, 1 us instruction cycle

//  NOTE: the ASCII representation of the PIC16F1829 will look correct in the PICC text editor

//                             ^ = ENABLE INTERNAL PULL-UP RESISTOR
/*                                                      PIC16F1829  20SOIC Pinout:
                                                       _____________   _____________
                                                      |            [___]            |
                                              +++   1-| +5V Regulated           GND |-20 ---
                                                      |                             |
                                           nc <<<   2-| RA5         DAC,PGD,RA0,AN0^|-19 >>> PGD
                                                      |                             |  
                                           nc <<<   3-| RA4,AN3         PGC,RA1,AN1^|-18 >>> PGC
                                                      |                             |
                                       /MCLR  >>>   4-| /MCLR,RA3           RA2,AN2 |-17 >>> GREEN LED OUT
                                                      |                             |  
                                           nc <<<   5-| RC5                     RC0 |-16 >>> nc
                                                      |                             |
                                           nc <<<   6-| RC4                     RC1 |-15 >>> nc
                                                      |                             | 
                                           nc <<<   7-| RC3                     RC2 |-14 >>> OLED SA0 -- I2C address for OLED,set output = HIGH (= 1) or IGNORE
                                                      |                             |  
                                           nc <<<   8-| RC6                     RB4 |-13 >>> OLED I2C SDA
                                                      |                             |
                                           nc <<<   9-| RC7                     RB5 |-12 >>> OLED RES#
                                                      |                             |  
                                           nc <<<  10-| RB7                     RB6 |-11 >>> OLED I2C SCK
                                                      |_____________________________|

OLED Module  LM096-128064   (OLED = organic LED)

Pinout using the OLED adapter PCB:

green wire =  ground on PCB            - connect to ground on PCB
yellow wire = +5V on PCB               - connect to +5volts on PCB
blue wire =   OLED SDA (serial data)   - connect to microcontroller pin 13 (RB4)
violet wire = OLED SCK (serial clock)  - connect to microcontroller pin 11 (RB6)
brown wire =  OLED RES# (reset)        - connect to microcontroller pin 12 (RB5)

headers:  USE SPRING PIN TERMINAL ON pcb

OLD configuration:

Pinout and connections for the ORIGINAL OLED MODULE
Pin # - Connection
 1 - +5 volts
 2 - Ground
 3 - Ground
 4 - RB5 (OLED RES#)
 5 - RC2 (OLED SA0)
 6 - Ground
 7 - Ground
 8 - RB6 (OLED I2C SCL)
 9 - RB4 (OLED I2C SDA)
10 - no connection (nc)
11 - Ground
12 - Ground
13 - Ground
14 - Ground
15 - Ground
16 - no connection (nc)

HEADERS: (use double row 16 pin headers: 2 x 8 pins)
use the MALE 16-pin header on the OLED display with the pins pointing downward, on the back of the OLED display panel
Place the FEMALE header on your PC board and connect to your uC as shown above, and be sure to mark Pin #1

*/

#include <16F1829.H>
#device ADC=10                      // Preprocessor directive to define the size of the ADC return value
#use delay (clock=800000)           // 800 KHz, 5 us instruction cycle

#fuses WDT, INTRC_IO, PUT     // internal oscillator operation with RA6 and RA7 as digital I/O, ref 16F1829.h, enable Power Up Timer
#fuses NOMCLR                 // disable /MCLR pin
#fuses NOPROTECT              // disable code protection
// #fuses NOLVP

// Low power configurations
#BIT OPTION_REG_WPUEN=getenv("SFR:OPTION_REG").7  // OPTION_REG: global register options !WPUEN bit 

// Port A
#BYTE TRISA_reg=getenv("SFR:TRISA")  // TRISA: Port A TRI-state register all set to 1 (configured as inputs)
#BYTE ANSELA_reg=getenv("SFR:ANSELA")  // ANSELA: Port A analog select register all set to 0 (configured as digital)
#BYTE WPUA_reg=getenv("SFR:WPUA")  // WPUA: Port A weak pull-up all set to 1 (pull-up enabled)
#BYTE INLVLA_reg=getenv("SFR:INLVLA")  // INLVLA: Port A input level control register all set to 1 (configured as ST)
#BYTE LATA_reg=getenv("SFR:LATA")  // LATA: Port A data latch register

// Port B
#BYTE TRISB_reg=getenv("SFR:TRISB")  // TRISB: Port B TRI-state register
#BYTE ANSELB_reg=getenv("SFR:ANSELB")  // ANSELB: Port B analog select register
#BYTE WPUB_reg=getenv("SFR:WPUB")  // WPUB: Port B weak pull-up
#BYTE INLVLB_reg=getenv("SFR:INLVLB")  // INLVLB: Port B input level control register
#BYTE LATB_reg=getenv("SFR:LATB")  // LATB: Port B data latch register

// Port C
#BYTE TRISC_reg=getenv("SFR:TRISC")  // TRISC: Port C TRI-state register
#BYTE ANSELC_reg=getenv("SFR:ANSELC")  // ANSELC: Port C analog select register
#BYTE WPUC_reg=getenv("SFR:WPUC")  // WPUC: Port C weak pull-up
#BYTE INLVLC_reg=getenv("SFR:INLVLC")  // INLVLC: Port C input level control register

#use rs232(baud=9600, xmit=PIN_C5, rcv=PIN_C4, stream=COM_MEM)

// Ross' definitions for PIC16F1829 for ADC setup and usage
#define ANALOG5 5
#define max_voltage 2.048   // define the maximum voltage to be Vss (This needs to be changed if the voltage range on the ADC changes)
#define num_states 1024     // Number of states for the given bit depth "ADC=8" (This needs to be changed if the bit depth changes

unsigned int16 externalTemp;  // 16 bit integer value for storing the ADC output from the external temperature pin
unsigned int32 totalTime=0;  // 32 bit integer value for counting the total number of elapsed time points

float tempE;             // floating point variable for external temperature
float AVG_tempE = 0;     // floating point variable for the average external temperature
float tempAVG_tempE;     // floating point variable for the average external temperature

///////////////////////////////////////
// SUBROUTINES

void init_ports(void) {
   // Initialize special function registers for I/O ports
   OPTION_REG_WPUEN = 0;
   
   TRISA_reg = 0b00111011;
   ANSELA_reg = 0b00000000;
   WPUA_reg = 0b00111011;
   INLVLA_reg = 0b00111111;
   LATA_reg = 0b00000000;
   
   TRISB_reg = 0b10100000;
   ANSELB_reg = 0b00000000;
   WPUB_reg = 0b10100000;
   INLVLB_reg = 0b11110000;
   LATB_reg = 0b00000000;
   
   TRISC_reg = 0b11011111;
   ANSELC_reg = 0b00000010;
   WPUC_reg = 0b11011101;
   INLVLC_reg = 0b11111101;

   SETUP_OSCILLATOR(OSC_8MHZ|OSC_INTRC);
   SETUP_WDT(WDT_8S);                        //  WDT set to 8 second period
   
   // Setup the ADC
   setup_adc(ADC_CLOCK_INTERNAL);            // ADC uses the internal clock
   setup_adc_ports(sAN5, VSS_FVR);           // ADC sets specific ports to ANALOG and specifies the range to be 0 V to FVR
   
   // Change ADC channel to read from channel 5
   set_adc_channel(ANALOG5);   // ADC reads from channel 5
   delay_ms(10);
   
   // Setup the reference voltage
   setup_vref(VREF_ON | VREF_ADC_2v048);     // FVR is turned on and set to ADC 2.048 V
}

///////////////////////////////////////
// PIC12F1829 goes here at RESET

void main()
{
init_ports();                 //  Initialize ports
restart_wdt();
delay_ms(50);                 //  insert a short delay before starting the system up

fprintf(COM_MEM, "BMME 580");
fputs("", COM_MEM);  // Adds a reliable carriage return for OpenLog data streams
fprintf(COM_MEM, "Ross Rucho");
fputs("", COM_MEM);  // Adds a reliable carriage return for OpenLog data streams
fprintf(COM_MEM, "Data Logging from PIC16F1829 to SparkFun OpenLog");
fputs("", COM_MEM);  // Adds a reliable carriage return for OpenLog data streams
   
CYCLE:

while(true)
{
  // Increment total time
  totalTime = totalTime + 1;
  
  // Read from the ADC
  externalTemp = read_adc();
  
  // Calculate analog external temperature in fahrenheit
  tempE = (externalTemp*(max_voltage/(num_states-1)))*100;  // This calculation includes the conversion from analog voltage to temperature for the LM34DZ temperature sensor
  AVG_tempE = AVG_tempE + tempE;
  tempAVG_tempE = AVG_tempE/totalTime;
  
  // Write the analog voltage to external memory
  fprintf(COM_MEM, "%2.3f", tempE);
  fputs("", COM_MEM);  // Adds a reliable carriage return for OpenLog data streams
  
  restart_wdt();
  
  #use delay (clock=32000)           // 32 KHz
  delay_ms(1000);
  #use delay (clock=800000)           // 800 KHz, 5 us instruction cycle
}
  
restart_wdt();
      
goto CYCLE;  //  cycle indefinitely until battery is removed or battery runs out of power
} // main

