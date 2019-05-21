/*
  This code work great with >> "Arduino MEGA 2560" (Unstatble when you use Arduino UNO with this code).
  So, please jump TX,RX signal as below
  - Pin 8 to Pin 48
  - Pin 9 to Pin 46
*/
#include "IoTtweetNBIoT.h"
#include "DHT.h"

#define relay_1 5   /*Connect relay to pin 6 of Arduino MEGA 2560*/
#define relay_2 6   /*Connect relay to pin 7 of Arduino MEGA 2560*/
#define relay_3 11  /*Connect relay to pin 11 of Arduino MEGA 2560*/
#define relay_4 12  /*Connect relay to pin 12 of Arduino MEGA 2560*/

#define DHTPIN 7 /* connect to Arduino MEGA 2560 pin D7 */
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/* LINE notify token parameter */
String LINE_TOKEN = "your-line-notify-token";

String userid = "your-iottweet-account-id";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "NB-IoT control";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Powered by IoTtweet";           /*Your public tweet message to dashboard*/

const long looptime_task1 = 5;    /* Task 1 time in sec. (To Send DHT to Dashboard) */
const long looptime_task2 = 10;   /* Task 2 time in sec. (To Send LINE notfiy) */
const long looptime_task3 = 2;    /* Task 3 time in sec. (To get switch status from dashboard) */

unsigned long previousMillis_task1 = 0;
unsigned long previousMillis_task2 = 0;
unsigned long previousMillis_task3 = 0;

float t,h;

IoTtweetNBIoT myNBiot;

void setup(){ 

  dht.begin();
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
  previousMillis_task2 = millis();
  previousMillis_task3 = millis();
  
}
void loop(){ 
  
  unsigned long currentMillis_task1 = millis();
  unsigned long currentMillis_task2 = millis();
  unsigned long currentMillis_task3 = millis();

  /* Task 1 : Send DHT data to Dashboard */
  if (currentMillis_task1 - previousMillis_task1 >= looptime_task1*1000)
    { 
      /* - DHT sensor reading - */
      t = dht.readTemperature();
      h = dht.readHumidity();

      if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

      String csq = myNBiot.readCSQ();
      Serial.println("CSQ = " + csq);
  
      Serial.println("Read DHT : Temp=" + String(t) + " c, Humid=" + String(h) + " %RH");
      myNBiot.sendDashboard(userid,key,t,h,0,0,private_tweet,public_tweet);      
      previousMillis_task1 = currentMillis_task1;
    }

    /* Task 2 : Send LINE notify */
  if (currentMillis_task2 - previousMillis_task2 >= looptime_task2*1000)
    { 
      
      String line_msg = "Temp = ";
             line_msg += String(t);
             line_msg += "| Humid = ";
             line_msg += String(h);

      Serial.println(">> Push LINE Notify <<");
      myNBiot.pushLineNotify(LINE_TOKEN, line_msg);
      previousMillis_task2 = currentMillis_task2;
    }

    /* Task 3 : Get control status from dashboard */
  if (currentMillis_task3 - previousMillis_task3 >= looptime_task3*1000)
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
      
      previousMillis_task3 = currentMillis_task3;
    }
     
}
