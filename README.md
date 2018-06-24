![alt text](https://github.com/Isaranu/IoTtweetNBIoT/blob/master/logo.png "logo")
# IoTtweetNBIoT
![alt_text](https://img.shields.io/badge/bulid-passing-brightgreen.svg "bulidpassing")
![alt_text](https://img.shields.io/badge/Compatible-ArduinoIDE-green.svg "bulidpassing")<br>
Library สำหรับการส่งข้อมูลจากอุปกรณ์ NB-IoT ไปที่ **IoTtweet, Internet of Things platform** ที่ใช้งานง่ายที่สุดแล้วในตอนนี้ :)

### [รายละเอียดของ Library]

- อุปกรณ์ที่รองรับ และผ่านการทดสอบ **IoTtweetNBIoT** library นี้ผ่านการทดสอบด้วยอุปกรณ์ NB-IoT device.<br>
**รุ่น Model** : DEVIO NB-SHIELD I. จากบริษัท AIS (Advanced Info Services plc.)<br>
**รุ่น Model** : TRUE NB-IoT board. จากบริษัท TRUE Corp.<br>

**ทำงานร่วมกับ** : Arduino UNO R3, Arduino MEGA 2560<br>
กรณีต่อกับ Arduino UNO : สามารถใช้งานได้ทันที<br>
กรณีต่อกับ Arduino MEGA 2560 : ให้ดึง jump สายดังนี้<br>
> pin 8 มายัง pin 48<br>
> pin 9 มายัง pin 46<br>

**Sensor ที่ใช้ร่วมทดสอบ** : DHT22(Digital Temperature/Humidity sensor), GPS U-Blox NEO 6M.<br>

- วิธีการติดตั้งบน Arduino IDE : เข้าไปที่ **Sketch** > **Includes library** > **Manage libraries**, และพิมพ์ค้นหา "IoTtweetNBIoT". กด Install ได้ทันที.

- Library ที่ต้องใช้งานร่วมด้วย : **AIS_NB_BC95.h**, สามารถติดตั้งได้จากค้นหาใน Arduino Library Manager.

### [วิธีใช้งานกับ Dashboard IoTtweet]

- **สมัครใช้งาน IoTtweet** : เข้าไปที่ www.iottweet.com ทำการ Signup และ verify activate e-mail ให้เรียบร้อย. ไปที่ **"My IoT garage"** ทำการเพิ่ม device เพื่อรับ key ที่ใช้สำหรับใส่ลงใน code.

- **ออกแบบ Dashboard** : ไปที่ **"Dashboard"**, และทำการ Edit layout. เพิ่ม Widget ต่างๆที่ต้องการ พร้อมทั้งตั้งค่า (setting) widget แต่ละ element ให้เรียบร้อย. เมื่อเสร็จเรียบร้อย ให้กด **"Save layout"**.

- **เชื่อมต่อบอร์ด** : ประกอบบอร์ด DEVIO NB-SHIELD เข้ากับ Arduino UNO หรือ Arduino MEGA. (ประกอบให้ Pin ตรงกัน ตาม spec. ของบอร์ด) และทำการเชือมต่อสาย USB.

- **Upload code** : สามารถใช้ code ตัวอย่างจากใน Examples ได้ เช่น<br>
**SendDHTsensor.ino** > ส่งค่าอุณหภูมิและความชื้นจากเซนเซอร์ DHT ไปที่ Dashboard ในช่องข้อมูล slot0, slot1 ตามลำดับ.<br>
**SendDataToDashboard.ino** > Random ค่าส่งไปแสดงผลที่หน้า Dashboard ในช่องข้อมูล slot0 ถึง slot3 ตามลำดับ.<br>
**SendRSSI** > ส่งค่าความเข้มสัญญาณ (Signal Strength - dbm) ไปแสดงผลที่ Dashboard.<br>
> การเชื่อมต่อสัญญาณ NB-IoT ได้หรือไม่นั้น ขึ้นอยู่กับการเปิดสัญญาณในแต่ละพื้นที่.

### [Code]

คำอธิบายคำสั่ง code ต่างๆใน **IoTtweetNBIoT** library.<br>

 - เรียกใช้งาน IoTtweetNBIoT.h library<br>
```CPP
#include "IoTtweetNBIoT.h"
```

- กรอกเลข ID ของ IoTtweet account และ key ของอุปกรณ์ที่ register ใน **My IoT garage**.
```CPP
String userid = "your-IoTtweet-account-ID";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "your-device-key";                   /*IoTtweet registered device key in "MY IOT Garage"*/
```

- Variable ของข้อมูลที่ต้องการส่ง. สามารถแทนเข้าไปในตัวแปรนี้ได้เลย.
```CPP
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "AIS NB-IoT";              /*Your private tweet meassage to dashboard*/
String public_tweet = "Hello IoTtweet";           /*Your public tweet message to dashboard*/
```

- ประกาศตัวแปร Class เพื่อใช้งานคำสั่งต่างๆที่อยู่ใน library
```CPP
IoTtweetNBIoT myNBiot;
```

- ส่งข้อมูล IoTtweet Dashboard
```CPP
myNBiot.sendDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
```

- อ่านค่า RSSI
```CPP
String rssi = myNBiot.readRSSI();
```

### [Server และ Protocol]
- Server ให้บริการบน Google Cloud Platform.
- Protocol แบบ UDP connection. (CoAP protocol กำลังพัฒนาอยู่ในขณะนี้)

**รายละเอียดเพิ่มเติม**
**website** : www.iottweet.com และ http://code.isaranu.com<br>
**facebook** : https://www.facebook.com/IoTtweet<br>
**facebook group** : https://www.facebook.com/groups/191156967967490<br>
**LINE ID** : @codeisaranu
