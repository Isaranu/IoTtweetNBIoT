#include "IoTtweetNBIoT.h"

String userid = "your-iottweet-account-id";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "Request network time";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Hello IoTtweet";           /*Your public tweet message to dashboard*/

const long looptime_task1 = 5;                         /* Task 1 time in sec. */

unsigned long previousMillis_task1 = 0;

IoTtweetNBIoT myNBiot;

void setup(){ 
  
  myNBiot.init();
  previousMillis_task1 = millis();
  
}
void loop(){ 
  
  unsigned long currentMillis_task1 = millis();

  /* Task 1 */
  if (currentMillis_task1 - previousMillis_task1 >= looptime_task1*1000)
    { 
      
      /* Request network time */
      String nt = myNBiot.getNetworkTime();
      Serial.println("Network time is " + nt);
      
      previousMillis_task1 = currentMillis_task1;
    }
     
}
