#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "";
const char* password =  "";
const char* mqttServer = "";
const int mqttPort = 2;
const char* mqttUser = "";
const char* mqttPassword = "";
 
WiFiClient espClient;
PubSubClient client(espClient);


#define ANALOG_PIN_0 36
#define adc 3300
int analog_value = 0;
int sen = 166;
float current, milli_volts, milli_volts_cal = 0;

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  delay(1000);// give me time to bring up serial monitor
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
    for(int i=0 ; i <100 ;i++)
      { 
    int cal = analogRead(ANALOG_PIN_0);
    milli_volts_cal += (cal*adc)/4095;  
      }
    milli_volts_cal/=100;  
 }

void loop()
{
    client.loop(); 
    for(int i=0;i<100;i++)
    {
      analog_value = analogRead(ANALOG_PIN_0);
      milli_volts = (analog_value*adc)/4095;
      milli_volts -= milli_volts_cal;
      current += (milli_volts)/sen; 
    }
    
  current/=100;
  if(current <0) current =0;
  
  client.publish("your article", "your value");
  delay(500);
}
