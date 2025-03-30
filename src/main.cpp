#include <Arduino.h>
#include <WiFiS3.h>
#include <Network.h>
#include <constants.h>
#include <secrets.h>
#include <map>
#include <Servo.h>
#include "Displays.h" // Include the new Displays library

char str_buffer[16];
int loopCount = 0;

NetworkClient netcli(WIFI_SSID, WIFI_PASS);

Servo myservo;
int servoVal;

std::map<std::string, float> data;

// Create instances of Display
Display display0(DisplayType::Oled);
Display display1(DisplayType::Lcd);

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting up...");

  netcli.connectWiFi();

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // Initialize displays
  display0.initialize();
  display1.initialize();

  delay(1000);

  // Clear displays
  display0.clear();
  display1.clear();
}

void loop() {
  Serial.println("\n\n==========================================================================");

  // read the inputs
  int sA0 = analogRead(A0);
  int sA1 = analogRead(A1);
  int sA2 = analogRead(A2);
  int sA3 = analogRead(A3);

  servoVal = map(sA0, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);              // sets the servo position according to the scaled value

  // Print to lcd
  sprintf(str_buffer, "A0 %4d; S1 %4d", sA0, servoVal);
  display1.print(0, 0, "LCD stuff");
  display1.print(0, 1, str_buffer);

  // Print to Oled
  display0.print(0, 0, "Oled stuff");
  sprintf(str_buffer, "A0 %4d; A1 %4d", sA0, sA1);
  display0.print(0, 1, str_buffer);
  sprintf(str_buffer, "A2 %4d; A3 %4d", sA2, sA3);
  display0.print(0, 2, str_buffer);

  delay(100);  // delay in between loops
  loopCount++;
}