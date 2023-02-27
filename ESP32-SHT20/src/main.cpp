#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <ModbusMaster.h>

#define MAX485_RE_NEG  32
#define MAX485_DE      33

ModbusMaster node;

void preTransmission() {
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission() {
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup() {
  // Initialize control pins
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 9600 baud
  Serial.begin(9600);
  Serial1.begin(9600);

  // Modbus slave ID 1
  node.begin(1, Serial1);

  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  // Request 2 registers starting at 0x0001
  uint8_t result = node.readInputRegisters(0x0001, 2);
  // Serial.println(result);

  if (result == node.ku8MBSuccess) {
    // Get response data from sensor
    Serial.print("Temperature: ");
    Serial.print(float(node.getResponseBuffer(0) / 10.00F));
    Serial.print("   Humidity: ");
    Serial.println(float(node.getResponseBuffer(1) / 10.00F));
  }
  if (result == node.ku8MBIllegalFunction) {
    Serial.print("0x01");
  }
  if (result == node.ku8MBIllegalDataAddress) {
    Serial.print("0x02");
  }
  if (result == node.ku8MBIllegalDataValue) {
      Serial.print("0x03");
  }
  if (result == node.ku8MBSlaveDeviceFailure) {
    Serial.print("0x04");
  }
  if (result == node.ku8MBInvalidSlaveID) {
      Serial.print("0xE0");
  }
  if (result == node.ku8MBInvalidFunction) {
    Serial.print("0xE1");
  }
  if (result == node.ku8MBResponseTimedOut) {
      Serial.print("0xE2");
  }
  if (result == node.ku8MBInvalidCRC ) {
    Serial.print("0xE3");
  }
  delay(1000);
}