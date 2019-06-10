
#include "IoTtweetNBIoT.h"

/* IoTtweet configuration parameter */
#define IoTtweetNBIoT_HOST "35.185.177.33"    // - New Cloud IoTtweet server
#define IoTtweetNBIoT_PORT "5683"             // - Default udp port
#define IoTtweetNBIoT_libVersion "v2.3"

/* AIS_NB_BC95 library parameter */
String apnName = "devkit.nb";
String serverIP = "35.185.177.33" ;
String serverPort = "5683";
String udpData = "HelloWorld";

AIS_NB_BC95 AISnb;

bool IoTtweetNBIoT::init(){
  AISnb.debug = true;
  Serial.begin(9600);

  Serial.println("Waiting Initialize...");
  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();
  pingRESP pingR = AISnb.pingIP(serverIP);
  Serial.println("Initialize completed !..");
  Serial.println("Ready for data sending to IoTtweet.com");
  return true;
}

String IoTtweetNBIoT::sendDashboard(String userid, String key, float slot0, float slot1, float slot2, float slot3, String tw, String twpb){

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

String IoTtweetNBIoT::readRSSI(){
  signal chksignal_rssi = AISnb.getSignal();
  _rssi = chksignal_rssi.rssi;
  return _rssi;
}

String IoTtweetNBIoT::readCSQ(){
  signal chksignal_csq = AISnb.getSignal();
  _csq = chksignal_csq.csq;
  return _csq;
}

String IoTtweetNBIoT::getVersion(){
  return IoTtweetNBIoT_libVersion;
}

String IoTtweetNBIoT::pushLineNotify(String linetoken, String linemsg){

  _linetoken = linetoken;
  _linemsg = linemsg;

  String _lnfPacket = "LNF";
         _lnfPacket += ":";
         _lnfPacket += _linetoken;
         _lnfPacket += ":";
         _lnfPacket += _linemsg;
         _lnfPacket += ":";
         _lnfPacket += "eol";

  Serial.println("_lnfPacket = " + _lnfPacket);

  UDPSend udpLineNoti = AISnb.sendUDPmsgStr(serverIP, serverPort, _lnfPacket);
  return "Line Notify OK";
}

String IoTtweetNBIoT::getNetworkTime(){

  String _ntpPacket = "NTP";
  Serial.println("Request network time from server (+7GMT)");

  UDPSend udpLineNoti = AISnb.sendUDPmsgStr(serverIP, serverPort, _ntpPacket);
  _ntp = getRespFromServer();

  return _ntp;
}

String IoTtweetNBIoT::getControlbySwitch(String userid, String key, int swnum){

  _userid = userid;
  _key = key;
  _swnum = String(swnum);

  String _getswctl = "SWC";
         _getswctl += ":";
         _getswctl += _userid;
         _getswctl += ":";
         _getswctl += _key;
         _getswctl += ":";
         _getswctl += _swnum;

  UDPSend udpGetcontrol = AISnb.sendUDPmsgStr(serverIP, serverPort, _getswctl);
  String _ctlstatus = getRespFromServer();
  return _ctlstatus;
}

String IoTtweetNBIoT::getUDPip(){

    String _udpipPacket = "IP";
    Serial.println("Request UDP IP address");

    UDPSend udpIP = AISnb.sendUDPmsgStr(serverIP, serverPort, _udpipPacket);
    _udpip = getRespFromServer();

    return _udpip;
}

String IoTtweetNBIoT::getRespFromServer(){

  String respStr = "";
  unsigned long responseChkRetry = 50000;
  int retCnt = 0;

  while((respStr = "") && (retCnt < responseChkRetry)){
    UDPReceive resp = AISnb.waitResponse();
      if(resp.data != ""){
        //Serial.println("resp.data = " + String(resp.data));
        //Serial.println("retry cnt = " + String(retCnt));
        respStr = AISnb.toString(resp.data);
        return respStr;
      }
    retCnt++;
  }

  if(retCnt >= responseChkRetry){
    Serial.println("Timeout at : " + String(retCnt));
    return "Request timeout";
  }

}

/*
String IoTtweetNBIoT::receiveResponse(){

  UDPReceive resp = AISnb.waitResponse();
  //_response = resp.data;
  //Serial.println("IoTtweet response : " + _response);

  return "received";
}
*/
