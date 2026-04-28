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

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const unsigned long interval = 500; 

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

