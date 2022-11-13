#include <Arduino.h>

int rows[3] = {A7, A1, A6};
int columns[4] = {A3, A4, A5, A0};

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
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(rows[i], HIGH);
    for (int j = 0; j < 4; j++)
    {
      if (digitalRead(columns[j]))
      {
        Serial.print("Button row: ");
        Serial.print(rows[i]);
        Serial.print("; col: ");
        Serial.println(columns[j]);
      }
    }
    digitalWrite(rows[i], LOW);
  }
  delay(100);
}