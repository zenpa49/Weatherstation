# Weatherstation
Weatherstation project with Blynk-Bridge.
This simple project consists of 2 seperate Nodemcu-devices, one for the sensor and one for the display unit.
Sensor is BME 280, measures temperature, barometric pressure and humidity.
Display is OLED display (ESP_SSD1306), 128x64. Library must be adapted for Nodemcu.
Sensor-device sends data Blynk App and to display-device using Blynk-Bridge.
To keep the bridge connection alive you must use a dummy project on the app with the auth[] token of the display-device.
