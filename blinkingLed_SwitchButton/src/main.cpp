#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void setup()
{
    Serial.begin(115200);
    pinMode(1, OUTPUT);
    pinMode(5, INPUT_PULLUP);
}

void loop()
{
    bool pushButton = digitalRead(5);
    if (pushButton) {
        Serial.println("HIGH");
        digitalWrite(1, LOW);
    } else{
        Serial.println("LOW");
        digitalWrite(1, HIGH);
    }
}