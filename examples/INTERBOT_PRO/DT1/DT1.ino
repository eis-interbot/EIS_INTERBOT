#include <Wire.h>  // รวมไลบรารี Wire สำหรับการสื่อสาร I2C
#include <SparkFun_VL6180X.h>  // รวมไลบรารี SparkFun VL6180X สำหรับเซ็นเซอร์ VL6180X
#define VL6180X_ADDRESS 0x29  // กำหนดที่อยู่ I2C ของเซ็นเซอร์ VL6180X
VL6180xIdentification identification;  // ประกาศตัวแปรสำหรับเก็บข้อมูลการระบุของเซ็นเซอร์
VL6180x sensor(VL6180X_ADDRESS);  // สร้างออบเจ็กต์สำหรับเซ็นเซอร์ VL6180X
void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารอนุกรมที่ความเร็ว 9600 bps
  Wire.begin();  // เริ่มต้นการสื่อสาร I2C
  delay(100);  // รอเวลาเล็กน้อยให้ระบบทำงาน
  if (sensor.VL6180xInit() != 0) {  // ตรวจสอบการเริ่มต้นเซ็นเซอร์
    Serial.println("Failed to initialize. Freezing...");  // ถ้าเริ่มต้นไม่สำเร็จให้แสดงข้อความนี้
    while (1)  // หยุดการทำงานที่นี่ (loop forever)
      ;
  }
  sensor.VL6180xDefautSettings();  // ตั้งค่าตั้งต้นของเซ็นเซอร์
  delay(1000);  // รอเวลาเล็กน้อย
}
void loop() {
  Serial.print("Distance measured (mm) = ");  // แสดงข้อความ
  Serial.println(sensor.getDistance());  // รับระยะทางที่วัดได้และพิมพ์ออกมา
  delay(500);  // รอ 500 ms ก่อนวัดระยะทางอีกครั้ง
}