#include "pitches.h"  // ไฟล์ pitches.h จะประกอบด้วยการกำหนดค่าความถี่ของโน้ตต่าง ๆ
int melody[] = {      // อาร์เรย์ของโน้ตที่ต้องการเล่น
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {  // อาร์เรย์ของความยาวโน้ต (ตัวเลขนี้บ่งบอกถึงส่วนของ 1 วินาที เช่น 4 หมายถึงโน้ตตัวหนึ่งยาว 1/4 วินาที)
  4, 8, 8, 4, 4, 4, 4, 4
};
void setup() {  // วนลูปเพื่อเล่นแต่ละโน้ตในเมโลดี้
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];  // คำนวณระยะเวลาของแต่ละโน้ต (1 วินาทีหารด้วยค่าในอาร์เรย์ noteDurations)
    tone(8, melody[thisNote], noteDuration);            // เล่นโน้ตที่พิน 8 โดยกำหนดความถี่ตามโน้ตที่อยู่ใน melody[]
    int pauseBetweenNotes = noteDuration * 1.30;        // กำหนดเวลาหยุดพักระหว่างโน้ต โดยหน่วงเวลามากกว่าโน้ตที่เล่นเล็กน้อย (30% เพิ่มเติม)
    delay(pauseBetweenNotes);                           // หน่วงเวลาการพักระหว่างโน้ต
    noTone(8);                                          // หยุดเล่นโน้ต
  }
}
void loop() {
  // ว่างเปล่า เนื่องจากไม่ต้องการทำอะไรในลูปหลัก
}