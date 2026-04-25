#define BLYNK_TEMPLATE_ID "TMPL3reqvOeE3"
#define BLYNK_TEMPLATE_NAME "esp8266 object detection"
#define BLYNK_AUTH_TOKEN "gJT3hnEeI8OSMsAtvDxMHN4zOJBK9lqv"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "Jai";
char pass[] = "54320000";

#define DHTPIN D5
#define DHTTYPE DHT11
#define LDR_PIN A0

#define FAN_PIN D1
#define LIGHT_PIN D2

//temp, humidity, light intensity
#define VPIN_LIGHT_VALUE V1
#define VPIN_TEMP V2
#define VPIN_HUMIDITY V3

// #define VPIN_FAN_STATUS V3
// #define VPIN_LIGHT_STATUS V4

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const unsigned long interval = 500; 

// float temperatureThreshold = 35.0;
// int lightThreshold = 400;

void sendGreenhouseData()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int ldrValue = analogRead(LDR_PIN);

  Blynk.virtualWrite(V2, ldrValue);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V4, humidity);

  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  

}

void setup()
{
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    sendGreenhouseData();
  }
}


  // if (isnan(temperature) || isnan(humidity))
  // {
  //   Serial.println("DHT11 reading failed");
  //   return;
  // }

  // Fan control


  /*
    LDR AO logic depends on module connection.
    Common case:
    Bright light -> high ADC value
    Darkness     -> low ADC value

    So light is turned ON when ldrValue < lightThreshold.
  */
/*
  If using relay module:
  Most relay modules are active LOW.
  If your relay works opposite, change these two lines.
*/