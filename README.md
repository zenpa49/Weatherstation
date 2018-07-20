# Weatherstation
Weatherstation project with Blynk-Bridge.
This simple project consists of 2 seperate Nodemcu-devices, one for the sensor and one for the display unit.
The sensor is BME 280, measures temperature, barometric pressure and humidity.
The display is OLED display (ESP_SSD1306), 128x64. Library must be adapted for Nodemcu.
The sensor-device sends data to the Blynk App via V1, V2 and V3 and to display-device via V4 using Blynk-Bridge.
To keep the bridge connection alive you must use a dummy project on the Blynk app with the auth[] token of the display-device.
