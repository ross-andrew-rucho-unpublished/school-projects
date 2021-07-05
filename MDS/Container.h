/*
 * Ross Rucho
 * Start Date: 11/9/18
 * Header file for Container class
 */

#ifndef Container_h
#define Container_h

#include "Arduino.h"

// Class declaration
class Container {
  public:
    Container();
    bool checkMotor(int hr, int mn);
    String getLabel();
    void setLabel(String label);
    void setDoseage(int doseage);
    int getDoseage();
    void setFrequency(int frequency);
    int getFrequency();
    void setStartTime(int startHour, int startMin);
    String printHeader();
    String getPrescription();

  private:
    String _label;
    int _doseage;
    int _frequency;
    int _startHour;
    int _startMin;
    int _lastRun;
};

#endif
