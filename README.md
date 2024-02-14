# ENS160-AHT21
Iot Poject to send data to Ubidots with this sensor  ENS160+AHT21

Project Overview:

This GitHub repository contains the source code for an air quality and environmental monitoring system that leverages the ESP8266 WiFi module and the ScioSense ENS160 and AHT20 sensors. The system collects data on air quality metrics (AQI, TVOC, eCO2, HP0-3) and environmental conditions (temperature, humidity), transmits it to the Ubidots cloud platform via MQTT, and makes it accessible for visualization and analysis.

Key Components and Functionalities:

Hardware:
ESP8266 WiFi module: Facilitates wireless communication with the Ubidots cloud.
ScioSense ENS160 sensor: Detects and measures various air quality gases.
AHT20 sensor: Measures temperature and humidity.
Software:
Arduino IDE: Used to develop and upload the code to the ESP8266.
Ubidots platform: Provides a cloud-based environment for data storage, visualization, and analysis.
Libraries:
Wire.h: Enables I2C communication for sensor interaction.
ESP8266WiFi.h: Connects the ESP8266 to a WiFi network.
PubSubClient.h: Handles MQTT communication with Ubidots.
ScioSense_ENS160.h: Interacts with the ENS160 sensor.
AHTxx.h: Interacts with the AHT20 sensor.
Workflow:
Initialization:
Connects to WiFi network.
Establishes an MQTT connection with Ubidots.
Initializes ENS160 and AHT20 sensors.
Data Acquisition:
Takes measurements from both sensors at regular intervals.
Data Formatting:
Converts sensor readings into appropriate data types (e.g., floats, strings).
MQTT Publishing:
Constructs MQTT topics and payloads based on Ubidots' data structure.
Publishes values for AQI, TVOC, eCO2, HP0-3, temperature, and humidity to Ubidots.
Looping:
Repeats the above steps at user-defined intervals.
Target Users:

Makers and hobbyists interested in DIY air quality and environmental monitoring projects.
Developers and professionals looking for an adaptable solution for air quality sensing and data transmission.
Educators and researchers using air quality data for academic or research purposes.
Benefits:

Remote Monitoring: Track air quality and environmental conditions from anywhere with internet access.
Visualization and Analysis: Utilize Ubidots' interactive dashboards and tools to gain insights from the collected data.
Cost-Effectiveness: Employs readily available and affordable hardware and software components.
Customization: Modify the code to suit specific data requirements, transmission intervals, and cloud platforms.
Getting Started:

Clone or download the GitHub repository.
Install the required libraries in your Arduino IDE.
Configure the WiFi credentials and Ubidots token in the code.
Connect your ESP8266 board, sensors, and power supply.
Upload the code to the ESP8266 board.
Observe the serial output for monitoring and troubleshooting.
Access your Ubidots dashboard to view the published data and create visualizations or applications.
Additional Notes:

Consider safety precautions when working with electrical components.
Ensure proper sensor mounting and calibration for accurate readings.
Explore Ubidots' resources and learning materials for advanced data manipulation and analysis.
Feel free to provide feedback or contribute to the project's development.

