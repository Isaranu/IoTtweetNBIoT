
#include "IoTtweetNBIoT.h"
#include "DHT.h"

String userid = "your-IoTtweet-account-ID";                         /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                      /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "AIS NB-IoT";              /*Your private tweet meassage to dashboard*/
String public_tweet = "DHT sensor reading";           /*Your public tweet message to dashboard*/

#define DHTPIN 7 /* connect to Arduino UNO pin D7 */
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const long looptime = 20;                         /* Loop delay time in sec. */
unsigned long previousMillis = 0;

long cnt = 0;

float t,h;

IoTtweetNBIoT myNBiot;

void setup()
{ 
  dht.begin();
  myNBiot.init();
  previousMillis = millis();

}
void loop()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= looptime*1000)
    {
      cnt++;     
      
      /* - DHT sensor reading - */
      t = dht.readTemperature();
      h = dht.readHumidity();

      if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

      Serial.println("----------- Read DHT sensor ------------");
      Serial.println("Temperature is " + String(t) + " celcuis");
      Serial.println("Humidity is " + String(h) + " %RH");
      Serial.println("----------------------------------------");

      myNBiot.sendDashboard(userid,key,t,h,0,0,private_tweet,public_tweet);
     
      previousMillis = currentMillis;
  
    }
     
}
