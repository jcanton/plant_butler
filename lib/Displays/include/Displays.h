#ifndef DISPLAYS_H
#define DISPLAYS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino_SensorKit.h"

enum class DisplayType {
  Oled,
  Lcd
};

class Display {
private:
  DisplayType type;
  LiquidCrystal_I2C lcd;
public:
  Display(DisplayType type);
  void initialize();
  void clear(); // New method to clear the display
  void print(uint8_t col, uint8_t row, const char* str);
};

#endif // DISPLAYS_H
