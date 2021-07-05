/*
 * Ross Rucho
 * Start Date: 11/9/18
 * MDS main procedure
 */

// Imported libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <TimeLib.h>

// Imported local files
#include "MDSparam.h"
#include "Container.h"

/**Global Constants**/

// Device Setup constants
const char powerOnPrompt[] = "Enter the time";
const char getTime[] = "hours, then minutes";

// Start screen constants
const char greeting[] = "Hi! My name is MDS";
const char startPrompt1[] = "Press enter to start";

// Menu screen constants
const char container1[] = "Container 1      (1)";
const char container2[] = "Container 2      (2)";
const char container3[] = "Container 3      (3)";
const char dayRelease[] = "One-day release  (4)";

// Container state screen constants
const char label1[] = "Label            (1)";
const char prescription1[] = "Prescription     (2)";
const char back1[] = "Back             (3)";

// Container label screen constants
const char label2[] = "Medication Name:    ";
const char back2[] = "Back             (1)";

// Container prescription screen constants
const char prescription2[] = "Prescription Info:  ";

// Dispensing screen constants
const char dispensing[] = "     Dispensing     ";

// One-day Release constants
const char releaseMessage[] = "Choose a container: ";

// Confirm Release constants
const char releaseConfirmation[] = "Confirm release of  ";
const char confirmed[] = "Yes          (enter)";
const char denied[] = "No, go back      (1)";

// Global Variables
String date;
int HOUR;
int MINUTE;
int DAY;
int MONTH;
int YEAR;
int a[3];
char code[21];

int screenState = -1;
int contState = 0;
int motorState = 0;
int releaseState = 0;
unsigned long screenTime = 0;
int setupState = 0;
int prevScreenState = screenState;
bool buttonPushed = false;
bool leave = false;

// Initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Initialize container objects
  Container Container0 = Container();
  Container Container1 = Container();
  Container Container2 = Container();

/*****************************************************************************************************/
// Local Methods

// Device Setup
// Route device setup to proper logic

void deviceSetup() {
  if(setupState==0) {
    screenState = -2;
  }else if(setupState==1) {
    screenState = -3;
  }else if(setupState==2) {
    screenState = -3;
  }else if(setupState==3) {
    screenState = -3;
  }
}

// Setup current time
// Method to accept user input to
// set the current time

void currentTime() {
  lcd.setCursor(0,0);
  lcd.print("Enter the year:     ");
  lcd.setCursor(0,1);
  lcd.print("Format: (2018)      ");
  typeMode(code, 0);
  char buf[5];
  String(String(code[0]) +""+ String(code[1]) +""+ String(code[2]) +""+ String(code[3])).toCharArray(buf, 5);
  YEAR = atoi(buf);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter the month:    ");
  lcd.setCursor(0,1);
  lcd.print("Format: (02)        ");
  typeMode(code, 0);
  char buf2[3];
  String(String(code[0]) +""+ String(code[1])).toCharArray(buf2, 3);
  MONTH = atoi(buf2);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Enter the day:     ");
  lcd.setCursor(0,1);
  lcd.print("Format: (09)       ");
  typeMode(code, 0);
  char buf3[3];
  String(String(code[0]) +""+ String(code[1])).toCharArray(buf3, 3);
  DAY = atoi(buf3);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Enter the time:     ");
  lcd.setCursor(0,1);
  lcd.print("Format: (09)(05)    ");
  typeMode(code, 0);
  char buf4[3];
  char buf5[3];
  String(String(code[0]) +""+ String(code[1])).toCharArray(buf4, 3);
  String(String(code[2]) +""+ String(code[3])).toCharArray(buf5, 3);
  HOUR = atoi(buf4);
  MINUTE = atoi(buf5);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter AM or PM:     ");
  typeMode(code, 1);
  if(code[0] == 'A') {
    HOUR = HOUR%12;
  }else {
    if(HOUR==12) {
      HOUR = 12;
    }else {
      HOUR = HOUR + 12;
    }
  }
  lcd.clear();
  
  setTime(HOUR, MINUTE, 0, DAY, MONTH, YEAR);
  screenState = -1;
  //setupState = 1;
  setupState = 2;
}

// Setup container info
// Method to setup container info given a 
// current container state

void enterInfo() {
  int temp_hr;
  if(setupState==1) {
    lcd.setCursor(0,0);
    lcd.print("Container 1         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the label:    ");
    typeMode(code, 1);
    Container0.setLabel(String(code));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 1         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the dosage:  ");
    typeMode(code, 0);
    char buf10[2];
    String(code[0]).toCharArray(buf10, 2);
    Container0.setDoseage(atoi(buf10));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 1         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the frequency:");
    typeMode(code, 0);
    char buf11[2];
    String(code[0]).toCharArray(buf11, 2);
    Container0.setFrequency(atoi(buf11));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 1         ");
    lcd.setCursor(0,1);
    lcd.print("Enter start time:   ");
    lcd.setCursor(0,2);
    lcd.print("Format: (06)(05) ");
    typeMode(code, 0);
    char buf12[3];
    char buf13[3];
    String(String(code[0]) +""+ String(code[1])).toCharArray(buf12, 3);
    String(String(code[2]) +""+ String(code[3])).toCharArray(buf13, 3);
    int temp_hr = atoi(buf12);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 1         ");
    lcd.setCursor(0,1);
    lcd.print("Enter AM or PM:     ");
    typeMode(code, 1);
    if(code[0] == 'A') {
      temp_hr = temp_hr%12;
    }else {
      if(temp_hr==12) {
        temp_hr = 12;
      }else {
        temp_hr = temp_hr + 12;
      }
    }
    Container0.setStartTime(temp_hr, atoi(buf13));
    lcd.clear();
   
    screenState = -1;
    setupState = 2;
  }else if(setupState==2) {
    lcd.setCursor(0,0);
    lcd.print("Container 2         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the label:    ");
    typeMode(code, 1);
    Container1.setLabel(String(code));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 2         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the dosage:  ");
    typeMode(code, 0);
    char buf20[2];
    String(code[0]).toCharArray(buf20, 2);
    Container1.setDoseage(atoi(buf20));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 2         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the frequency:");
    typeMode(code, 0);
    char buf21[2];
    String(code[0]).toCharArray(buf21, 2);
    Container1.setFrequency(atoi(buf21));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 2         ");
    lcd.setCursor(0,1);
    lcd.print("Enter start time:   ");
    lcd.setCursor(0,2);
    lcd.print("Format: (06)(05) ");
    typeMode(code, 0);
    char buf22[3];
    char buf23[3];
    String(String(code[0]) +""+ String(code[1])).toCharArray(buf22, 3);
    String(String(code[2]) +""+ String(code[3])).toCharArray(buf23, 3);
    temp_hr = atoi(buf22);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 2         ");
    lcd.setCursor(0,1);
    lcd.print("Enter AM or PM:     ");
    typeMode(code, 1);
    if(code[0] == 'A') {
      temp_hr = temp_hr%12;
    }else {
      if(temp_hr==12) {
        temp_hr = 12;
      }else {
        temp_hr = temp_hr + 12;
      }
    }
    Container1.setStartTime(temp_hr, atoi(buf23));
    lcd.clear();
   
    //screenState = -1;
    //setupState = 3;
    screenState = 0;
  }else if(setupState==3) {
    lcd.setCursor(0,0);
    lcd.print("Container 3         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the label:    ");
    typeMode(code, 1);
    Container2.setLabel(String(code));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 3         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the dosage:  ");
    typeMode(code, 0);
    char buf30[2];
    String(code[0]).toCharArray(buf30, 2);
    Container2.setDoseage(atoi(buf30));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 3         ");
    lcd.setCursor(0,1);
    lcd.print("Enter the frequency:");
    typeMode(code, 0);
    char buf31[2];
    String(code[0]).toCharArray(buf31, 2);
    Container2.setFrequency(atoi(buf31));
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 3         ");
    lcd.setCursor(0,1);
    lcd.print("Enter start time:   ");
    lcd.setCursor(0,2);
    lcd.print("Format: (06)(05) ");
    typeMode(code, 0);
    char buf32[3];
    char buf33[3];
    String(String(code[0]) +""+ String(code[1])).toCharArray(buf32, 3);
    String(String(code[2]) +""+ String(code[3])).toCharArray(buf33, 3);
    int temp_hr = atoi(buf32);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Container 3         ");
    lcd.setCursor(0,1);
    lcd.print("Enter AM or PM:     ");
    typeMode(code, 1);
    if(code[0] == 'A') {
      temp_hr = temp_hr%12;
    }else {
      if(temp_hr==12) {
        temp_hr = 12;
      }else {
        temp_hr = temp_hr + 12;
      }
    }
    Container2.setStartTime(temp_hr, atoi(buf33));
    lcd.clear();
   
    screenState = 0;
  }
}

// Accumulates button presses
// Listens for up to three button presses to 
// implement button to character logic

int accumulator(int a[], int alpha, int count) {
  for(int i=0; i<3; i++) {
    a[i] = 0;
  }

  int internal = 0;
  bool flag = false;
  unsigned long wait = millis();
  unsigned long offset;
  if(alpha==1) {
    offset = 3000;
  }else {
    offset = 1500;
  }

  while(millis() - wait < offset) {
    if(buttonPushed) {
      delay(250);
      buttonPushed=false;
    }else if(analogRead(enter) >= 768) {
      leave = true;
      buttonPushed=true;
    }else if(digitalRead(number0)==HIGH) {
      a[internal] = 0;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number1)==HIGH) {
      a[internal] = 1;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number2)==HIGH) {
      a[internal] = 2;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number3)==HIGH) {
      a[internal] = 3;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number4)==HIGH) {
      a[internal] = 4;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number5)==HIGH) {
      a[internal] = 5;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number6)==HIGH) {
      a[internal] = 6;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number7)==HIGH) {
      a[internal] = 7;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number8)==HIGH) {
      a[internal] = 8;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }else if(digitalRead(number9)==HIGH) {
      a[internal] = 9;
      internal = internal + 1;
      flag = true;
      buttonPushed=true;
    }
  }   
  if(flag) {
    count = count + 1;
  }
  return count;
}

// Interprets button presses
// Accepts the accumulated button presses as input
// and converts them into characters or digits

void interpreter(int a[], char code[], int alpha, int count) {
  if(alpha==1) {
      if(a[0] == a[1] && a[1] == a[2]) {
        if(a[0] == 1) {
          code[count] = 'C';
        }else if(a[0] == 2) {
          code[count] = 'F';
        }else if(a[0] == 3) {
          code[count] = 'I';
        }else if(a[0] == 4) {
          code[count] = 'L';
        }else if(a[0] == 5) {
          code[count] = 'O';
        }else if(a[0] == 6) {
          code[count] = 'R';
        }else if(a[0] == 7) {
          code[count] = 'U';
        }else if(a[0] == 8) {
          code[count] = 'X';
        }else if(a[0] == 11) {
          code[count-1] = ' ';
          count = count - 1;
        }
      }else if(a[0] == a[1]) {
        if(a[0] == 1) {
          code[count] = 'B';
        }else if(a[0] == 2) {
          code[count] = 'E';
        }else if(a[0] == 3) {
          code[count] = 'H';
        }else if(a[0] == 4) {
          code[count] = 'K';
        }else if(a[0] == 5) {
          code[count] = 'N';
        }else if(a[0] == 6) {
          code[count] = 'Q';
        }else if(a[0] == 7) {
          code[count] = 'T';
        }else if(a[0] == 8) {
          code[count] = 'W';
        }else if(a[0] == 9) {
          code[count] = 'Z';
        }else if(a[0] == 11) {
          code[count-1] = ' ';
          count = count - 1;
        }
      }else {
        if(a[0] == 1) {
          code[count] = 'A';
        }else if(a[0] == 2) {
          code[count] = 'D';
        }else if(a[0] == 3) {
          code[count] = 'G';
        }else if(a[0] == 4) {
          code[count] = 'J';
        }else if(a[0] == 5) {
          code[count] = 'M';
        }else if(a[0] == 6) {
          code[count] = 'P';
        }else if(a[0] == 7) {
          code[count] = 'S';
        }else if(a[0] == 8) {
          code[count] = 'V';
        }else if(a[0] == 9) {
          code[count] = 'Y';
        }else if(a[0] == 11) {
          code[count-1] = ' ';
          count = count - 1;
        }
      }
  }else {
    if(a[0] == 0) {
      code[count] = '0';
    }else if(a[0] == 1) {
      code[count] = '1';
    }else if(a[0] == 2) {
      code[count] = '2';
    }else if(a[0] == 3) {
      code[count] = '3';
    }else if(a[0] == 4) {
      code[count] = '4';
    }else if(a[0] == 5) {
      code[count] = '5';
    }else if(a[0] == 6) {
      code[count] = '6';
    }else if(a[0] == 7) {
      code[count] = '7';
    }else if(a[0] == 8) {
      code[count] = '8';
    }else if(a[0] == 9) {
      code[count] = '9';
    }else if(a[0] == 11) {
      code[count-1] = ' ';
      count = count - 1;
    }
  }
}

// Initiates mode for accepting long strings of
// characters or letters
// Outer loop for accepting one line of text from
// user

void typeMode(char code[], int alpha) {
  for(int i=0; i<3; i++) {
    a[i] = -1;
  }
  for(int i=0; i<20; i++) {
    code[i] = ' ';
  }
  
  int count = 0;
  int new_count = 0;
  leave = false;
  
  while(count<20 && leave == false) {
    new_count = accumulator(a, alpha, count); 
    if(count != new_count) {
      interpreter(a, code, alpha, count);
      lcd.setCursor(0,4);
      lcd.print(code);
    }
    count = new_count;
  }
}

// Screen Display
// This method relays the code to the current state logic

void screenDisplay(){
  if(prevScreenState != screenState) {  
    lcd.clear();
    prevScreenState = screenState;
    screenTime = millis();
  }

  if(millis() - screenTime > 900000) {
    screenTime = millis();
    screenState = 0;
  }
  
  if(screenState==0) {
    startScreen();
  }else if(screenState==1) {
    menuScreen();
  }else if(screenState==2) {
    containerState();
  }else if(screenState==3) {
    displayLabel();
  }else if(screenState==4) {
    displayPrescription();
  }else if(screenState==5) {
    oneRelease();
  }else if(screenState==6) {
    confirmRelease();
  }else if(screenState==-1) {
    deviceSetup();
  }else if(screenState==-2) {
    currentTime();
  }else if(screenState==-3) {
    enterInfo();
  }
}

// Start Screen

void startScreen() {
  lcd.setCursor(1,0);
  lcd.print(greeting);
  lcd.setCursor(0,1);
  lcd.print(startPrompt1);
  lcd.setCursor(1,2);
  lcd.print(date);
  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(analogRead(enter) >= 768) {
    screenState = 1;
    buttonPushed=true;
  }
}

// Menu Screen


void menuScreen() {
  lcd.setCursor(0,0);
  lcd.print(container1);
  lcd.setCursor(0,1);
  lcd.print(container2);
  lcd.setCursor(0,2);
  lcd.print(container3);
  lcd.setCursor(0,3);
  lcd.print(dayRelease);    

  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(digitalRead(number1)==HIGH) {
    screenState = 2;
    contState = 0;
    buttonPushed = true;
  }else if(digitalRead(number4)==HIGH) {
    screenState = 5;
    buttonPushed = true;
  }else if(digitalRead(number2)==HIGH) {
    screenState = 2;
    contState = 1;
    buttonPushed = true;
  }else if(digitalRead(number3)==HIGH) {
    screenState = 2;
    contState = 2;
    buttonPushed = true;
  }
}

// Container Screen

void containerState() {
  lcd.setCursor(0,0);
  lcd.print("Container "+ String(contState+1) +":");
  lcd.setCursor(0,1);
  lcd.print(label1);
  lcd.setCursor(0,2);
  lcd.print(prescription1);
  lcd.setCursor(0,3);
  lcd.print(back1);

  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(digitalRead(number1)==HIGH) {
    screenState = 3;
    buttonPushed = true;
  }else if(digitalRead(number2)==HIGH) {
    screenState = 4;
    buttonPushed = true;
  }else if(digitalRead(number3)==HIGH) {
    screenState = 1;
    buttonPushed = true;
  } 
}

// One-day release screen

void oneRelease() {
  lcd.setCursor(0,0);
  lcd.print(releaseMessage);
  lcd.setCursor(0,1);
  lcd.print(container1);
  lcd.setCursor(0,2);
  lcd.print(container2);
  lcd.setCursor(0,3);
  lcd.print(container3);

  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(digitalRead(number1)==HIGH) {
    screenState = 6;
    releaseState = 0;
    buttonPushed = true;
  }else if(digitalRead(number2)==HIGH) {
    screenState = 6;
    releaseState = 1;
    buttonPushed = true;
  }else if(digitalRead(number3)==HIGH) {
    screenState = 6;
    releaseState = 2;
    buttonPushed = true;
  }
}

// Release Confirmation Screen

void confirmRelease() {
  lcd.setCursor(0,0);
  lcd.print(releaseConfirmation);
  if(releaseState==0) {
    lcd.setCursor(0,1);
    lcd.print("Container 1?        ");
    lcd.setCursor(0,2);
    lcd.print(confirmed);
    lcd.setCursor(0,3);
    lcd.print(denied);
    
    if(buttonPushed) {
      delay(2);
      buttonPushed=false;
    }else if(analogRead(enter) >= 768) {
      int count = Container0.getFrequency();
      motorState = 0;
      for(int i=0; i<count; i++) { 
        dispense(); 
      }
      screenState = 1;
      buttonPushed = true;
    }else if(digitalRead(number1)==HIGH) {
      screenState = 1;
      buttonPushed = true;
    }
  }else if(releaseState==1) {
    lcd.setCursor(0,1);
    lcd.print("Container 2?        ");
    lcd.setCursor(0,2);
    lcd.print(confirmed);
    lcd.setCursor(0,3);
    lcd.print(denied);

    if(buttonPushed) {
      delay(2);
      buttonPushed=false;
    }else if(analogRead(enter) >= 768) {
      int count = Container1.getFrequency();
      motorState = 1;
      for(int i=0; i<count; i++) {   
        dispense();
      }
      screenState = 1;
      buttonPushed = true;
    }else if(digitalRead(number1)==HIGH) {
      screenState = 1;
      buttonPushed = true;
    }
  }else if(releaseState==2) {
    lcd.setCursor(0,1);
    lcd.print("Container 3?        ");
    lcd.setCursor(0,2);
    lcd.print(confirmed);
    lcd.setCursor(0,3);
    lcd.print(denied);

    if(buttonPushed) {
      delay(2);
      buttonPushed=false;
    }else if(analogRead(enter) >= 768) {
      int count = Container2.getFrequency();
      motorState = 2;
      for(int i=0; i<count; i++) {
        dispense();  
      }
      screenState = 1;
      buttonPushed = true;
    }else if(digitalRead(number1)==HIGH) {
      screenState = 1;
      buttonPushed = true;
    }
  }
}

// Display Label Screen

void displayLabel() {
  if(contState==0) {
    lcd.setCursor(0,0);
    lcd.print(label2);
    lcd.setCursor(0,1);
    lcd.print(Container0.getLabel());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }else if(contState==1) {
    lcd.setCursor(0,0);
    lcd.print(label2);
    lcd.setCursor(0,1);
    lcd.print(Container1.getLabel());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }else if(contState==2) {
    lcd.setCursor(0,0);
    lcd.print(label2);
    lcd.setCursor(0,1);
    lcd.print(Container2.getLabel());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }

  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(digitalRead(number1)==HIGH) {
    screenState = 2;
    buttonPushed = true;
  }
}

// Display Prescription Screen

void displayPrescription() {
  if(contState==0) {
    lcd.setCursor(0,0);
    lcd.print(prescription2);
    lcd.setCursor(0,1);
    lcd.print(Container0.printHeader());
    lcd.setCursor(0,2);
    lcd.print(Container0.getPrescription());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }else if(contState==1) {
    lcd.setCursor(0,0);
    lcd.print(prescription2);
    lcd.setCursor(0,1);
    lcd.print(Container1.printHeader());
    lcd.setCursor(0,2);
    lcd.print(Container1.getPrescription());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }else if(contState==2) {
    lcd.setCursor(0,0);
    lcd.print(prescription2);
    lcd.setCursor(0,1);
    lcd.print(Container2.printHeader());
    lcd.setCursor(0,2);
    lcd.print(Container2.getPrescription());
    lcd.setCursor(0,3);
    lcd.print(back2);
  }

  if(buttonPushed) {
    delay(2);
    buttonPushed=false;
  }else if(digitalRead(number1)==HIGH) {
    screenState = 2;
    buttonPushed = true;
  }
}

// Check Dispensation
// Method to determine if it is time to dispense
// medication

void checkDispensation() {
  if(Container0.checkMotor(hour(), minute())) {
    motorState = 0;
    lcd.clear();
    digitalWrite(alarm, HIGH);
    while(analogRead(enter) <= 768) {
      lcd.setCursor(0,0);
      lcd.print("Confirm Dispensation");
      lcd.setCursor(0,1);
      lcd.print("Please press enter  ");
    }
    digitalWrite(alarm, LOW);
    dispense();
  }else if(Container1.checkMotor(hour(), minute())) {
    motorState = 1;
    lcd.clear();
    digitalWrite(alarm, HIGH);
    while(analogRead(enter) <= 768) {
      lcd.setCursor(0,0);
      lcd.print("Confirm Dispensation");
      lcd.setCursor(0,1);
      lcd.print("Please press enter  ");
    }
    digitalWrite(alarm, LOW);
    dispense();
  }else if(Container2.checkMotor(hour(), minute())) {
    motorState = 2;
    lcd.clear();
    digitalWrite(alarm, HIGH);
    while(analogRead(enter) <= 768) {
      lcd.setCursor(0,0);
      lcd.print("Confirm Dispensation");
      lcd.setCursor(0,1);
      lcd.print("Please press enter  ");
    }
    digitalWrite(alarm, LOW);
    dispense();
  }
}

// Dispense
// Method to actually dispense the prescription
// specified amount of medication

void dispense() {
  int count;
  unsigned long offset;
  if(motorState==0) { // Dispense Container 1
    count = Container0.getDoseage();
    for(int i = 0; i < count; i++) {
      offset = millis();
      lcd.clear();
      digitalWrite(motor0, HIGH);
      while(millis() - offset < 5000) {
        lcd.setCursor(0,1);
        lcd.print(dispensing);
      }
      offset = millis();
      lcd.clear();
      digitalWrite(motor0, LOW);
      while(millis() - offset < 1000) {
        lcd.setCursor(10,1);
        lcd.print(String(i+1));
      }
    }
  }else if(motorState==1) { // Dispense Container 2
    count = Container1.getDoseage();
    for(int i = 0; i < count; i++) {
      offset = millis();
      lcd.clear();
      digitalWrite(motor1, HIGH);
      while(millis() - offset < 5000) {
        lcd.setCursor(0,1);
        lcd.print(dispensing);
      }
      offset = millis();
      lcd.clear();
      digitalWrite(motor1, LOW);
      while(millis() - offset < 1000) {
        lcd.setCursor(10,1);
        lcd.print(String(i+1));
      }
    }
  }else if(motorState==2) { // Dispense Container 3
    count = Container2.getDoseage();
    for(int i = 0; i < count; i++) {
      offset = millis();
      lcd.clear();
      analogWrite(motor2, 255);
      while(millis() - offset < 5000) {
        lcd.setCursor(0,1);
        lcd.print(dispensing);
      }
      offset = millis();
      lcd.clear();
      analogWrite(motor2, 0);
      while(millis() - offset < 1000) {
        lcd.setCursor(10,1);
        lcd.print(String(i+1));
      }
    }
  }
}

/*****************************************************************************************************/
// Methods for setup and loop

// Setup

void setup() {
  //LCD Screen Setup
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 

  // Numeric keypad pin setup
  pinMode(motor0, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(number0, INPUT);
  pinMode(number1, INPUT);
  pinMode(number2, INPUT);
  pinMode(number3, INPUT);
  pinMode(number4, INPUT);
  pinMode(number5, INPUT);
  pinMode(number6, INPUT);
  pinMode(number7, INPUT);
  pinMode(number8, INPUT);
  pinMode(number9, INPUT);
  pinMode(enter, INPUT);
  
  // Clear the screen
  lcd.clear();

  // Hard code values for Container 1
  Container0.setLabel("Acebutolol");
  Container0.setDoseage(1);
  Container0.setFrequency(5);
  Container0.setStartTime(8, 30);

  // Hard code values for Container 3
  Container2.setLabel("Prazosin");
  Container2.setDoseage(3);
  Container2.setFrequency(2);
  Container2.setStartTime(10, 0);

}


// Loop

void loop() {
  // Conversion between 12 hour clock and 24 hour clock
  String ext;
  String hr;
  String mn;
  if(hour()>=12) {
    if(hour()>12) {
      hr = String(hour()%12);
    }else {
      hr = String(hour());
    }
    ext = "PM";
  }else {
    if(hour()==0) {
      hr = 12;
    }else {
      hr = String(hour());
    }
    ext = "AM";
  }

  if(minute()<10) {
    mn = String("0"+String(minute()));
  }else {
    mn = String(minute());
  }

  // Format date for idle screen
  date = String(hr +":"+ mn + ext +" "+ (String)day() +"/"+ (String)month() +"/"+ (String)year());

  // Display the correct screen
  screenDisplay();

  // Respond to motor signals
  checkDispensation();
}
