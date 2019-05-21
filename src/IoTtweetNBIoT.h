
#ifndef IoTtweetNBIoT_h
#define IoTtweetNBIoT_h

#include "Arduino.h"
#include "AIS_NB_BC95.h"

class IoTtweetNBIoT
{

public:

  bool init();
  String sendDashboard(String userid, String key, float slot0, float slot1, float slot2, float slot3, String tw, String twpb);
  String receiveResponse();
  String readRSSI();
  String readCSQ();
  String getVersion();
  String pushLineNotify(String linetoken, String linemsg);
  String getNetworkTime();
  String getRespFromServer();
  String getControlbySwitch(String userid, String key, int swnum);
  String getUDPip();

private:
  String _packet, _rssi, _csq;
  String _userid, _key;
  String _tw, _twpb;
  float _slot0, _slot1, _slot2, _slot3;
  const char *_libversion;
  String _str, _response, _controlpanelstatus;
  const char *_sw1status, *_sw2status, *_sw3status, *_sw4status, *_sw5status, *_sl1status, *_sl2status, *_sl3status;
  float f_sl1status, f_sl2status, f_sl3status;
  String _allcontrol;
  uint8_t _sw, _slider;
  bool _conn;
  String _linetoken, _linemsg;
  String _ntp;
  String _swnum;
  String _udpip;
};

#endif
