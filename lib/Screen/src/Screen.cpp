#include "Screen.h"

Screen::Screen(ScreenType type) : type(type), lcd(0x27, 16, 2) {}

void Screen::initialize() {
  if (type == ScreenType::Oled) {
    Oled.begin();
    Oled.setFlipMode(true);
    Oled.setFont(u8x8_font_chroma48medium8_r);
    Oled.print("Oled Initialized");
  } else if (type == ScreenType::Lcd) {
    lcd.init();
    lcd.backlight();
    lcd.print("LCD Initialized");
  }
}

void Screen::clear() {
  if (type == ScreenType::Oled) {
    Oled.clearDisplay();
  } else if (type == ScreenType::Lcd) {
    lcd.clear();
  }
}

void Screen::print(uint8_t col, uint8_t row, const char* str) {
  if (type == ScreenType::Oled) {
    Oled.drawString(col, row, str);
  } else if (type == ScreenType::Lcd) {
    lcd.setCursor(col, row);
    lcd.print(str);
  }
}
