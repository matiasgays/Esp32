#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>

#define LED 2
#define WIFI_SSID "WK"
#define WIFI_PASSWORD "15581849"

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Starting..");
}

bool isConnected = false;

void loop() {
  if(WiFi.status() == WL_CONNECTED && ! isConnected){
    Serial.println("Conected");
    digitalWrite(LED, HIGH);
    isConnected = true;
    Serial.print("Got IP: ");  
    Serial.println(WiFi.localIP());
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(bmp.readTemperature())
                          + "&value2=" + String(bmp.readAltitude()) + "&value3=" + String(bmp.readPressure()/100.0F) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BMP180 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BMP180&location=Home&value1=24.75&value2=49.54&value3=1005.14";
// Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(5000);  
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    digitalWrite(LED, !digitalRead(LED));
    delay(500);
    isConnected = false;
  }
}