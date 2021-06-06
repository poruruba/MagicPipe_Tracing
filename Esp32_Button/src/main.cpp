#include <M5Stickc.h>
#include <BleMouse.h>

BleMouse bleMouse;
#define BTN_WAIT  100

bool btnA_pressed = false;
bool btnB_pressed = false;
bool ble_connected = false;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(M5_LED, OUTPUT);
  digitalWrite(M5_LED, HIGH);

  bleMouse.begin();
}

void loop() {
  M5.update();

  // put your main code here, to run repeatedly:
  if (bleMouse.isConnected())
  {
    if (!ble_connected)
      ble_connected = true;

    if (M5.BtnA.isPressed() && !btnA_pressed)
    {
      btnA_pressed = true;
      digitalWrite(M5_LED, LOW);
      bleMouse.press(MOUSE_LEFT);
      Serial.println("Pressed LEFT");
      delay(BTN_WAIT);
    }
    else if (M5.BtnA.isReleased() && btnA_pressed)
    {
      btnA_pressed = false;
      digitalWrite(M5_LED, HIGH);
      bleMouse.release(MOUSE_LEFT);
      Serial.println("Released LEFT");
      delay(BTN_WAIT);
    }

    if (M5.BtnB.isPressed() && !btnB_pressed)
    {
      btnB_pressed = true;
      bleMouse.press(MOUSE_RIGHT);
      Serial.println("Pressed RIGHT");
      delay(BTN_WAIT);
    }
    else if (M5.BtnB.isReleased() && btnB_pressed)
    {
      btnB_pressed = false;
      bleMouse.release(MOUSE_RIGHT);
      Serial.println("Released RIGHT");
      delay(BTN_WAIT);
    }
  }else{
    if (ble_connected){
      ble_connected = false;
      digitalWrite(M5_LED, HIGH);
    }
  }
}