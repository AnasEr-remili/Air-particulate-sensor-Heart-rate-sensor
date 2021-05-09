#include "T4_V13.h"
#include "icons_battery.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#define MIN_USB_VOL 4.9
#define ADC_PIN 35       // Pin waar de spanningsdeler op aanwezig is voor de batterijspanning te bepalen 
#define CONV_FACTOR 1.8
#define READS 20

Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);

SPIClass sdSPI(VSPI);
#define IP5306_ADDR         0X75
#define IP5306_REG_SYS_CTL0 0x00d

uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x97, 0x05, 0x90};
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB
TFT_eSPI tft = TFT_eSPI();
#define button1 38 // Button voor het starten van het lokaal loggen op sd kaart
#define button2 39 // Button voor het endigen van het lokaal loggen op sd kaart 

MAX30105 particleSensor;
//Syntax van de eerste versie voor BLE
//BluetoothSerial SerialBT;

const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE]; //Array van de hartslagen
byte rateSpot = 0;
long lastBeat = 0; //Tijd waarbij laatste slag op was
float beatsPerMinute;
int beatAvg;
String dataString = "";

// Variabelen om op te slaan als verzending succesvol was
String success;
typedef struct struct_message {
    float BPM;
    int AVG;
} struct_message;

struct_message BPMReadings;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

long interval = 2000;
long previousMillis = 0; 
 

void setup()
{

  tft.init();
  Serial.begin(9600);
  pinoutInit();
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.println("Initializing...");

  //Syntax voor de BLE communicatie van de eerste versie
  //SerialBT.begin("TTGO_T4_Heartrate"); //Bluetooth device name
  //Serial.println("The device started, now you can pair it with bluetooth!");
  
  //Initialisatie van de hartslagsensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");
  
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A); 
  particleSensor.setPulseAmplitudeGreen(0); 
  spisd_test();
  writeFile(SD, "/data.txt", "beatsPerMinute, Average beatsPerMinute");
  //SerialBT.println("beatsPerMinute, Average beatsPerMinute"); Deze lijne code is van de eerste versie voor de BLE
  
}


void loop()
{
  //tft.fillScreen(BLACK);
  test();
  battery_info();
  
  unsigned long currentMillis = millis();
  
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We hebben een slag !
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Opslaan van de reading in een array
      rateSpot %= RATE_SIZE; 

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
  if (irValue < 50000)
  {
    // Hartslagsensor kijkt voor een drempelwaarde van een hartslag
    Serial.print(" No arm?");
    Serial.println();
  }
  else
  {
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.println(beatAvg);
  }
  
  checking();
  
  if(currentMillis - previousMillis >= interval){
  // Verzenden van de hartslagwaardes
  BPMReadings.BPM = beatsPerMinute;
  BPMReadings.AVG = beatAvg;

  // Verzenden van een bericht met ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BPMReadings, sizeof(BPMReadings));
   
  if (result == ESP_OK) { Serial.println("Sent with success");}
  else { Serial.println("Error sending the data"); }
  
  previousMillis = currentMillis;
  }
  

