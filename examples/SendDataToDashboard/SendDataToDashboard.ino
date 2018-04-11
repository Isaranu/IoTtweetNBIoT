#include "IoTtweetNBIoT.h"

String userid = "your-IoTtweet-account-ID";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "AIS NB-IoT";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Hello IoTtweet";           /*Your public tweet message to dashboard*/

const long looptime = 20;                         /* Loop delay time in sec. */
unsigned long previousMillis = 0;

long cnt = 0;

IoTtweetNBIoT myNBiot;

void setup()
{ 
  myNBiot.init();
  previousMillis = millis();

}
void loop()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= looptime*1000)
    {
      cnt++;     
      
      /* Example data generating */
      data0 = random(20,80);
      data1 = random(30,70);
      data2 = random(40,60);
      data3 = random(50,55);

      myNBiot.sendDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
     
      previousMillis = currentMillis;
  
    }
     
}
