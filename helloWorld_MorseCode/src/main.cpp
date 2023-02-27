#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// H . . . .
// E . 
// L . - . .
// 0 - - -

// W . - -
// R . - .
// D - . .

int ledPin = 2;

void dot(bool isLast = false) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(isLast? 1000 : 250);
}

void dash(bool isLast = false) {
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(isLast? 1000 : 600);
}

void h(){
    dot();
    dot();
    dot();
    dot(true);
}

void e() {
    dot(true);
}

void l() {
    dot();
    dash();
    dot();
    dot(true);
}

void o(){
    dash();
    dash();
    dash(true);
}

void w() {
    dot();
    dash();
    dash(true);
}

void r() {
    dot();
    dash();
    dot(true);
}

void d() {
    dash();
    dot();
    dot(true);
}


void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    h();
    e();
    l();
    l();
    o();
    delay(2000);
    w();
    o();
    r();
    l();
    d();
    delay(5000);
}