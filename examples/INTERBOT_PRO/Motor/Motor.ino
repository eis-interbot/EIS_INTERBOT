#define PWM1 2  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 1
#define INA1 22  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 1
#define INB1 23  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 1
#define PWM2 3  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 2
#define INA2 25  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 2
#define INB2 24  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 2
#define PWM3 5  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 3
#define INA3 26  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 3
#define INB3 27  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 3
#define PWM4 6  // กำหนดขาพิน PWM สำหรับมอเตอร์ตัวที่ 4
#define INA4 29  // กำหนดขาพินควบคุมทิศทาง INA สำหรับมอเตอร์ตัวที่ 4
#define INB4 28  // กำหนดขาพินควบคุมทิศทาง INB สำหรับมอเตอร์ตัวที่ 4
void setup() {
  // กำหนดให้พินที่ใช้ทั้งหมดเป็น OUTPUT
  pinMode(PWM1, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(INA3, OUTPUT);
  pinMode(INB3, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(INA4, OUTPUT);
  pinMode(INB4, OUTPUT);
}
void loop() {
  // ทำให้มอเตอร์หมุนไปในทิศทางแรก
  digitalWrite(INA1, LOW);   // ตั้งทิศทางสำหรับมอเตอร์ 1
  digitalWrite(INB1, HIGH);  // ตั้งทิศทางสำหรับมอเตอร์ 1
  analogWrite(PWM1, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 1
  digitalWrite(INA2, LOW);   // ตั้งทิศทางสำหรับมอเตอร์ 2
  digitalWrite(INB2, HIGH);  // ตั้งทิศทางสำหรับมอเตอร์ 2
  analogWrite(PWM2, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 2
  digitalWrite(INA3, LOW);   // ตั้งทิศทางสำหรับมอเตอร์ 3
  digitalWrite(INB3, HIGH);  // ตั้งทิศทางสำหรับมอเตอร์ 3
  analogWrite(PWM3, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 3
  digitalWrite(INA4, LOW);   // ตั้งทิศทางสำหรับมอเตอร์ 4
  digitalWrite(INB4, HIGH);  // ตั้งทิศทางสำหรับมอเตอร์ 4
  analogWrite(PWM4, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 4
  delay(1000);               // หน่วงเวลา 1 วินาที
  // ทำให้มอเตอร์หมุนไปในทิศทางตรงกันข้าม
  digitalWrite(INA1, HIGH);  // สลับทิศทางมอเตอร์ 1
  digitalWrite(INB1, LOW);   // สลับทิศทางมอเตอร์ 1
  analogWrite(PWM1, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 1
  digitalWrite(INA2, HIGH);  // สลับทิศทางมอเตอร์ 2
  digitalWrite(INB2, LOW);   // สลับทิศทางมอเตอร์ 2
  analogWrite(PWM2, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 2
  digitalWrite(INA3, HIGH);  // สลับทิศทางมอเตอร์ 3
  digitalWrite(INB3, LOW);   // สลับทิศทางมอเตอร์ 3
  analogWrite(PWM3, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 3
  digitalWrite(INA4, HIGH);  // สลับทิศทางมอเตอร์ 4
  digitalWrite(INB4, LOW);   // สลับทิศทางมอเตอร์ 4
  analogWrite(PWM4, 255);    // กำหนดความเร็วสูงสุดให้มอเตอร์ 4
  delay(1000);               // หน่วงเวลา 1 วินาที
  // หยุดมอเตอร์ทั้งสองตัว
  digitalWrite(INA1, HIGH);  // หยุดมอเตอร์ 1
  digitalWrite(INB1, HIGH);  // หยุดมอเตอร์ 1
  analogWrite(PWM1, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  digitalWrite(INA2, HIGH);  // หยุดมอเตอร์ 2
  digitalWrite(INB2, HIGH);  // หยุดมอเตอร์ 2
  analogWrite(PWM2, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  digitalWrite(INA3, HIGH);  // หยุดมอเตอร์ 3
  digitalWrite(INB3, HIGH);  // หยุดมอเตอร์ 3
  analogWrite(PWM3, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  digitalWrite(INA4, HIGH);  // หยุดมอเตอร์ 4
  digitalWrite(INB4, HIGH);  // หยุดมอเตอร์ 4
  analogWrite(PWM4, 255);    // ยังคงกำหนด PWM แต่ทิศทางทำให้มอเตอร์หยุด
  delay(1000);               // หน่วงเวลา 1 วินาที
}