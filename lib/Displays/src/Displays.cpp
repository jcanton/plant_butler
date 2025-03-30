#include "Displays.h"

Display::Display(DisplayType type) : type(type), lcd(0x27, 16, 2) {}

void Display::initialize() {
  if (type == DisplayType::Oled) {
    Oled.begin();
    Oled.setFlipMode(true);
    Oled.setFont(u8x8_font_chroma48medium8_r);
    Oled.print("Oled Initialized");
  } else if (type == DisplayType::Lcd) {
    lcd.init();
    lcd.backlight();
    lcd.print("LCD Initialized");
  }
}

void Display::clear() {
  if (type == DisplayType::Oled) {
    Oled.clearDisplay();
  } else if (type == DisplayType::Lcd) {
    lcd.clear();
  }
}

void Display::print(uint8_t col, uint8_t row, const char* str) {
  if (type == DisplayType::Oled) {
    Oled.drawString(col, row, str);
  } else if (type == DisplayType::Lcd) {
    lcd.setCursor(col, row);
    lcd.print(str);
  }
}
