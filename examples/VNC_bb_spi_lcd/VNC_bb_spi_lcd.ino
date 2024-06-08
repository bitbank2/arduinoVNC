/*
 * VNC_bb_spi_lcd.ino
 *
 *  Created on: Jun 8, 2024
 *
 * required librarys:
 *  - WiFi (arduino core)
 *  - bb_spi_lcd (https://github.com/bitbank2/bb_spi_lcd)
 *  - arduinoVNC (https://github.com/Links2004/arduinoVNC)
 */

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <VNC_bb_spi_lcd.h>
#include <VNC.h>

const char * vnc_ip = "192.168.10.200";
const uint16_t vnc_port = 5900;
const char * vnc_pass = "larryvnc";

const char* ssid = "MEO-B970C0-2G&5G";
const char* password = "19b59e2bf7";

BB_SPI_LCD_VNC tft = BB_SPI_LCD_VNC(DISPLAY_WT32_SC01_PLUS);
arduinoVNC vnc = arduinoVNC(&tft);

void TFTnoWifi(void) {
    tft.lcd.fillScreen(TFT_BLACK);
    tft.lcd.setCursor(0, ((tft.lcd.height() / 2) - (5 * 8)));
    tft.lcd.setTextColor(TFT_RED);
    tft.lcd.setFont(FONT_12x16);
    tft.lcd.println("NO WIFI!");
    tft.lcd.setFont(FONT_8x8);
    tft.lcd.println();
}


void TFTnoVNC(void) {
    tft.lcd.fillScreen(TFT_BLACK);
    tft.lcd.setCursor(0, ((tft.lcd.height() / 2) - (4 * 8)));
    tft.lcd.setTextColor(TFT_GREEN);
    tft.lcd.setFont(FONT_12x16);
    tft.lcd.println("connect VNC");
    tft.lcd.setFont(FONT_8x8);
    tft.lcd.println();
    tft.lcd.print(vnc_ip);
    tft.lcd.print(":");
    tft.lcd.println(vnc_port);
}

void setup(void) {
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();

    tft.lcd.fillScreen(TFT_BLUE);
#ifdef ESP8266
    // disable sleep mode for better data rate
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
#endif
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    TFTnoWifi();
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    TFTnoVNC();

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println(F("[SETUP] VNC..."));

    vnc.begin(vnc_ip, vnc_port);
    vnc.setPassword(vnc_pass); // optional
}

void loop() {
    if(WiFi.status() != WL_CONNECTED) {
        vnc.reconnect();
        TFTnoWifi();
        delay(100);
    } else {
        vnc.loop();
        if(!vnc.connected()) {
            TFTnoVNC();
            // some delay to not flood the server
            delay(5000);
        }
    }
}
