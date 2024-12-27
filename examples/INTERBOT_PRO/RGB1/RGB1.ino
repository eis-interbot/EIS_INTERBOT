#include <Wire.h>  // รวมไลบรารี Wire สำหรับการสื่อสาร I2C
#include "Adafruit_TCS34725.h"  // รวมไลบรารี Adafruit TCS34725 สำหรับเซ็นเซอร์สี
// สร้างออบเจ็กต์สำหรับเซ็นเซอร์ TCS34725 โดยระบุเวลาในการรวมแสง 614 ms และการขยาย 1x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
void setup(void) {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารอนุกรมที่ความเร็ว 9600 bps
  if (tcs.begin()) {  // ตรวจสอบว่าเซ็นเซอร์ถูกค้นพบหรือไม่
    Serial.println("Found sensor");  // ถ้าพบเซ็นเซอร์ ให้พิมพ์ข้อความนี้
  } else {
    Serial.println("No TCS34725 found ... check your connections");  // ถ้าไม่พบเซ็นเซอร์ ให้พิมพ์ข้อความนี้
    while (1);  // หยุดการทำงานที่นี่ (loop forever)
  }
}
void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;  // ประกาศตัวแปรเพื่อเก็บค่าที่ได้จากเซ็นเซอร์
  tcs.getRawData(&r, &g, &b, &c);  // รับข้อมูลดิบ (ค่า R, G, B, C) จากเซ็นเซอร์
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);  // คำนวณอุณหภูมิสี
  lux = tcs.calculateLux(r, g, b);  // คำนวณความสว่าง (Lux)
  // แสดงผลอุณหภูมิสีและความสว่าง
  Serial.print("Color Temp: ");
  Serial.print(colorTemp, DEC);  // แสดงผลอุณหภูมิสี
  Serial.print(" K - ");
  Serial.print("Lux: ");
  Serial.print(lux, DEC);  // แสดงผลความสว่าง
  Serial.print(" - ");
  Serial.print("R: ");
  Serial.print(r, DEC);  // แสดงผลค่ารวมของสีแดง
  Serial.print(" ");
  Serial.print("G: ");
  Serial.print(g, DEC);  // แสดงผลค่ารวมของสีเขียว
  Serial.print(" ");
  Serial.print("B: ");
  Serial.print(b, DEC);  // แสดงผลค่ารวมของสีน้ำเงิน
  Serial.print(" ");
  Serial.print("C: ");
  Serial.print(c, DEC);  // แสดงผลค่ารวมของแสงที่ตรวจจับได้
  Serial.print(" ");
  Serial.println(" ");
}