#include <Adafruit_MCP3008.h>  // ไลบรารีสำหรับการใช้งาน MCP3008 (ADC)

#define PWMA 6  // พิน PWM สำหรับมอเตอร์ A
#define AIN1 7  // พินควบคุมทิศทาง IN1 ของมอเตอร์ A
#define AIN2 4  // พินควบคุมทิศทาง IN2 ของมอเตอร์ A
#define PWMB 5  // พิน PWM สำหรับมอเตอร์ B
#define BIN1 2  // พินควบคุมทิศทาง IN1 ของมอเตอร์ B
#define BIN2 3  // พินควบคุมทิศทาง IN2 ของมอเตอร์ B

Adafruit_MCP3008 mcp;  // สร้างออบเจ็กต์สำหรับ MCP3008

// ตัวแปรที่เกี่ยวข้องกับเซนเซอร์
uint8_t Unit_sensor = 8;                                           // จำนวนเซนเซอร์ที่ใช้งาน (8 ตัว)
uint16_t sensor_pin[8];                                            // อาเรย์สำหรับเก็บค่าที่อ่านได้จากแต่ละเซนเซอร์
uint16_t minValue[] = { 120, 121, 139, 133, 142, 426, 130, 129 };  // ค่าต่ำสุดของแต่ละเซนเซอร์ (ใช้สำหรับการปรับเทียบ)
uint16_t maxValue[] = { 555, 553, 644, 628, 681, 592, 571, 549 };  // ค่าสูงสุดของแต่ละเซนเซอร์ (ใช้สำหรับการปรับเทียบ)
uint32_t Last_Position;                                            // ตำแหน่งล่าสุดของเส้น (บันทึกไว้สำหรับใช้กรณีหลุดเส้น)

// ตัวแปรที่เกี่ยวข้องกับ PD Controller
float kp, kd;     // ค่าพารามิเตอร์ของ PD (Proportional,Derivative)
float p, d, fl;   // ตัวแปรสำหรับเก็บผลการคำนวณ PD แต่ละส่วน
float m1, m2;     // ความเร็วของมอเตอร์ A และ B
int error, last;  // ข้อผิดพลาดปัจจุบันและข้อผิดพลาดครั้งก่อน
int power;  // กำลังพื้นฐานของมอเตอร์

// ฟังก์ชันคำนวณตำแหน่งของเส้นจากค่าของเซนเซอร์
int position() {
  readADC();             // อ่านค่าจากเซนเซอร์ทั้งหมด
  bool In_line = false;  // ตัวบอกว่าเซนเซอร์จับเส้นอยู่หรือไม่
  long Average = 0;      // ค่าเฉลี่ยของตำแหน่งเส้น
  long sum = 0;          // ผลรวมของค่าที่อ่านได้จากเซนเซอร์
  for (uint8_t i = 0; i < Unit_sensor; i++) {
    // แปลงค่าที่อ่านได้ให้อยู่ในช่วง 0 ถึง 1000 โดยปรับตาม minValue และ maxValue
    long value = map(long(sensor_pin[i]), minValue[i], maxValue[i], 1000, 0);
    if (value > 1000) value = 1000;         // หากค่าเกิน 1000 ให้ตั้งเป็น 1000
    if (value < 0) value = 0;               // หากค่าต่ำกว่า 0 ให้ตั้งเป็น 0
    if (value > 200) In_line = true;        // หากค่ามากกว่า 200 ถือว่าเซนเซอร์จับเส้นได้
    if (value > 50) {                       // ใช้เฉพาะค่าที่มากกว่า 50 มาคำนวณตำแหน่ง
      Average += (long)value * (i * 1000);  // คำนวณตำแหน่ง
      sum += value;                         // บวกค่าของเซนเซอร์
    }
  }
  if (!In_line) {  // ถ้าทุกเซนเซอร์ไม่จับเส้น (หลุดเส้น)
    if (Last_Position < (Unit_sensor - 1) * 1000 / 2) {
      return 0;  // ถ้าตำแหน่งล่าสุดอยู่ทางซ้าย ให้ส่งตำแหน่ง 0
    } else {
      return (Unit_sensor - 1) * 1000;  // ถ้าตำแหน่งล่าสุดอยู่ทางขวา ให้ส่งค่าตำแหน่งสูงสุด
    }
  } else {
    Last_Position = Average / sum;  // คำนวณตำแหน่งล่าสุดจากค่าเฉลี่ย
  }
  return Last_Position;  // ส่งค่าตำแหน่งล่าสุดกลับไป
}

void setup() {
  mcp.begin(13, 11, 12, 10);  // เริ่มต้นการใช้งาน MCP3008
  // กำหนดโหมดของพินมอเตอร์ทั้งหมดเป็น OUTPUT
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  motorA(0);                       // หยุดมอเตอร์ A
  motorB(0);                       // หยุดมอเตอร์ B
  while (analogRead(A6) < 512) {}  // รอจนกว่าปุ่มจะถูกกด
}

void loop() {
  power = 50;                 // กำหนดค่ากำลังพื้นฐานของมอเตอร์
  kp = 0.015;                 // กำหนดค่าพารามิเตอร์ Proportional
  kd = 0.35;                  // กำหนดค่าพารามิเตอร์ Derivative
  error = position() - 3500;  // คำนวณข้อผิดพลาด (ตำแหน่งปัจจุบัน - ตำแหน่งเป้าหมาย)
  p = error * kp;             // คำนวณส่วน P (Proportional)
  d = (error - last) * kd;    // คำนวณส่วน D (Derivative)
  fl = p + d;                 // รวมค่าที่คำนวณได้ของ P และ D
  last = error;               // เก็บข้อผิดพลาดปัจจุบันสำหรับใช้ในรอบถัดไป
  m1 = power - fl;            // คำนวณความเร็วสำหรับมอเตอร์ A
  m2 = power + fl;            // คำนวณความเร็วสำหรับมอเตอร์ B
  // จำกัดค่าความเร็วของมอเตอร์ไม่ให้อยู่เกิน -100 ถึง 100
  if (m1 <= -100) m1 = -100;
  if (m1 >= 100) m1 = 100;
  if (m2 <= -100) m2 = -100;
  if (m2 >= 100) m2 = 100;
  motorA(m1);  // ขับมอเตอร์ A
  motorB(m2);  // ขับมอเตอร์ B
}

void readADC() {
  for (int i = 0; i < 8; i++) {
    sensor_pin[i] = mcp.readADC(i);  // อ่านค่าจาก MCP3008 สำหรับแต่ละเซนเซอร์
  }
}

void motorA(int speed) {
  speed = speed * 2.55;             // แปลงความเร็วจาก -100 ถึง 100 ให้เป็นค่าที่ PWM เข้าใจ (0 ถึง 255)
  if (speed >= 255) speed = 255;    // จำกัดค่า PWM ไม่เกิน 255
  if (speed <= -255) speed = -255;  // จำกัดค่า PWM ไม่ต่ำกว่า -255
  boolean inPin1, inPin2;
  if (speed >= 0) {  // กำหนดทิศทางเดินหน้า
    inPin1 = HIGH;
    inPin2 = LOW;
  } else {  // กำหนดทิศทางถอยหลัง
    inPin1 = LOW;
    inPin2 = HIGH;
    speed = -speed;  // เปลี่ยนความเร็วเป็นค่าบวก
  }
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);  // ส่งสัญญาณ PWM ไปยังมอเตอร์ A
}

void motorB(int speed) {
  speed = speed * 2.55;             // แปลงความเร็วจาก -100 ถึง 100 ให้เป็นค่าที่ PWM เข้าใจ (0 ถึง 255)
  if (speed >= 255) speed = 255;    // จำกัดค่า PWM ไม่เกิน 255
  if (speed <= -255) speed = -255;  // จำกัดค่า PWM ไม่ต่ำกว่า -255
  boolean inPin1, inPin2;
  if (speed >= 0) {  // กำหนดทิศทางเดินหน้า
    inPin1 = HIGH;
    inPin2 = LOW;
  } else {  // กำหนดทิศทางถอยหลัง
    inPin1 = LOW;
    inPin2 = HIGH;
    speed = -speed;  // เปลี่ยนความเร็วเป็นค่าบวก
  }
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB, speed);  // ส่งสัญญาณ PWM ไปยังมอเตอร์ B
}