#include <Arduino.h>

#include <WiFiS3.h>
#include <Network.h>

#include <constants.h>
#include <secrets.h>

NetworkClient netcli(WIFI_SSID, WIFI_PASS);

#include <map>

#include <Servo.h>
//#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h>
#include "Arduino_SensorKit.h" // Used for Oled, screen size is 128x64 pixels

char str_buffer[16];
int  loopCount = 0;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Servo myservo;
int servoVal;

std::map<std::string, float> data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n\nStarting up...");

  netcli.connectWiFi();

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  lcd.init();
  lcd.backlight();
  lcd.print("LCD Initialized");

  Oled.begin();
  Oled.setFlipMode(true); // Sets the rotation of the screen
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.print("Oled Initialized");   

  delay(1000);  // delay in between reads for stability
  Oled.clearDisplay(); // Clear the OLED
  lcd.clear(); // Clear the LCD
}

void loop() {
  Serial.println("\n\n==========================================================================");


  // read the inputs
  int sA0 = analogRead(A0);
  int sA1 = analogRead(A1);
  int sA2 = analogRead(A2);
  int sA3 = analogRead(A3);
  // int sA4 = analogRead(A4); // can't use these pins as they are used by the I2C
  // int sA5 = analogRead(A5);


  servoVal = map(sA0, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);              // sets the servo position according to the scaled value

  // print to serial
  Serial.println((String)"A0: " + sA0 + " | A1: " + sA1 + " | A2: " + sA2 + " | A3: " + sA3 + " ---> Pot: " + servoVal);

  //============================================================================
  // LCD
  //
  lcd.setCursor(0,0); // set the cursor to column 0, line 0
  lcd.print("LCD stuff");
  lcd.setCursor(0,1); // set the cursor to column 0, line 1
  sprintf(str_buffer, "A0 %4d; S1 %4d", sA0, servoVal);
  lcd.print(str_buffer);
  //============================================================================

  //============================================================================
  // OLED
  //
  // reference: https://github.com/olikraus/u8g2/wiki/u8x8reference#setcursor
  // font list: https://github.com/olikraus/u8g2/wiki/fntlist8x8
  // Oled.clearDisplay();
  // dtostrf(Environment.readTemperature(), 5, 2, str_float);
  // dtostrf(Environment.readHumidity(),    5, 2, str_float);

  Oled.drawString(0,0, "Oled stuff");
  sprintf(str_buffer, "A0 %4d; A1 %4d", sA0, sA1);
  Oled.drawString(0,1, str_buffer);
  sprintf(str_buffer, "A2 %4d; A3 %4d", sA2, sA3);
  Oled.drawString(0,2, str_buffer);
  //============================================================================


  /*
  //============================================================================
  // NETWORK
  //
  netcli.connectToServer(HOST_NAME, HTTP_PORT);

  // Add a key-value pair to the map
  data["potnr"] = 3;
  data["temp"] = 21.2;
  data["humi"] = 83;
  // Transmit data to web server
  netcli.sendData(data);
  netcli.getServerReply();
  //============================================================================
  */


  delay(100);  // delay in between loops
  loopCount++;

}