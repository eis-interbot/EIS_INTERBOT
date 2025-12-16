#include <PS2X_lib.h>          //เรียกไลบรารี PS2X_lib.h
#include <Servo.h>             // ไลบรารี Servo.h
#include <Adafruit_MCP3008.h>  // เรียกใช้ไลบรารี MCP3008

PS2X ps2x;             // สร้างอ็อบเจ็กต์ของ PS2X เพื่อเชื่อมต่อและควบคุมการทำงานของ PS2 Controller
Adafruit_MCP3008 adc;  // สร้างออบเจ็กต์ adc สำหรับ MCP3008

// กำหนดขาเชื่อมต่อของมอเตอร์และพินต่างๆ
#define PWM1 5       // ขา PWM ของมอเตอร์ 1
#define INA1 2       // ขาอินพุต A ของมอเตอร์ 1
#define INB1 3       // ขาอินพุต B ของมอเตอร์ 1
#define PWM2 6       // ขา PWM ของมอเตอร์ 2
#define INA2 7       // ขาอินพุต A ของมอเตอร์ 2
#define INB2 4       // ขาอินพุต B ของมอเตอร์ 2
#define PS2_DAT 11   // ขา PS2 Data
#define PS2_CMD 12   // ขา PS2 Command
#define PS2_SEL 9    // ขา PS2 Select
#define PS2_CLK 13   // ขา PS2 Clock
#define PIEZO_PIN 8  // ขาของ Buzzer (สำหรับเสียงแจ้งเตือน)

// กำหนดขาเซอร์โว
#define LIFTER_PIN A3  // เซอร์โวสำหรับ Lifter (ยก)
Servo lifter;          // สร้างอ็อบเจ็กต์เซอร์โว
int error = 0;         // สร้างอ็อบเจ็กต์สำหรับเช็คค่าการเชื่อมต่อ
int lifterCount;
// ฟังก์ชัน setup() ใช้ตั้งค่าเริ่มต้น
void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารผ่าน Serial ที่ความเร็ว 9600 bps
  // เชื่อมต่อกับ PS2 controller
  error = ps2x.config_gamepad(PS2_CLK, PS2_DAT, PS2_SEL, PS2_CMD, true, true);
  // ตรวจสอบหากมีข้อผิดพลาดในการเชื่อมต่อ
  if (error == 0) {
    Serial.println("PS2 Controller connected successfully");
  } else {
    Serial.println("Error connecting PS2 Controller");
  }

  while (!Serial)
    ;                              // รอจนกว่า Serial จะพร้อมใช้งาน
  adc.begin(PS2_CLK, 11, 12, 10);  // กำหนดขาพิน SPI สำหรับการสื่อสารกับ MCP3008 (SCK = 13, MOSI = 11, MISO = 12, CS = 10)

  // ตั้งค่าพินที่ใช้ควบคุมมอเตอร์ให้เป็น Output
  pinMode(PWM1, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);

  // กำหนดค่าเริ่มต้นให้มอเตอร์หยุด
  analogWrite(PWM1, 0);
  digitalWrite(INA1, LOW);
  digitalWrite(INB1, LOW);
  analogWrite(PWM2, 0);
  digitalWrite(INA2, LOW);
  digitalWrite(INB2, LOW);

  // กำหนดขาเซอร์โว
  lifter.attach(LIFTER_PIN);
  // ตั้งค่าเริ่มต้นให้เซอร์โว
  lifterCount = 90;
  lifter.write(lifterCount);  // เซอร์โว Lifter เริ่มต้นที่มุม 0 องศา (กลาง)

  // เล่นเสียงเบื้องต้นบน Buzzer
  tone(PIEZO_PIN, 440, 1000);  // เสียง 440 Hz, ใช้เวลา 1 วินาที
  delay(5000);                 // หน่วงเวลา 5 วินาที
  tone(PIEZO_PIN, 262, 500);   // เสียง 262 Hz, ใช้เวลา 0.5 วินาที
}

// ฟังก์ชัน loop() ใช้ควบคุมมอเตอร์ตามค่าจาก PS2 controller
void loop() {
  if (error == 1)  // ถ้ามีข้อผิดพลาดในการตั้งค่า ให้หยุดการทำงาน
    return;

  ps2x.read_gamepad(false, 0);  // อ่านข้อมูลจาก PS2 controller

  // ตรวจสอบว่าได้กดปุ่ม CROSS หรือไม่
  bool xPressed = ps2x.ButtonPressed(PSB_CROSS);
  if (xPressed) {
    tone(PIEZO_PIN, 1000, 500);  // เล่นเสียง 1000 Hz เมื่อกดปุ่ม CROSS
  }

  // การควบคุม Lifter (ยกขึ้น-ลง)
  if (ps2x.ButtonPressed(PSB_R1)) {
    lifterCount = lifterCount - 5;
    if (lifterCount < 0) {
      lifterCount = 0;
    }
    lifter.write(lifterCount);
  }
  if (ps2x.ButtonPressed(PSB_R2)) {
    lifterCount = lifterCount + 5;
    if (lifterCount > 90) {
      lifterCount = 90;
    }
    lifter.write(lifterCount);  // ยกลงต่ำสุด
  }

  // อ่านค่าจาก Analog stick ซ้าย (LY: Left Y-axis) และขวา (RX: Right X-axis)
  int ly = ps2x.Analog(PSS_LY);  // ค่าจาก Joystick แนวตั้ง (LY)
  int rx = ps2x.Analog(PSS_RX);  // ค่าจาก Joystick แนวนอน (RX)

  // แปลงค่า LY และ RX ให้อยู่ในช่วง -255 ถึง 255
  int speed = map(ly, 0, 255, -255, 255);  // แปลงค่า LY (การเคลื่อนไหวแนวตั้ง) ให้เป็น -255 ถึง 255
  int turn = map(rx, 0, 255, -255, 255);   // แปลงค่า RX (การเลี้ยวแนวนอน) ให้เป็น -255 ถึง 255

  // การควบคุมมอเตอร์ที่เดินหน้า/ถอยหลังตามค่า speed
  if (speed > 10) {            // หากค่าความเร็วเป็นบวก (เดินหน้า)
    analogWrite(PWM1, speed);  // ปรับความเร็วมอเตอร์ 1
    digitalWrite(INA1, LOW);   // หมุนมอเตอร์ 1 ไปข้างหน้า
    digitalWrite(INB1, HIGH);
    analogWrite(PWM2, speed);  // ปรับความเร็วมอเตอร์ 2
    digitalWrite(INA2, LOW);   // หมุนมอเตอร์ 2 ไปข้างหน้า
    digitalWrite(INB2, HIGH);
  } else if (speed < -10) {     // หากค่าความเร็วเป็นลบ (ถอยหลัง)
    analogWrite(PWM1, -speed);  // ปรับความเร็วมอเตอร์ 1 สำหรับการถอยหลัง
    digitalWrite(INA1, HIGH);   // หมุนมอเตอร์ 1 ถอยหลัง
    digitalWrite(INB1, LOW);
    analogWrite(PWM2, -speed);  // ปรับความเร็วมอเตอร์ 2 สำหรับการถอยหลัง
    digitalWrite(INA2, HIGH);   // หมุนมอเตอร์ 2 ถอยหลัง
    digitalWrite(INB2, LOW);
  } else {                    // หากไม่มีการเคลื่อนไหว (ความเร็วเป็น 0)
    analogWrite(PWM1, 0);     // หยุดมอเตอร์ 1
    digitalWrite(INA1, LOW);  // ปิดการหมุนของมอเตอร์ 1
    digitalWrite(INB1, LOW);
    analogWrite(PWM2, 0);     // หยุดมอเตอร์ 2
    digitalWrite(INA2, LOW);  // ปิดการหมุนของมอเตอร์ 2
    digitalWrite(INB2, LOW);
  }

  // การควบคุมการเลี้ยว
  if (turn > 10) {             // หากการเลี้ยวไปทางขวา
    analogWrite(PWM1, turn);   // ปรับความเร็วมอเตอร์ 1
    digitalWrite(INA1, HIGH);  // หมุนมอเตอร์ 1 ไปทางขวา
    digitalWrite(INB1, LOW);
    analogWrite(PWM2, turn);  // ปรับความเร็วมอเตอร์ 2
    digitalWrite(INA2, LOW);  // หมุนมอเตอร์ 2 ไปทางขวา
    digitalWrite(INB2, HIGH);
  } else if (turn < -10) {     // หากการเลี้ยวไปทางซ้าย
    analogWrite(PWM1, -turn);  // ปรับความเร็วมอเตอร์ 1 สำหรับการเลี้ยวซ้าย
    digitalWrite(INA1, LOW);   // หมุนมอเตอร์ 1 ไปทางซ้าย
    digitalWrite(INB1, HIGH);
    analogWrite(PWM2, -turn);  // ปรับความเร็วมอเตอร์ 2 สำหรับการเลี้ยวซ้าย
    digitalWrite(INA2, HIGH);  // หมุนมอเตอร์ 2 ไปทางซ้าย
    digitalWrite(INB2, LOW);
  }
  int ch4 = adc.readADC(3);      // อ่านค่าจาก Sensor 3
  if (ch4 == 0) {                // ตรวจพบโลหะ
    tone(PIEZO_PIN, 1000, 500);  // เล่นเสียง 1000 Hz
  }

  delay(10);  // หน่วงเวลา 10 มิลลิวินาทีเพื่อให้การทำงานราบรื่น
}
