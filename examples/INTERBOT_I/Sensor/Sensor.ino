#include <Adafruit_MCP3008.h> // เรียกใช้ไลบรารี MCP3008
Adafruit_MCP3008 adc; // สร้างออบเจ็กต์ adc สำหรับ MCP3008
int count = 0; // ประกาศตัวแปร count สำหรับนับจำนวนการวนลูป
void setup() {
  Serial.begin(9600); // เริ่มการสื่อสารผ่าน Serial Monitor ที่ความเร็ว 9600 บอด
  while (!Serial) ; // รอจนกว่า Serial จะพร้อมใช้งาน
  Serial.println("MCP3008 simple test."); // แสดงข้อความเพื่อยืนยันการเริ่มต้น
  adc.begin(13, 11, 12, 10); // กำหนดขาพิน SPI สำหรับการสื่อสารกับ MCP3008 (SCK = 13, MOSI = 11, MISO = 12, CS = 10)
}
void loop() {
  for (int chan = 0; chan < 8; chan++) { // วนลูปอ่านค่า ADC จากทั้ง 8 ช่อง
    Serial.print(adc.readADC(chan)); // อ่านค่าอนาล็อกจากแต่ละช่องและแสดงผล
    Serial.print("\t"); // เว้นวรรคด้วยแท็บระหว่างแต่ละค่า
  }
  Serial.print("["); // แสดงเครื่องหมายเปิดวงเล็บ
  Serial.print(count); // แสดงค่าตัวนับการวนลูป
  Serial.println("]"); // แสดงเครื่องหมายปิดวงเล็บและขึ้นบรรทัดใหม่
  count++; // เพิ่มค่าตัวนับทีละ 1
  delay(100); // หน่วงเวลาการทำงาน 100 มิลลิวินาที
}