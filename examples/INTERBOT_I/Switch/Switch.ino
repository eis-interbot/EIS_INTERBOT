#define SW_Start A6 // กำหนดให้ SW_Start หมายถึงขาพิน A6
int Value = 0; // ประกาศตัวแปร Value เพื่อเก็บค่าที่อ่านได้
void setup() {
  Serial.begin(9600); // เริ่มการสื่อสารผ่าน Serial Monitor ที่ความเร็ว 9600 บอด
}
void loop() {
  Value = analogRead(SW_Start); // อ่านค่าจากพิน A6 และเก็บในตัวแปร Value
  Serial.print("Value = "); // แสดงข้อความ "Value = " ผ่าน Serial Monitor
  Serial.println(Value); // แสดงค่าของ Value ที่อ่านได้บน Serial Monitor
  delay(2); // หน่วงเวลา 2 มิลลิวินาที
}