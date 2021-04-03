
#define BLYNK_PRINT Serial

#include <Arduino.h>

#define EspSerial Serial1
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
int buzzer = 10;
int pirpin = 8;
int led = 9;
int hareket;
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
char auth[] = "hKbvCD7nr_sFjyiOAoCt-HSlCnt4_GZ-";

char ssid[] = "CenkayEv1";
char pass[] = "0ebcd7a8";
String h;
BlynkTimer timer; 
BLYNK_WRITE(V1)
{  
   int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println(" ALARM SISTEMI BASLATILDI");
    h="ALARM SISTEMI AKTIF";
    Blynk.virtualWrite(V3, h);
    delay(1200);
    hareket=digitalRead(pirpin);
  while(hareket == 1){
    Blynk.email("cenkaycengiz751@gmail.com", "EVDE HAREKET ALGILANDI!!", "Lutfen eve donunuz evde hirsiz olabilir!");
    Blynk.notify("HAREKET ALGILANDI LUTFEN EVE DONUNUZ!!");
    h="HAREKET ALGILANDI";  
  Blynk.virtualWrite(V3, h);
    Serial.println(" HAREKET ALGILANDI!!");
    for(int i=0;i<6;i++){
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(80);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    delay(80);
    }
    delay(500);
    hareket=digitalRead(pirpin);
    if(hareket == 0){
      Serial.println(" HAREKET ALGILANMADI");
      digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    h="ALARM SISTEMI AKTIF";
    Blynk.virtualWrite(V3, h);
    break;
    }
  }
   if(hareket == 0){
      Serial.println(" HAREKET ALGILANMADI");
      digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    }
  delay(100);
    }
  else{
      Serial.println("ALARM SISTEMI KAPALI");
      h = "ALARM SISTEMI KAPALI";
      digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    Blynk.virtualWrite(V3, h);
    }
    Blynk.run(); 
  pinValue = 0; 
  Blynk.syncVirtual(V1);
}
void setup()
{ 
  Serial.begin(9600);
   pinMode(led,OUTPUT);
  pinMode(pirpin,INPUT);
  pinMode(buzzer,OUTPUT);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);  
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
}
