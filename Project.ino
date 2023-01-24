#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ScioSense_ENS160.h"  // ENS160 library
#include <AHTxx.h> // include AHTxx library

ScioSense_ENS160 ens160(ENS160_I2CADDR_1); // I2C address of the ENS160 sensor
AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR); // I2C address and type of the AHT21 sensor

// WiFi and Ubidots constants
#define WIFI_SSID "name"
#define WIFI_PASSWORD "psw"
#define TOKEN "Token"
#define MQTT_CLIENT_NAME "ENS160_Station"

// Variable and device labels for Ubidots
#define VARIABLE_LABEL1 "AQI"
#define VARIABLE_LABEL2 "TVOC"
#define VARIABLE_LABEL3 "eCO2"
#define VARIABLE_LABEL4 "HP0"
#define VARIABLE_LABEL5 "HP1"
#define VARIABLE_LABEL6 "HP2"
#define VARIABLE_LABEL7 "HP3"
#define DEVICE_LABEL "ENS160_Station"
#define VARIABLE_LABEL8 "Temperature"
#define VARIABLE_LABEL9 "Humidity"

// MQTT broker and topic names
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[1000];
char topic1[150];
char topic2[150];
char topic3[150];
char topic4[150];
char topic5[150];
char topic6[150];
char topic7[150];
char topic8[150];
char topic9[150];

// Space to store values to send
char str_AQI[10];
char str_TVOC[10];
char str_eCO2[10];
char str_HP0[10];
char str_HP1[10];
char str_HP2[10];
char str_HP3[10];
char str_temperature[10];
char str_humidity[10];

// WiFi and MQTT client
WiFiClient ubidots;
PubSubClient client(ubidots);

// Callback function for incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.write(payload, length);
  Serial.println(topic);
}

// Function to establish a new MQTT connection
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {
  // Initialize serial communication and ENS160 sensor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ENS160 - Digital air quality sensor");
  if (!ens160.begin()) {
    Serial.println("Could not find a valid ENS160 sensor, check wiring!");
    while (1);
  }
  Serial.println("ENS160 sensor found");
  ens160.setMode(ENS160_OPMODE_STD);  // Set standard mode of operation
  Serial.println("ENS160 sensor set to standard mode");

if (!aht20.begin()) {
Serial.println("Could not find a valid ATH20 sensor, check wiring!");
while (1);
}
Serial.println("ATH20 sensor found");
//aht20.setResolution(AHTXX_14BIT_RESOLUTION); // Set 14-bit resolution
Serial.println("ATH20 sensor set to 14-bit resolution");

  // Connect to WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Waiting for WiFi connection...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected");
   Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);


  // Set MQTT callback function
  client.setCallback(callback);

// Set up the AHT21 sensor
//Wire.begin(); // Start the I2C bus
//aht20.begin(); // Initialize the AHT21 sensor

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  // Perform a measurement and read the sensor values
  ens160.measure(0);
  float aqi = ens160.getAQI();
  float tvoc = ens160.getTVOC();
  float eco2 = ens160.geteCO2();
  float hp0 = ens160.getHP0();
  float hp1 = ens160.getHP1();
  float hp2 = ens160.getHP2();
  float hp3 = ens160.getHP3();

// Read the temperature and humidity from the AHT21 sensor
float temperature = aht20.readTemperature();
float humidity = aht20.readHumidity();



  Serial.println("MQTT connection status: " + String(client.connected()));
  Serial.println("Publishing value for AQI: " + String(aqi));

  // Print out the sensor values for debugging
  Serial.println("MQTT connection status: " + String(client.connected()));
  Serial.println("Publishing value for AQI: " + String(aqi));
  Serial.println("Publishing value for TVOC: " + String(tvoc));
  Serial.println("Publishing value for eCO2: " + String(eco2));
  Serial.println("Publishing value for HP0: " + String(hp0));
  Serial.println("Publishing value for HP1: " + String(hp1));
  Serial.println("Publishing value for HP2: " + String(hp2));
  Serial.println("Publishing value for HP3: " + String(hp3));
   Serial.println("Publishing value for temperature: " + String(temperature));
  Serial.println("Publishing value for humidity: " + String(humidity));

  // Format the values as strings
  dtostrf(aqi, 5, 2, str_AQI);
  dtostrf(tvoc, 5, 2, str_TVOC);
  dtostrf(eco2, 5, 2, str_eCO2);
  dtostrf(hp0, 5, 2, str_HP0);
  dtostrf(hp1, 5, 2, str_HP1);
  dtostrf(hp2, 5, 2, str_HP2);
  dtostrf(hp3, 5, 2, str_HP3);
  dtostrf(temperature, 5, 2, str_temperature);
  dtostrf(humidity, 5, 2, str_humidity);



  // Ensure MQTT connection
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Send values to Ubidots through MQTT


  sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_AQI);
  
  client.publish(topic1, payload);


  sprintf(topic2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL2);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_TVOC);

  delay(500);
  client.publish(topic2, payload);

  sprintf(topic3, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL3);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_eCO2);
  
  delay(1000);
  client.publish(topic3, payload);

 sprintf(topic4, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL4);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_HP0);

 // client.publish(topic4, payload);

  sprintf(topic5, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL5);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_HP1);
 
 // client.publish(topic5, payload);


 sprintf(topic6, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL6);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_HP2);
 
 // client.publish(topic6, payload);

  sprintf(topic7, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL7);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_HP3);

  //client.publish(topic7, payload);


  sprintf(topic8, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL8);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_temperature);
 
  delay(1500);
  client.publish(topic8, payload);

  sprintf(topic9, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL9);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_humidity);

  delay(2000);
  client.publish(topic9, payload);

  Serial.println("Data sent to Ubidots");

  // Wait 30 minute before next measurement
  delay(1800000);
}

