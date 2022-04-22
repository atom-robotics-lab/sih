
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHT_SENSOR_PIN  4 // ESP32 pin GIOP21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11
#define LIGHT_SENSOR_PIN 34 // ESP32 pin GIOP36 (ADC0)

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define i2c_sda 33
#define i2c_scl 32
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 oled2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const char* ssid = "Wifi";
const char* password = "12345678";
const char* serverName = "http://192.168.69.38:8000";
String response = "";

int Gas_analog = 15;    // used for ESP32
int Gas_digital = 2;   // used for ESP32
float ldr_area = 0.9625;
TwoWire i2coled = TwoWire(0);
void setup() {
  Serial.begin(9600);
  dht_sensor.begin(); 
  pinMode(Gas_digital, INPUT);
  i2coled.begin(i2c_sda, i2c_scl, 400000);
  oled2.begin(SSD1306_SWITCHCAPVCC, 0x3C, &i2coled);

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
  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  
  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  
  oled2.clearDisplay(); // clear display

  oled2.setTextSize(1);         // set text size
  oled2.setTextColor(WHITE);    // set text color
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
    
    oled.setCursor(0, 10);       // set position to display
              // display on OLED
  oled.print("Temp:  ");
  oled.println(tempC); // set text
  oled.println();
  oled.print("Humidity:  ");
  oled.println(humi);
  oled.println();
  oled2.println("Temp:  ");
  

  // wait a 2 seconds between readings
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading
  api_call(String(serverName)+String("/ldr/")+String(analogValue));
  oled.print("Light Intensity: ");
  oled.println(analogValue);
  

  // We'll have a few threshholds, qualitatively determined
  //converting resistance to light intensity(luminions flux)
   
  
  if (analogValue < 40) {
    Serial.println(" => Dark");
    oled.println();
    oled.print("Category :(Dark)");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
    oled.println();
    oled.print("Category :(Dim)");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
    oled.println();
    oled.print("Category :(Light)");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
    oled.println();
    oled.print("Category :(Bright)");
  } else {
    Serial.println(" => Very bright");
    oled.println();
    oled.print("Category :(Very bright)");
  }
  oled.display();  
  oled.clearDisplay();


  int gassensorAnalog = random(100, 120);
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
    Serial.println("Gas not detected");
  }
 
  
}
