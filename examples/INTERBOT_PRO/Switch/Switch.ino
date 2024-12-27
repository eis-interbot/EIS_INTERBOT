#define SW_Start 7  // กำหนดพิน 7 ให้เป็นชื่อ SW_Start
#define SW_Mode 8  // กำหนดพิน 8 ให้เป็นชื่อ SW_Mode
int Value1 = 0;  // ประกาศตัวแปร Value1 เพื่อเก็บค่าที่อ่านได้จากพิน SW_Start
int Value2 = 0;  // ประกาศตัวแปร Value2 เพื่อเก็บค่าที่อ่านได้จากพิน SW_Mode
void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารแบบ Serial ที่ความเร็ว 9600 bps
  pinMode(SW_Start, INPUT);  // กำหนดให้พิน SW_Start เป็น input เพื่อรับค่าจากปุ่มหรือสวิตช์
  pinMode(SW_Mode, INPUT);   // กำหนดให้พิน SW_Mode เป็น input เพื่อรับค่าจากปุ่มหรือสวิตช์
}
void loop() {
  Value1 = digitalRead(SW_Start);  // อ่านค่าสถานะ (HIGH หรือ LOW) จากพิน SW_Start
  Value2 = digitalRead(SW_Mode);  // อ่านค่าสถานะ (HIGH หรือ LOW) จากพิน SW_Mode
  Serial.print("SW_Start = ");  // พิมพ์ข้อความ "SW_Start = " ลงบน Serial Monitor
  Serial.print(Value1);  // พิมพ์ค่าที่อ่านได้จากพิน SW_Start (0 หรือ 1)
  Serial.print("\t");  // พิมพ์ตัวแท็บ (\t) เพื่อจัดรูปแบบให้อยู่บรรทัดเดียวกัน
  Serial.print("SW_Mode = ");  // พิมพ์ข้อความ "SW_Mode = " ลงบน Serial Monitor
  Serial.println(Value2);  // พิมพ์ค่าที่อ่านได้จากพิน SW_Mode แล้วขึ้นบรรทัดใหม่
  delay(2);  // หน่วงเวลา 2 มิลลิวินาทีเพื่อป้องกันการทำงานที่เร็วเกินไป
}