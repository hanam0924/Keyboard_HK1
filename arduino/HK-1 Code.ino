#include <Keyboard.h>

#define MACRO_KR_ENTER 255 

struct KeyButton {
  int pin;
  int keyCode;
  String keyName;
  bool lastState;
};

// ==========================================
// [Current mapping]
// Make sure this part matches the actual wiring.
// ==========================================

KeyButton keys[] = {
  {9,  '0', "0", HIGH},          // When pin 9 is pressed -> 0
  {8,  'h', "h", HIGH},          // When pin 8 is pressed -> h
  {7,  't', "t", HIGH},          // When pin 7 is pressed -> t
  {6,  'u', "u", HIGH},          // When pin 6 is pressed -> u
  {5,  'o', "o", HIGH},          // When pin 5 is pressed -> o
  {4,  'y', "y", HIGH},          // When pin 4 is pressed -> y
  {3,  'n', "n (PIN 3)", HIGH},  // When pin 3 is pressed -> n
  {2,  'h', "h", HIGH},          // When pin 2 is pressed -> h
  {10, '9', "9", HIGH},          // When pin 10 is pressed -> 9 (Caution: No.9 pin)
  {16, '2', "2", HIGH},          // When pin 16 is pressed -> 2 (Caution: No.2 pin)
  {14, '4', "4", HIGH},          // When pin 14 is pressed -> 4 (Caution: No.4 pin)
  {15, '!', "!", HIGH},          // When pin 15 is pressed ->!
  {18, '@', "@", HIGH},          // When pin 18 (A0) is pressed -> @
  {19, '#', "#", HIGH},          // When pin 19 (A1) is pressed -> #
  {20, '$', "$", HIGH},          // When pin 20 (A2) is pressed -> $
  {21, MACRO_KR_ENTER, ".KR+Enter", HIGH} // No. 21 (A3) pin -> kr macro
};

const int keyCount = sizeof(keys) / sizeof(KeyButton);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  
  for (int i = 0; i < keyCount; i++) {
    pinMode(keys[i].pin, INPUT_PULLUP);
  }
  Serial.println("--- KEY MAPPING CHECK START ---");
}

void loop() {
  for (int i = 0; i < keyCount; i++) {
    int currentState = digitalRead(keys[i].pin);

    if (currentState != keys[i].lastState) {
      delay(10); 
      
      if (digitalRead(keys[i].pin) == currentState) {
        
        // When you press it (LOW)
        if (currentState == LOW) {
          
          // [Output diagnostic messages]
          // Serial monitor shows "Pin pressed several times -> What key is sent"
          Serial.print("[PIN ");
          Serial.print(keys[i].pin);
          Serial.print("] detected -> Sending: ");
          Serial.println(keys[i].keyName);

          // [Actual Key Input Behavior]
          if (keys[i].keyCode == MACRO_KR_ENTER) {
            Keyboard.print(".kr");
            Keyboard.write(KEY_RETURN);
          } else {
            Keyboard.press(keys[i].keyCode);
          }
        } 
        // When you take it off (HIGH)
        else {
          if (keys[i].keyCode != MACRO_KR_ENTER) {
            Keyboard.release(keys[i].keyCode);
          }
        }
        
        keys[i].lastState = currentState;
      }
    }
  }
}
