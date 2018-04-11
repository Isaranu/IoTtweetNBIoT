
#include "IoTtweetNBIoT.h"

/* IoTtweet configuration parameter */
#define IoTtweetNBIoT_HOST "35.185.177.33"    // - New Cloud IoTtweet server
#define IoTtweetNBIoT_PORT "5683"             // - Default udp port
#define IoTtweetNBIoT_libVersion "v1.0"

/* AIS_NB_BC95 library parameter */
String apnName = "devkit.nb";
String serverIP = "35.185.177.33" ;
String serverPort = "5683";
String udpData = "HelloWorld";

AIS_NB_BC95 AISnb;

bool IoTtweetNBIoT:: init(){
  AISnb.debug = false;  /* Terminated all debug print */
  Serial.begin(9600);
  //Serial.println("--- NB-IoT device Initializing and network connecting..... ---");

  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();
  pingRESP pingR = AISnb.pingIP(serverIP);
  Serial.println("Initialize completed !..");
  Serial.println("Ready for data sending to IoTtweet.com");
  return true;
}

String IoTtweetNBIoT:: sendDashboard(String userid, String key, float slot0, float slot1, float slot2, float slot3, String tw, String twpb){

  _userid = userid;
  _key = key;
  _slot0 = slot0;
  _slot1 = slot1;
  _slot2 = slot2;
  _slot3 = slot3;
  _tw = tw;
  _twpb = twpb;

  /* whitespace string replace to %20 */
  //_tw.replace(" ","%20");
  //_twpb.replace(" ","%20");

  Serial.println("------ Send to Cloud.IoTtweet -------");
             _packet = _userid;
             _packet += ":";
             _packet += _key;
             _packet += ":";
             _packet += String(_slot0);
             _packet += ":";
             _packet += String(_slot1);
             _packet += ":";
             _packet += String(_slot2);
             _packet += ":";
             _packet += String(_slot3);
             _packet += ":";
             _packet += _tw;
             _packet += ":";
             _packet += _twpb;

      Serial.println("packet sent : " + String(_packet));
      //unsigned int packetSize = _packet.length();
      //Serial.println("packet length : " + String(packetSize) + " byte.");

  Serial.println("--------------------------------------");

  UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, _packet);
  return "OK";
}

/*
String IoTtweetNBIoT::receiveResponse(){

  UDPReceive resp = AISnb.waitResponse();
  //_response = resp.data;
  //Serial.println("IoTtweet response : " + _response);

  return "received";
}
*/

String IoTtweetNBIoT:: readRSSI(){

  signal chksignal = AISnb.getSignal();
  _rssi = chksignal.rssi;

  return _rssi;
}

String IoTtweetNBIoT:: getVersion()
{
  return IoTtweetNBIoT_libVersion;
}
