
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHT_SENSOR_PIN  22 // ESP32 pin GIOP21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11
#define LIGHT_SENSOR_PIN 34 // ESP32 pin GIOP36 (ADC0)

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const char* ssid = "Kartik 2.4Ghz";
const char* password = "9990358387";
const char* serverName = "http://937d-110-235-217-112.in.ngrok.io";
String response = "";

int Gas_analog = 4;    // used for ESP32
int Gas_digital = 2;   // used for ESP32
float ldr_area = 0.9625;

void setup() {
  Serial.begin(9600);
  dht_sensor.begin(); 
  pinMode(Gas_digital, INPUT);

  // begin Wifi connect
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //end Wifi connect
}

void api_call(String url){
  HTTPClient http;
  http.begin(url);
  http.GET();
  response = http.getString();
  http.end();
  }

void loop() {
  // read humidity
  float humi  = dht_sensor.readHumidity();
  api_call(String(serverName)+String("/humidity/")+String(humi));
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    api_call(String(serverName)+String("/temp/")+String(tempC));
    Serial.print("°C  ~  ");
    Serial.print(tempF);
    Serial.println("°F");
  }

  // wait a 2 seconds between readings
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading
  api_call(String(serverName)+String("/ldr/")+String(analogValue));

  // We'll have a few threshholds, qualitatively determined
  //converting resistance to light intensity(luminions flux)
   
  
  if (analogValue < 40) {
    Serial.println(" => Dark");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
  } else {
    Serial.println(" => Very bright");
  }


  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
  api_call(String(serverName)+String("/gas_analog/")+String(gassensorAnalog));
  Serial.print("\t");
  Serial.print("Gas Class: ");
  Serial.print(gassensorDigital);
  Serial.print("\t");
  Serial.print("\t");

  if (gassensorAnalog > 1000) {
    Serial.println("Gas");
  }
  else {
    Serial.println("No Gas");
  }
 
  
}
