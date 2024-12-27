#include <Adafruit_GFX.h>  // รวมไลบรารี Adafruit GFX สำหรับฟังก์ชันกราฟิก
#include <Adafruit_ST7789.h>  // รวมไลบรารี Adafruit ST7789 สำหรับควบคุมจอแสดงผล
#include <SPI.h>  // รวมไลบรารี SPI สำหรับการสื่อสารแบบอนุกรมกับจอแสดงผล
Adafruit_ST7789 tft = Adafruit_ST7789(0, 12, 11);  // สร้างออบเจ็กต์สำหรับควบคุมจอ ST7789 โดยระบุขา: CS=0, DC=12, RST=11
void setup() {
  tft.init(240, 240, SPI_MODE2);  // เริ่มต้นจอแสดงผลด้วยความกว้าง 240, ความสูง 240 และ SPI_MODE2
  tft.setRotation(2);  // ตั้งค่าการหมุนของจอแสดงผล; 2 หมายถึงการกลับด้าน
  tft.fillScreen(ST77XX_BLACK);  // เติมพื้นหลังของหน้าจอด้วยสีดำ
}
void loop() {
  tft.setTextSize(2);  // ตั้งขนาดข้อความเป็น 2 (ส่งผลต่อขนาดตัวอักษร)
  tft.setCursor(0, 5);  // ตั้งตำแหน่งของเคอร์เซอร์ไปที่มุมบนซ้าย (0, 5)
  tft.print("INTERBOT - PRO");  // แสดงข้อความ "INTERBOT - PRO" บนจอแสดงผล
}