#include <Arduino.h>
#include <WiFiS3.h>
#include <Network.h>
#include <constants.h>
#include <secrets.h>
#include <map>
#include <Screen.h>
#include <Manifold.h>

std::map<std::string, float> data;

// WiFi client
//NetworkClient net_client(WIFI_SSID, WIFI_PASS);

// Screen(s)
Screen screen1(ScreenType::Oled);
Screen screen2(ScreenType::Lcd);

// Manifold(s)
Manifold manifold1(5, 8, &screen2); // Pass screen2 to manifold1

char str_buffer[16];
int loop_count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting up...");

  //net_client.connectWiFi();

  //// Initialize screen(s)
  screen1.initialize();
  screen2.initialize();
  delay(1000);
  
  // Initialize manifold(s)
  screen1.clear();
  screen1.print(0, 0, "Init manifold 1");
  manifold1.initialize();
  screen1.print(0, 1, "Done.");
  delay(5000);

  // Test manifold(s)
  screen1.clear();
  screen1.print(0, 0, "Test manifold 1");
  manifold1.test();
  screen1.print(0, 1, "Done.");
  delay(5000);

  // Clear screen(s)
  screen1.clear();
  screen2.clear();
}

void loop() {
  sprintf(str_buffer, "Loop nr. %d", loop_count);
  Serial.println(str_buffer);

  // read the inputs
  int s_a0 = analogRead(A0);
  int s_a1 = analogRead(A1);
  int s_a2 = analogRead(A2);
  int s_a3 = analogRead(A3);

  // Print to screen1
  screen1.print(0, 0, "Oled measure");
  sprintf(str_buffer, "A0 %4d; A1 %4d", s_a0, s_a1);
  screen1.print(0, 1, str_buffer);
  sprintf(str_buffer, "A2 %4d; A3 %4d", s_a2, s_a3);
  screen1.print(0, 2, str_buffer);

  // Print to screen2
  sprintf(str_buffer, "A0 %4d; A1 %4d", s_a0, s_a1);
  screen2.print(0, 0, "LCD printing");
  screen2.print(0, 1, str_buffer);

  delay(1000);  // delay in between loops
  loop_count++;
}