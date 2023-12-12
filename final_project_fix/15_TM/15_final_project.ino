#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <AsyncElegantOTA.h>
#include "DHT.h"
#include <math.h>
#include <HTTPClient.h>
#include "time.h"
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

LiquidCrystal_I2C lcd2(0x27, 20, 4);


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200; 
const int   daylightOffset_sec = 0;

// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycbztEVyCrQqw3tPDye-r8Y7WkQQEpL4nZNC60RJNzY8VTVtgiXUzr-O-IJaWdqiUUAPl";    // change Gscript ID
int count = 0;

#define DHTPIN 4
#define DHTTYPE DHT22
#define smokePin 34
#define firePin 18
#define pirPin 2
#define ldrPin 36
#define buzzerPin 25
#define ledRPin 14
#define ledGPin 12
#define ledBPin 13
#define ledYPin 19
#define dcFanPin 35

// Access Point Credentials
const char* ssid_ap = "Devin_ESP32";
const char* password_ap = "@Devin373";

// WiFi Credentials
const char* ssid_wifi = "Devin";
const char* password_wifi = "@Devin737";

// Init DHT Sensor
DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

// String Variables for PIR and Fire Digital Sensor
String pirState;
String fireState;

int smokeValue = 0;
double ppm = 0;
double pressure = 0;
int ldrValue = 0;
double lux = 0;
double t = 0, h = 0, f = 0, hic = 0, hif = 0;
bool buzzerState;
int R_cycle = 1000, Y_cycle = 1000;

// Create a sensor object
Adafruit_BMP280 bmp; // BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)

// Get Sensor Readings and return JSON object
String getSensorReadings(){
  readings["temperatureC"] = String(t);
  readings["humidity"] =  String(h);
  readings["temperatureF"] = String(f);
  readings["heatIndexC"] =  String(hic);
  readings["heatIndexF"] = String(hif);
  readings["smoke_sensor"] =  String(ppm);
  readings["pressure_sensor"] = String(pressure);
  readings["LDR"] =  String(lux);
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

// Read digital Sensor and convert to string display
String readPIR() {
  if(digitalRead(pirPin)){
    pirState = "Aktivitas Terdeteksi";
  } else {
    pirState = "Tidak Ada Aktivitas";
  }
  Serial.println(pirState);
  return pirState;
}

String readFire() {
  if(!digitalRead(firePin)){
    fireState = "Ada Api, Berbahaya!";
  } else {
    fireState = "Tidak Ada Api, Aman!";
  }
  Serial.println(fireState);
  return fireState;
}

// Function untuk proses output sensor digital PIR dan Fire 
String processor(const String& var) {
  Serial.println(var);
  if(var == "STATEPIR"){
    pirState = readPIR();
    return pirState;
  } else if(var == "STATEFIRE") {
    fireState = readFire();
    return fireState;
  }
  return String();
}

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_wifi, password_wifi);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// Initialize Access Point
void initAP() {
  Serial.print("Setting AP (Access Point)...");
  WiFi.softAP(ssid_ap, password_ap);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void TaskSensors(void *parameters) {
  esp_task_wdt_reset();
  HTTPClient http;
  for(;;) {
    esp_task_wdt_reset();
    // LDR sensor
    ldrValue = analogRead(ldrPin);
    Serial.print("LDR sensor value: ");
    Serial.println(ldrValue);
    double Vldr = 3.3/4095 * ldrValue;
    double Rldr = (10 * Vldr) / (3.3 - Vldr); // kOhm
    lux = -90 * ((Rldr - 3.3) / 15) + 100;
    if (lux < 0){
      lux = 0;
    }
    Serial.print("Light Intensity in lux: ");
    Serial.println(lux);
    
    // BMP Sensor
    pressure = bmp.readPressure() / 100; // Pressure in hPa
    Serial.print("Pressure in hPa: ");
    Serial.println(pressure);
    
    // Smoke Sensor
    smokeValue = analogRead(smokePin);
    Serial.print("MQ2 sensor value: ");
    Serial.println(smokeValue);
    double Vrl = smokeValue * (3.3/4095);
    double R = ((3.3/Vrl) - 1);
    double ratio = R/20;
    ppm = (pow(10, ((log10(ratio) - 0.42) / -0.263))) / 3000; // use formula to calculate ppm
    Serial.print("PPM Value: ");
    Serial.println(ppm); // print ppm
    
    esp_task_wdt_reset();
    
    // DHT Sensor
    h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    esp_task_wdt_reset();
    // Compute heat index in Fahrenheit (the default)
    hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" || ");
    Serial.println(f);
    Serial.print("Heat Index: ");
    Serial.print(hic);
    Serial.print(" || ");
    Serial.println(hif);
    Serial.print("Humidity: ");
    Serial.println(h);

    Serial.print("PIR State: ");
    Serial.println(pirState);
    Serial.print("Fire State: ");
    Serial.println(fireState);

    esp_task_wdt_reset();
    
    // Data Logging to Script and Time Extraction
    if (WiFi.status() == WL_CONNECTED) {
      static bool flag = false;
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
      }
      char timeStringBuff[50]; //50 chars should be enough
      strftime(timeStringBuff, sizeof(timeStringBuff), "%A,%d-%B-%Y||%H:%M:%S", &timeinfo);
      String asString(timeStringBuff);
      Serial.print("Time:");
      Serial.println(asString);

      String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "date=" + String(asString) + 
      "&sensor=" + String(count) + 
      "&tempC=" + String(t) + 
      "&tempF=" + String(f) + 
      "&heatIndexC=" + String(hic) + 
      "&heatIndexF=" + String(hif) + 
      "&humidity=" + String(h) + 
      "&ppm=" + String(ppm) + 
      "&ldr=" + String(lux) + 
      "&pressure=" + String(pressure) + 
      "&fireStatus=" + String(!digitalRead(firePin)) + 
      "&activityStatus=" + String(digitalRead(pirPin));
      esp_task_wdt_reset();
      Serial.print("POST data to spreadsheet:");
      Serial.println(urlFinal);
      http.begin(urlFinal.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET(); 
      Serial.print("HTTP Status Code: ");
      Serial.println(httpCode);

      //getting response from google sheet
      String payload;
      if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: "+payload);    
      }
      http.end();
    }
    count++;
    esp_task_wdt_reset();
    
    // Update Pembacaan Sensor ke Web Server
    if ((millis() - lastTime) > timerDelay) {
      // Send Events to the client with the Sensor Readings Every 1 seconds
      events.send("ping", NULL, millis());
      events.send(getSensorReadings().c_str(), "new_readings", millis());
      lastTime = millis();
    }
  }
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void TaskActuators(void *parameters) {
  esp_task_wdt_reset();

  // LCD 20x4 Init
  lcd2.init();
  lcd2.backlight();
  lcd2.setCursor(0, 0);
  lcd2.print("Sistem Monitoring Ruangan Otomatis");
  lcd2.setCursor(0, 1);
  lcd2.print("dan Berbasis IoT pada Web Server");

  // OLED Init
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(32, 10);       // set position to display
  oled.println("FINPRO SISTEM"); // set text
  oled.setCursor(32, 20);       // set position to display
  oled.println("BENAM PRAKTIKUM"); // set text
  oled.display();              // display on OLED

  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(3, 8000, 12);
  ledcAttachPin(ledRPin, 0);
  ledcAttachPin(ledYPin, 1);
  ledcAttachPin(buzzerPin, 3);
  buzzerState = 1;
  delay(2000);
  lcd2.clear();
  oled.clearDisplay();

  for(;;) {
    esp_task_wdt_reset();
    // Print initial message on the LCD
    lcd2.setCursor(0, 0);
    lcd2.print("Room Temp: ");
    lcd2.print(t);
    lcd2.print(" C       ");
    lcd2.setCursor(0, 1);
    lcd2.print("Humidity: ");
    lcd2.print(h);
    lcd2.print(" %       ");
    lcd2.setCursor(0, 2);
    lcd2.print("Pressure: ");
    lcd2.print(f);
    lcd2.print(" F       ");
    lcd2.setCursor(0, 3);
    lcd2.print("Light: ");
    lcd2.print(lux);
    lcd2.print(" lux     ");

    oled.setTextSize(1);            // set text size
    oled.setTextColor(WHITE);       // set text color
    oled.setCursor(0, 5);          // set position to display
    oled.println("Tekanan Udara");  // set text
    oled.setCursor(0, 20);          // set position to display
    oled.print(pressure);           // set text    
    oled.print(" hPa");             // set text  
    oled.setCursor(0, 35);    
    oled.println("Kualitas Udara"); // set text
    oled.setCursor(0, 50);          // set position to display
    oled.print(ppm);                // set text 
    oled.println(" ppm");           // set text 
    oled.display();                 // display on OLED

    unsigned long currentMillis = millis();
    Serial.print("State Fire Alarm = ");
    Serial.println(digitalRead(firePin));
    if(digitalRead(firePin) == 0) {
      digitalWrite(ledBPin, LOW);
      digitalWrite(ledGPin, LOW);
      if(buzzerState == 1) {
        ledcWrite(0, 0);
        ledcWrite(1, Y_cycle);
        ledcWriteTone(3, 800);
        delay(100);
        buzzerState = 0;
      } else {
        ledcWrite(0, R_cycle);
        ledcWrite(1, 0);
        ledcWriteTone(3, 2500);
        delay(100);
        buzzerState = true;
      }
    } else {
      digitalWrite(ledGPin, HIGH);
      digitalWrite(ledBPin, HIGH);
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      ledcWriteTone(3, 0);
      delay(1000);
    }

    // Menyalakan kipas saat panas
    if (t > 30) {
      digitalWrite(dcFanPin, HIGH);
    } else {
      digitalWrite(dcFanPin, LOW);
    }
  }
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(smokePin, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  pinMode(ledYPin, OUTPUT);
  pinMode(dcFanPin, OUTPUT);
  pirState = readPIR();
  fireState = readFire();
  bmp.begin(0x76);
  // init bmp pressure sensor
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // init DHT22
  dht.begin();

  initWiFi();
  initAP();
  initSPIFFS();
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.serveStatic("/", SPIFFS, "/");

  // Request for the latest sensor readings
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
  });

  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  // Start Elegant OTA
  AsyncElegantOTA.begin(&server);

  // Start server
  server.begin();

  // Task Begin 
  xTaskCreatePinnedToCore(
                  TaskSensors,   /* Task function. */
                  "Sensor and Web Server",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  2,           /* priority of the task */
                  NULL,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */    
  xTaskCreatePinnedToCore(
                  TaskActuators,   /* Task function. */
                  "Actuators",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  NULL,      /* Task handle to keep track of created task */
                  1);          /* pin task to core 1 */  
}

void loop() {
  // loop kosong karena menggunakan multitasking
}
