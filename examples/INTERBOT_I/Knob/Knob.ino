#define Pot A7 // กำหนดให้ Pot หมายถึงขาพิน A7
int Value = 0; // ประกาศตัวแปร Value เพื่อเก็บค่าที่อ่านได้จาก potentiometer
void setup() {
  Serial.begin(9600); // เริ่มการสื่อสารผ่าน Serial Monitor ที่ความเร็ว 9600 บอด
}
void loop() {
  Value = analogRead(Pot); // อ่านค่าจาก potentiometer ที่ขาพิน A7 และเก็บลงในตัวแปร Value
  Serial.print("Value = "); // แสดงข้อความ "Value = " ผ่าน Serial Monitor
  Serial.println(Value); // แสดงค่าของ Value ที่อ่านได้บน Serial Monitor
  delay(2); // หน่วงเวลาการทำงาน 2 มิลลิวินาที
}