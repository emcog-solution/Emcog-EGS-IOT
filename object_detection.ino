#define BLYNK_TEMPLATE_ID "TMPL3reqvOeE3"
#define BLYNK_TEMPLATE_NAME "esp8266 object detection"
#define BLYNK_AUTH_TOKEN "gJT3hnEeI8OSMsAtvDxMHN4zOJBK9lqv"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Jai";
char pass[] = "54320000";

unsigned long previousMillis = 0;
const unsigned long interval = 500;   

void checkIRSensor()
{
  int irValue = digitalRead(D5);
  if (irValue == LOW)
  {
    Blynk.virtualWrite(V0, "Object Detected");
      Blynk.logEvent("object_detected", "Object detected by IR sensor");
      Serial.println("Object Detected");
  }
  else
  {
    Blynk.virtualWrite(V0, "No Object");
    Serial.println("No Object");
  }  
}

void setup()
{
  Serial.begin(9600);

  pinMode(D5, INPUT);
  Serial.println("Connecting to WiFi and Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk Connected");
}

void loop()
{
  Blynk.run();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    checkIRSensor();
  }
}