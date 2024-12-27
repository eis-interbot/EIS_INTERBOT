#include <PS2X_lib.h>  // ไลบรารี PS2X สำหรับคอนโทรลเลอร์ PS2
PS2X ps2x;  // สร้างออบเจ็กต์ ps2x สำหรับคอนโทรลเลอร์ PS2
int error = 0;  // ตัวแปรเก็บสถานะการกำหนดค่า
byte type = 0;  // ตัวแปรเก็บชนิดของคอนโทรลเลอร์
byte vibrate = 0;  // ตัวแปรเก็บค่าการสั่นของคอนโทรลเลอร์
void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสารผ่าน Serial ที่ความเร็ว 9600 bps
  // กำหนดค่าพิน 13, 11, 9, 12 สำหรับเชื่อมต่อกับคอนโทรลเลอร์ PS2
  // พร้อมด้วยเปิดการสั่นและการรองรับการเชื่อมต่อหลายครั้ง
  error = ps2x.config_gamepad(13, 11, 9, 12, true, true);
  // อ่านชนิดของคอนโทรลเลอร์ที่เชื่อมต่อ
  type = ps2x.readType();
  delay(5000);
}
void loop() {
  if (error == 1)  // ถ้ามีข้อผิดพลาดในการตั้งค่า ให้หยุดการทำงาน
    return;
  // อ่านสถานะของคอนโทรลเลอร์และเปิดใช้งานการสั่น
  ps2x.read_gamepad(false, vibrate);
  // ตรวจสอบการกดปุ่มต่าง ๆ บนคอนโทรลเลอร์ PS2
  if (ps2x.Button(PSB_START))
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");
  // อ่านค่าการกดปุ่มทิศทาง
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }
  // ปรับการสั่นตามการกดปุ่ม X (PSAB_BLUE)
  vibrate = ps2x.Analog(PSAB_BLUE);
  // ตรวจสอบสถานะใหม่ของปุ่ม
  if (ps2x.NewButtonState()) {
    if (ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if (ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if (ps2x.Button(PSB_L2))
      Serial.println("L2 pressed");
    if (ps2x.Button(PSB_R2))
      Serial.println("R2 pressed");
    if (ps2x.Button(PSB_GREEN))
      Serial.println("Triangle pressed");
  }
  // ตรวจสอบการกดและปล่อยปุ่ม
  if (ps2x.ButtonPressed(PSB_RED))
    Serial.println("Circle just pressed");
  if (ps2x.ButtonReleased(PSB_PINK))
    Serial.println("Square just released");
  if (ps2x.NewButtonState(PSB_BLUE))
    Serial.println("X just changed");
  // อ่านค่าของปุ่ม L1 หรือ R1 และอ่านค่าของ Joystick
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
    Serial.print("Stick Values: ");
    Serial.print(ps2x.Analog(PSS_LY), DEC);  // อ่านค่า Joystick ซ้ายแกน Y
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);  // อ่านค่า Joystick ซ้ายแกน X
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);  // อ่านค่า Joystick ขวาแกน Y
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC); // อ่านค่า Joystick ขวาแกน X
  }
  delay(10);  // หน่วงเวลา 10 ms
}