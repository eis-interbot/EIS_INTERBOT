#include <SPI.h>  // เรียกใช้ไลบรารี SPI
#include <Wire.h> // เรียกใช้ไลบรารี Wire
#include <Adafruit_GFX.h> // เรียกใช้ไลบรารี Adafruit_GFX
#include <Adafruit_SSD1306.h> // เรียกใช้ไลบรารี Adafruit_SSD1306
Adafruit_SSD1306 display(128, 64, &Wire, -1);  // กำหนดหน้าจอ OLED ขนาด 128x64 พิกเซล
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // เริ่มต้นการทำงานของจอ OLED ที่อยู่ที่ Address 0x3C
  display.clearDisplay(); // ล้างหน้าจอ OLED
  display.display();  // แสดงผลหน้าจอ (ณ ตอนนี้หน้าจอว่าง)
}
void loop() {
  display.clearDisplay(); // ล้างหน้าจอก่อนการแสดงผลใหม่
  display.setTextSize(1); // กำหนดขนาดของข้อความเป็นขนาดเล็กสุด (1 เท่า)
  display.setTextColor(SSD1306_WHITE); // กำหนดสีของข้อความให้เป็นสีขาว
  display.setCursor(0, 0);  // กำหนดตำแหน่งการเริ่มต้นแสดงผลที่มุมซ้ายบน (0, 0)
  display.print("Hellow INTERBOT - I");  // แสดงข้อความบนหน้าจอ
  display.display();  // อัปเดตหน้าจอเพื่อแสดงข้อความ
}