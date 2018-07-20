//HF 20 7 2018, With Bridge to OLED
//Combined with Blynk_OLED_Weatherstation
 
#define BLYNK_PRINT Serial
#define LED D0 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>  //sensors
#include <Adafruit_BME280.h>  //barometer
#include <math.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
char oledauth[] = "YourDeviceAuthToken";//token OLED device 2

//variabelen
float vochtigheid;
float temperatuur;
float luchtdruk;
Adafruit_BME280 bme;//I2C address 0x76, Attention: change in library-updates !!
WidgetBridge bridge1(V4);//bridge definition

BlynkTimer timer;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  bme.begin();
  pinMode(LED, OUTPUT);   // LED pin as output.
  timer.setInterval(5000L, sendSensor);
}//setup()

//initialise Bridge
BLYNK_CONNECTED() {
  bridge1.setAuthToken(oledauth); // Token of device 2
}

void sendSensor()
{
  digitalWrite(LED, LOW);   // turn the LED on
  vochtigheid = bme.readHumidity();
  temperatuur = bme.readTemperature();
  luchtdruk = bme.readPressure()/100;//correction for hPascal
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, temperatuur);//for use on app
  Blynk.virtualWrite(V2, vochtigheid);//for use on app
  Blynk.virtualWrite(V3, luchtdruk);//for use on app
  bridge1.virtualWrite(V4, temperatuur, vochtigheid, luchtdruk); //and send it to device 2 via bridge1 as V4
  digitalWrite(LED, HIGH);// turn the LED off
}//sendSensor()

void loop()
{
  Blynk.run();
  timer.run();
}//loop()

