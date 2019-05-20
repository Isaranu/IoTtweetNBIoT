#include "IoTtweetNBIoT.h"

String userid = "your-iottweet-account-id";           /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-iottweet-device-key";              /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                     /*Your sending data variable.*/
String private_tweet = "AIS NB-IoT with Line Notify";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Hello IoTtweet";               /*Your public tweet message to dashboard*/

const long looptime_task1 = 5;                        /* Task 1 time in sec., Example in 5 second */
const long looptime_task2 = 10*60;                    /* Task 2 time in sec., Example in 10 mins */

unsigned long previousMillis_task1 = 0;
unsigned long previousMillis_task2 = 0;

/* LINE notify token parameter */
String LINE_TOKEN = "your-line-notify-token";

IoTtweetNBIoT myNBiot;

void setup(){ 
  
  myNBiot.init();
  
  previousMillis_task1 = millis();
  previousMillis_task2 = millis();
  
}
void loop(){ 
  
  unsigned long currentMillis_task1 = millis();
  unsigned long currentMillis_task2 = millis();

  /* Task 1 : Send data to IoTtweet dashboard */
  if (currentMillis_task1 - previousMillis_task1 >= looptime_task1*1000)
    { 
      
      /* Example data generating */
      data0 = random(20,80);
      data1 = random(30,70);
      data2 = random(40,60);
      data3 = random(50,55);

      myNBiot.sendDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
      previousMillis_task1 = currentMillis_task1;
    }

  /* Task 2 : Send LINE notify */
  if (currentMillis_task2 - previousMillis_task2 >= looptime_task2*1000)
    {
      String line_msg = "data0 = ";
             line_msg += String(data0);
             line_msg += "|data1 = ";
             line_msg += String(data1);
             line_msg += "|data2 = ";
             line_msg += String(data2);
             line_msg += "|data3 = ";
             line_msg += String(data3);
      
      myNBiot.pushLineNotify(LINE_TOKEN, line_msg);
      previousMillis_task2 = currentMillis_task2;
    }
     
}
