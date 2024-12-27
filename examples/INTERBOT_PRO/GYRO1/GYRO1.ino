#include "Wire.h"  // รวมไลบรารี Wire สำหรับการสื่อสาร I2C
#include "I2Cdev.h"  // รวมไลบรารี I2Cdev สำหรับการสื่อสารกับเซ็นเซอร์
#include "MPU6050.h"  // รวมไลบรารี MPU6050 สำหรับเซ็นเซอร์ MPU6050
MPU6050 mpu;  // สร้างออบเจ็กต์สำหรับเซ็นเซอร์ MPU6050
int16_t ax, ay, az;  // ประกาศตัวแปรสำหรับเก็บค่าการเร่งในแกน X, Y, Z
int16_t gx, gy, gz;  // ประกาศตัวแปรสำหรับเก็บค่าการหมุนในแกน X, Y, Z
struct MyData {  // ประกาศโครงสร้างข้อมูลสำหรับเก็บค่าที่ปรับมา
  byte X;  // ค่าการเร่งในแกน X
  byte Y;  // ค่าการเร่งในแกน Y
  byte Z;  // ค่าการเร่งในแกน Z
};
MyData data;  // สร้างตัวแปร data จากโครงสร้าง MyData
void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารอนุกรมที่ความเร็ว 9600 bps
  Wire.begin();  // เริ่มต้นการสื่อสาร I2C
  mpu.initialize();  // เริ่มต้นเซ็นเซอร์ MPU6050
}
void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);  // อ่านค่าจากเซ็นเซอร์ MPU6050
  data.X = map(ax, -17000, 17000, 0, 255);  // ปรับค่าการเร่งจากช่วง -17000 ถึง 17000 ไปยังช่วง 0 ถึง 255
  data.Y = map(ay, -17000, 17000, 0, 255); 
  data.Z = map(az, -17000, 17000, 0, 255);  
  delay(500); // รอ 500 ms ก่อนอ่านค่าต่อไป
  // แสดงค่าการเร่งในแต่ละแกน
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);
}