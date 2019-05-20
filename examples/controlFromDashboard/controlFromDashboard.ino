#include "IoTtweetNBIoT.h"

#define relay_1 6   /*Connect relay to pin 6 of UNO*/
#define relay_2 7   /*Connect relay to pin 7 of UNO*/
#define relay_3 11  /*Connect relay to pin 11 of UNO*/
#define relay_4 12  /*Connect relay to pin 12 of UNO*/

String userid = "your-iottweet-account-id";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "Get Control to NB-IoT";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Hello IoTtweet";           /*Your public tweet message to dashboard*/

const long looptime_task1 = 2;                    /* Task 1 time in sec. */

unsigned long previousMillis_task1 = 0;

IoTtweetNBIoT myNBiot;

void setup(){ 
  
  myNBiot.init();

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);

  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, LOW);
  
  previousMillis_task1 = millis();
  
}
void loop(){ 
  
  unsigned long currentMillis_task1 = millis();

  /* Task 1 : Get control status from dashboard */
  if (currentMillis_task1 - previousMillis_task1 >= looptime_task1*1000)
    { 
      
      /* Get control from IoTtweet dashboard */
      String sw1 = myNBiot.getControlbySwitch(userid, key, 1);
      Serial.println("sw1 = " + sw1);
      if(sw1 == "ON"){
        digitalWrite(relay_1, HIGH);
      }else{
        digitalWrite(relay_1, LOW);
      }

      String sw2 = myNBiot.getControlbySwitch(userid, key, 2);
      Serial.println("sw2 = " + sw2);
      if(sw2 == "ON"){
        digitalWrite(relay_2, HIGH);
      }else{
        digitalWrite(relay_2, LOW);
      }

      String sw3 = myNBiot.getControlbySwitch(userid, key, 3);
      Serial.println("sw3 = " + sw3);
      if(sw3 == "ON"){
        digitalWrite(relay_3, HIGH);
      }else{
        digitalWrite(relay_3, LOW);
      }

      String sw4 = myNBiot.getControlbySwitch(userid, key, 4);
      Serial.println("sw4 = " + sw4);
      if(sw4 == "ON"){
        digitalWrite(relay_4, HIGH);
      }else{
        digitalWrite(relay_4, LOW);
      }
      
      previousMillis_task1 = currentMillis_task1;
    }
     
}
