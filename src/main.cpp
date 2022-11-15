#include <Arduino.h>
#include "Adafruit_TinyUSB.h"

int rows[3] = {A7, A1, A6};
int columns[4] = {A3, A4, A5, A0};
uint8_t hidcode[] = 
{ 
  HID_KEY_0, 
  HID_KEY_1, 
  HID_KEY_2, 
  HID_KEY_3, 
  HID_KEY_4, 
  HID_KEY_5, 
  HID_KEY_6, 
  HID_KEY_7, 
  HID_KEY_8, 
  HID_KEY_9, 
  HID_KEY_A, 
  HID_KEY_B, 
  HID_KEY_C
};

uint8_t const desc_hid_report[] = 
{
   TUD_HID_REPORT_DESC_KEYBOARD(),
};

Adafruit_USBD_HID usb_hid;

void setup()
{

  for (int i = 0; i < 3; i++)
  {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], LOW);
  }
  for (int i = 0; i < 4; i++)
  {
    pinMode(columns[i], INPUT_PULLDOWN);
  }

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setStringDescriptor("in:control Keyboard");

  usb_hid.begin();

  // wait until device mounted
  while (!USBDevice.mounted())
    delay(1);
}

void loop()
{
  if (!usb_hid.ready())
    return;

  uint8_t count = 0;
  uint8_t keycode[6] = {0};

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(rows[i], HIGH);

    for (int j = 0; j < 4; j++)
    {
      if (digitalRead(columns[j]))
      {
        Serial.println(hidcode[j + i * 4]);
        keycode[count++] = hidcode[j + i * 4];
      }
    }
    digitalWrite(rows[i], LOW);
    if (count >= 5) break;
  }
  if (count)
  {
    usb_hid.keyboardReport(0, 0, keycode);
  }
  else
  {
    usb_hid.keyboardRelease(0);
  }
  delay(2);
}