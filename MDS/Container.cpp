/*
 * Ross Rucho
 * Start Date: 11/9/18
 * Source file for Container class
 */

#include "Arduino.h"
#include "Container.h"

// Class Implementation

Container::Container() {
  _label = ""; // Name of prescription
  _doseage = 0; // Number of pills distributed 
  _frequency = 0; // Number of distributions per day
  _startHour = 0; // Time of first dispensation hours
  _startMin = 0; // Time of first dispensation minutes
  _lastRun = 1440; // Time of the last run in minutes
}

// Method to check if the motor should dispense

bool Container::checkMotor(int hr, int mn) {
  bool flag = false;
  if(60*hr + mn != _lastRun) {
    _lastRun = 1440;
    int time_inc = (int) (960.0/_frequency);
  
    for(int i=0; i<_frequency; i++) {
      if( (60*hr + mn) == (60*_startHour + _startMin + i*time_inc) ) {
        flag = true;
        _lastRun = 60*hr + mn;
      }
    }
  }
  
  return flag;
}

// Get prescripition label

String Container::getLabel() {
  return _label;
}

// Set prescription label

void Container::setLabel(String label) {
  _label = label;
}

// Set prescription dosage

void Container::setDoseage(int doseage) {
  _doseage = doseage;
}

// Get prescription dosage

int Container::getDoseage() {
  return _doseage;
}

// Set prescription frequency

void Container::setFrequency(int frequency) {
  _frequency = frequency;
}

// Get prescription frequency

int Container::getFrequency() {
  return _frequency;
}

// Set prescription start time

void Container::setStartTime(int startHour, int startMin) {
  _startHour = startHour;
  _startMin = startMin;
}

// Format printing header

String Container::printHeader() {
  return String("Quant. Freq.  Start ");
}

// Format printing prescription info.

String Container::getPrescription() {
  String ext;
  String hr;
  String mn;
  if(_startHour>=12) {
    if(_startHour>12) {
      hr = String(_startHour%12);
    }else {
      hr = String(_startHour);
    }
    ext = "PM";
  }else {
    if(_startHour == 0) {
      hr = 12;
    }else {
      hr = String(_startHour);
    }   
    ext = "AM";
  }

  if(_startMin<10) {
    mn = String("0"+ String(_startMin));
  }else {
    mn = String(_startMin);
  }
  
  return String("  "+ (String)_doseage +"      "+ (String)_frequency +"   "+ hr +":"+ mn + ext);
}
