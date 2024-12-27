#define PWM1 5  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 1
#define INA1 2  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 1
#define INB1 3  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 1
#define PWM2 6  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 2
#define INA2 7  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 2
#define INB2 4  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 2
void setup() {
  // กำหนดให้พินที่ใช้ทั้งหมดเป็น OUTPUT
  pinMode(PWM1, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
}
void loop() {
  // ทำให้มอเตอร์หมุนไปในทิศทางแรก
  digitalWrite(INA1, LOW);  // ตั้งทิศทางสำหรับมอเตอร์ 1
  digitalWrite(INB1, HIGH); // ตั้งทิศทางสำหรับมอเตอร์ 1
  analogWrite(PWM1, 255);   // กำหนดความเร็วสูงสุดให้มอเตอร์ 1
  digitalWrite(INA2, LOW);  // ตั้งทิศทางสำหรับมอเตอร์ 2
  digitalWrite(INB2, HIGH); // ตั้งทิศทางสำหรับมอเตอร์ 2
  analogWrite(PWM2, 255);   // กำหนดความเร็วสูงสุดให้มอเตอร์ 2
  delay(1000);  // หน่วงเวลา 1 วินาที
  // ทำให้มอเตอร์หมุนไปในทิศทางตรงกันข้าม
  digitalWrite(INA1, HIGH);  // สลับทิศทางมอเตอร์ 1
  digitalWrite(INB1, LOW);   // สลับทิศทางมอเตอร์ 1
  analogWrite(PWM1, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 1
  digitalWrite(INA2, HIGH);  // สลับทิศทางมอเตอร์ 2
  digitalWrite(INB2, LOW);   // สลับทิศทางมอเตอร์ 2
  analogWrite(PWM2, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 2
  delay(1000);  // หน่วงเวลา 1 วินาที
  // หยุดมอเตอร์ทั้งสองตัว
  digitalWrite(INA1, HIGH);  // หยุดมอเตอร์ 1
  digitalWrite(INB1, HIGH);  // หยุดมอเตอร์ 1
  analogWrite(PWM1, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  digitalWrite(INA2, HIGH);  // หยุดมอเตอร์ 2
  digitalWrite(INB2, HIGH);  // หยุดมอเตอร์ 2
  analogWrite(PWM2, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  delay(1000);  // หน่วงเวลา 1 วินาที
}