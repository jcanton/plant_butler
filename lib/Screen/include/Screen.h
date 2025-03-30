#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino_SensorKit.h"

enum class ScreenType {
  Oled,
  Lcd
};

class Screen {
private:
  ScreenType type;
  LiquidCrystal_I2C lcd;
public:
  Screen(ScreenType type);
  void initialize();
  void clear(); // Method to clear the screen
  void print(uint8_t col, uint8_t row, const char* str);
};

#endif // SCREEN_H
