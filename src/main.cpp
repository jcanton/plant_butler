#include <Arduino.h>
#include <WiFiS3.h>
#include <Network.h>
#include <constants.h>
#include <secrets.h>
#include <map>
#include <Servo.h>
#include <Screen.h>

char str_buffer[16];
int loop_count = 0;

NetworkClient net_client(WIFI_SSID, WIFI_PASS);

Servo my_servo;
int servo_val;

std::map<std::string, float> data;

// Create instances of Screen
Screen screen0(ScreenType::Oled);
Screen screen1(ScreenType::Lcd);

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting up...");

  net_client.connectWiFi();

  my_servo.attach(9);  // attaches the servo on pin 9 to the servo object

  // Initialize screens
  screen0.initialize();
  screen1.initialize();

  delay(1000);

  // Clear screens
  screen0.clear();
  screen1.clear();
}

void loop() {
  Serial.println("\n\n==========================================================================");

  // read the inputs
  int s_a0 = analogRead(A0);
  int s_a1 = analogRead(A1);
  int s_a2 = analogRead(A2);
  int s_a3 = analogRead(A3);

  servo_val = map(s_a0, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  my_servo.write(servo_val);              // sets the servo position according to the scaled value

  // Print to screen0
  screen0.print(0, 0, "Oled measure");
  sprintf(str_buffer, "A0 %4d; A1 %4d", s_a0, s_a1);
  screen0.print(0, 1, str_buffer);
  sprintf(str_buffer, "A2 %4d; A3 %4d", s_a2, s_a3);
  screen0.print(0, 2, str_buffer);

  // Print to screen1
  sprintf(str_buffer, "A0 %4d; S1 %4d", s_a0, servo_val);
  screen1.print(0, 0, "LCD printing");
  screen1.print(0, 1, str_buffer);

  delay(100);  // delay in between loops
  loop_count++;
}