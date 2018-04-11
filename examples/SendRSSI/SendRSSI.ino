#include "IoTtweetNBIoT.h"

String userid = "your-IoTtweet-account-ID";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "";                        /*Your private tweet meassage to dashboard*/
String public_tweet = "";                         /*Your public tweet message to dashboard*/

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
      
      String rssi = myNBiot.readRSSI();
      String rssi_txt = "RSSI is " + rssi;

      byte buf[30];
      rssi.toCharArray(buf,30);
      
      int rssi_num = atoi(buf);
      rssi_num = rssi_num * (-1);

      myNBiot.sendDashboard(userid,key,rssi_num,0,0,0,rssi_txt,public_tweet);
     
      previousMillis = currentMillis;
  
    }
     
}
