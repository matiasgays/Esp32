#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define BUTTON_PIN 4
#define RELAY_PIN 3
#define BUZZER_PIN 15
#define COFFEE_TIME 10 * 1000
#define BUZZER_TIME 5 * 1000

void setup()
{
    Serial.begin(115200);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

}

unsigned long cofeeReadyTime;
unsigned long buzzerOffTime;

bool isButtonPressed() {
    return digitalRead(BUTTON_PIN);
}

bool isRelayOn() {
    return digitalRead(RELAY_PIN);
}

bool isBuzzerOn() {
    return digitalRead(BUZZER_PIN);
}

void switchOnRelay() {
    Serial.println("Switching relay on");
    digitalWrite(RELAY_PIN, HIGH);
    cofeeReadyTime = millis() + COFFEE_TIME;
    return;
}

void switchOffRelay() {
    Serial.println("Switching relay off");
    digitalWrite(RELAY_PIN, LOW);
    return;
}

void swicthOnBuzzer() {
    Serial.println("Switching buzzer on");
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerOffTime = millis() + BUZZER_TIME;
    return;
}

void swicthOffBuzzer() {
    Serial.println("Switching buzzer off");
    digitalWrite(BUZZER_PIN, LOW);
    return;
}

void loop()
{
    if (isButtonPressed() && !isRelayOn()){
        switchOnRelay();
    }

    if (!isButtonPressed() && cofeeReadyTime < millis()){
        switchOffRelay();
        swicthOnBuzzer();
    }

    if(isBuzzerOn() && buzzerOffTime < millis()) {
        swicthOffBuzzer();
    }
}