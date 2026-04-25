#define BLYNK_TEMPLATE_ID "TMPL3reqvOeE3"
#define BLYNK_TEMPLATE_NAME "esp8266 object detection"
#define BLYNK_AUTH_TOKEN "gJT3hnEeI8OSMsAtvDxMHN4zOJBK9lqv"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Jai";
char pass[] = "54320000";
 

unsigned long previousMillis = 0;
const unsigned long interval = 500;   


void checkldr()
{
  int ldrValue = analogRead(A0);
  Serial.print("ldrValue: ");
  Serial.println(ldrValue);


  if (ldrValue < 500)
  {
    digitalWrite(D4, HIGH);  
    Serial.println("ledON");
    Blynk.virtualWrite(V0, 1);
  }
  else
  {
    digitalWrite(D4, LOW);    
    Serial.println("ledOFF");
    Blynk.virtualWrite(V0, 0);
  }
}



void setup()
{
  Serial.begin(9600);

  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop()
{
  Blynk.run();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    checkldr();
  }
}

  /*
    Connection used:
    3.3V --- LDR --- A0 --- 10k --- GND

    Bright light  -> higher ADC value
    Darkness      -> lower ADC value

    So LED ON when ldrValue < threshold
  */
  
// // To change threshold from Blynk app
// BLYNK_WRITE(VPIN_THRESHOLD)
// {
//   threshold = param.asInt();

//   Serial.print("New Threshold: ");
//   Serial.println(threshold);
// }