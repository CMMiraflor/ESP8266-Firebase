#include <dummy.h>

//wifi and firebase declaration

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <FirebaseError.h>

//humidity sensor declaration
#include "DHT.h"
#define DHTPIN D5  
#define DHTTYPE DHT11 


//firebaseConnection declaration
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

//wifiConnection declaration
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

//humidity and temperature sensor setup
DHT dht(DHTPIN, DHTTYPE);

//soil mositure setup


void setup() {

Serial.begin(115200);

//setups wifi connection
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");

//dht sensor setup
dht.begin();

//error for wifi connection
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}

Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

int soilMoistureFunc(){
  int soil_moisture;
  soil_moisture= analogRead(A0);
  return soil_moisture;
  }
  
float humidityFunc(){
  float humidity;
  humidity = dht.readHumidity();
  }
  
float temperatureFunc(){
  float temperature;
  temperature = dht.readTemperature();
  }



void loop() {

//declaration for values
float temperature;
float humidity;
int soilMoisture;


//getter of data
 soilMoisture = soilMoistureFunc();
 humidity = humidityFunc();
 temperature = temperatureFunc();

//serial prints of what is happening
Serial.print(soilMoisture);
Serial.println();
Serial.print(humidity);
Serial.println();
Serial.print(temperature);
Serial.println();


StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
root["temperature"] = temperature;
root["humidity"] = humidity;
root["soil moisture"] = soilMoisture;

String name = Firebase.push("/sensor/dht", root);

//puts 

if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  
 return;
  }


delay(3000);

}