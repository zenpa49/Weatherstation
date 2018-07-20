//OLED display op NODEMCU V2, SDK->D1 SDA->D2, 3,3V
//HF 20 juli 2018, 
//Combined with Blynk_Weatherstation_BME280, driven via Blynk-Bridge
//Keep project active to preserve AuthToken for this device!!! Make a placeholder Project

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ESP_SSD1306.h>    // Modification of Adafruit_SSD1306 for ESP8266 compatibilit
#define OLED_RESET 16
ESP_SSD1306 display(OLED_RESET); // FOR I2C

char auth[] = "YourAuthToken";//Keep project active to preserve this AuthToken for the device!!!
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
char deg = 247;

const int t=5000;
String tempt,druk,vocht;

void setup()   {               
Serial.begin (9600);
  delay(1000);
  // init OLED display
  Serial.print("setup OLED display");
  display.begin(SSD1306_SWITCHCAPVCC);  // Switch OLED (aangepaste versie voor ESP8266)
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
  delay(1000);
  // start Wifi
  Blynk.begin(auth, ssid, pass);
  delay(2000);
}//setup

//data via bridge naar display
BLYNK_WRITE(V4)//from Blynk_Weatherstation_BME280
  {
    tempt = String (param[0].asFloat(),1); // assigning incoming temperature value from pin V4 to tempt
    druk = String (param[1].asFloat(),1); // assigning incoming pressure value from pin V4 to druk
    vocht = String (param[2].asFloat(),1); // assigning incoming humidity value from pin V4 to vocht
    
    //prepare OLED:(x pixels = [0-128] ,y pixels = [0-64])0,0 is upperleft   
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    //prepare Data
    display.setCursor(0,2);display.print("Temperature: "+tempt+" "+char(247)+"C");
    display.setCursor(0,16);display.println("Pressure:   "+druk+" hPa");
    display.setCursor(0,29);display.println("Humidity: "+vocht+" %");
    //put on OLED display
    display.display();
  }//BLYNK_WRITE(V4)

void loop() {
  Blynk.run();
}//loop

