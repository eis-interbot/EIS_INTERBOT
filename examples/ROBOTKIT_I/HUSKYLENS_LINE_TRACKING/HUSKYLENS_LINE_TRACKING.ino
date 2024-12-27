#include "HUSKYLENS.h"
HUSKYLENS huskylens;
// เรียกใช้ไลบรารี HuskyLens สำหรับควบคุมกล้อง AI และสร้างออบเจ็กต์ `huskylens`

// กำหนดพินที่ใช้ควบคุมมอเตอร์ทั้งสอง
#define PWMA 6  // พิน PWM สำหรับมอเตอร์ A ใช้ควบคุมความเร็ว
#define AIN1 7  // พิน IN1 สำหรับควบคุมทิศทางของมอเตอร์ A
#define AIN2 4  // พิน IN2 สำหรับควบคุมทิศทางของมอเตอร์ A
#define PWMB 5  // พิน PWM สำหรับมอเตอร์ B ใช้ควบคุมความเร็ว
#define BIN1 2  // พิน IN1 สำหรับควบคุมทิศทางของมอเตอร์ B
#define BIN2 3  // พิน IN2 สำหรับควบคุมทิศทางของมอเตอร์ B

// ตัวแปรที่เกี่ยวข้องกับการควบคุม PD Controller
float kp, kd;     // ค่า Proportional (kp) และ Derivative (kd)
float p, d, fl;   // ค่าผลลัพธ์ของ P, D, และผลรวม (Final Output)
float m1, m2;     // ความเร็วที่คำนวณได้สำหรับมอเตอร์ A และ B
int error, last;  // ข้อผิดพลาดปัจจุบัน (error) และข้อผิดพลาดครั้งก่อน (last)
int power;        // กำลังพื้นฐานที่ส่งให้มอเตอร์ (ความเร็วคงที่)

// ID ของเส้นที่ต้องการติดตาม (ตั้งค่าเริ่มต้นเป็น 1)
int ID1 = 1;

// ฟังก์ชันเริ่มต้นการทำงาน (Setup)
void setup() {
  // กำหนดพินที่เชื่อมต่อกับมอเตอร์ให้ทำงานในโหมด Output
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // เริ่มต้นมอเตอร์ให้อยู่ในสถานะหยุด
  motorA(0);
  motorB(0);

  // เริ่มการสื่อสารผ่าน I2C กับ HuskyLens
  Wire.begin();
  while (!huskylens.begin(Wire)) {  // ตรวจสอบการเชื่อมต่อกับ HuskyLens
    delay(100);                     // หากเชื่อมต่อไม่สำเร็จ ให้รอ 100 ms แล้วลองใหม่
  }

  // ตั้งค่าให้ HuskyLens ใช้โหมดติดตามเส้น (Line Tracking)
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
}

// ฟังก์ชันหลักที่ทำงานในลูป
void loop() {
  // ขอข้อมูลจาก HuskyLens ว่าตรวจพบเส้นที่ต้องการหรือไม่
  if (huskylens.request(ID1)) {
    HUSKYLENSResult result = huskylens.read();  // อ่านค่าผลลัพธ์จาก HuskyLens

    // ตั้งค่ากำลังพื้นฐานและพารามิเตอร์ของ PD Controller
    power = 20;  // กำลังพื้นฐานสำหรับมอเตอร์
    kp = 0.05;   // ค่าการคูณสำหรับส่วน Proportional
    kd = 0.025;  // ค่าการคูณสำหรับส่วน Derivative

    // คำนวณข้อผิดพลาด: ตำแหน่งปัจจุบันของเส้น - จุดกึ่งกลางที่ต้องการ (160)
    error = (int32_t)result.xTarget - (int32_t)160;

    // คำนวณส่วน Proportional (P): คูณข้อผิดพลาดด้วย kp
    p = error * kp;

    // คำนวณส่วน Derivative (D): ดูความเปลี่ยนแปลงของข้อผิดพลาดแล้วคูณด้วย kd
    d = (error - last) * kd;

    // รวมค่า P และ D เป็นค่าผลลัพธ์สุดท้าย (fl)
    fl = p + d;

    // บันทึกข้อผิดพลาดปัจจุบันไว้ใช้ในลูปถัดไป
    last = error;

    // คำนวณความเร็วของมอเตอร์ A และ B โดยปรับตามค่าผลลัพธ์ fl
    m1 = power - fl;  // มอเตอร์ A ชดเชยในทิศทางหนึ่ง
    m2 = power + fl;  // มอเตอร์ B ชดเชยในทิศทางตรงกันข้าม

    // จำกัดค่าความเร็วให้อยู่ในช่วง -100 ถึง 100 เพื่อป้องกันค่าผิดพลาด
    if (m1 <= -100) m1 = -100;
    if (m1 >= 100) m1 = 100;
    if (m2 <= -100) m2 = -100;
    if (m2 >= 100) m2 = 100;

    // ส่งค่าความเร็วไปควบคุมมอเตอร์ A และ B
    motorA(m1);
    motorB(m2);
  } else {
    // หากไม่พบเส้น ให้หยุดมอเตอร์ทั้งสอง
    motorA(0);
    motorB(0);
  }

  // หน่วงเวลาเล็กน้อยเพื่อความเสถียรของการควบคุม
  delay(100);
}

// ฟังก์ชันควบคุมมอเตอร์ A
void motorA(int speed) {
  // แปลงค่าความเร็วจาก -100 ถึง 100 ให้เป็น 0 ถึง 255 สำหรับ PWM
  speed = speed * 2.55;
  if (speed >= 255) speed = 255;    // จำกัดความเร็วสูงสุด
  if (speed <= -255) speed = -255;  // จำกัดความเร็วต่ำสุด

  // กำหนดทิศทางของมอเตอร์ A
  boolean inPin1, inPin2;
  if (speed >= 0) {  // เดินหน้า
    inPin1 = HIGH;
    inPin2 = LOW;
  } else {  // ถอยหลัง
    inPin1 = LOW;
    inPin2 = HIGH;
    speed = -speed;  // เปลี่ยนความเร็วเป็นค่าบวก
  }

  // ส่งสัญญาณไปยังพินควบคุม
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);  // ส่งค่า PWM เพื่อควบคุมความเร็ว
}

// ฟังก์ชันควบคุมมอเตอร์ B
void motorB(int speed) {
  // แปลงค่าความเร็วจาก -100 ถึง 100 ให้เป็น 0 ถึง 255 สำหรับ PWM
  speed = speed * 2.55;
  if (speed >= 255) speed = 255;    // จำกัดความเร็วสูงสุด
  if (speed <= -255) speed = -255;  // จำกัดความเร็วต่ำสุด

  // กำหนดทิศทางของมอเตอร์ B
  boolean inPin1, inPin2;
  if (speed >= 0) {  // เดินหน้า
    inPin1 = HIGH;
    inPin2 = LOW;
  } else {  // ถอยหลัง
    inPin1 = LOW;
    inPin2 = HIGH;
    speed = -speed;  // เปลี่ยนความเร็วเป็นค่าบวก
  }

  // ส่งสัญญาณไปยังพินควบคุม
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB, speed);  // ส่งค่า PWM เพื่อควบคุมความเร็ว
}