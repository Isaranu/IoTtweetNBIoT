# IoTtweetNBIoT
Library สำหรับการส่งข้อมูลจากอุปกรณ์ NB-IoT ไปที่ IoTtweet, Internet of Things platform ที่ใช้งานง่ายที่สุดแล้วในตอนนี้ :)

### [รายละเอียดของ Library]

- อุปกรณ์ที่รองรับ และผ่านการทดสอบ **IoTtweetNBIoT** library นี้ผ่านการทดสอบด้วยอุปกรณ์ NB-IoT จากบริษัท AIS (Advanced Info Services plc.)<br>
**รุ่น Model** : DEVIO NB-SHIELD I.<br>
**ทำงานร่วมกับ** : Arduino UNO R3, Arduino MEGA 2560<br>
**Sensor ที่ใช้ร่วมทดสอบ** : DHT22(Digital Temperature/Humidity sensor), GPS U-Blox NEO 6M.<br>

- วิธีการติดตั้งบน Arduino IDE : เข้าไปที่ **Sketch** > **Includes library** > **Manage libraries**, และพิมพ์ค้นหา "IoTtweetNBIoT". กด Install ได้ทันที.

- Library ที่ต้องใช้งานร่วมด้วย : **AIS_NB_BC95.h**, สามารถติดตั้งได้จากค้นหาใน Arduino Library Manager.

### [วิธีใช้งานกับ Dashboard IoTtweet]

- **สมัครใช้งาน IoTtweet** : เข้าไปที่ www.iottweet.com ทำการ Signup และ verify activate e-mail ให้เรียบร้อย. ไปที่ **My IoT garage** ทำการเพิ่ม device เพื่อรับ key ที่ใช้สำหรับใส่ลงใน code.


