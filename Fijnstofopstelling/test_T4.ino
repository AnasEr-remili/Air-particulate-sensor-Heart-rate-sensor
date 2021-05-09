#include "T4_V13.h"
#include "RTClib.h"
#include "BluetoothSerial.h"
#include <SD.h>
#include <SoftwareSerial.h>
#include <esp_now.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <Pangodream_18650_CL.h>
#include "battery_01.h"
#include "battery_02.h"
#include "battery_03.h"
#include "battery_04.h"
#include "battery_05.h"

int battery_01Width = 70;
int battery_01Height = 36;
int battery_02Width = 70;
int battery_02Height = 36;
int battery_03Width = 70;
int battery_03Height = 36;
int battery_04Width = 70;
int battery_04Height = 36;
int battery_05Width = 70;
int battery_05Height = 36;

#define ICON_WIDTH 70
#define ICON_HEIGHT 36
#define STATUS_HEIGHT_BAR ICON_HEIGHT
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define ICON_POS_X (tft.width() - ICON_WIDTH)

#define MIN_USB_VOL 4.9
#define ADC_PIN 35
#define CONV_FACTOR 1.8
#define READS 20

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB

Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
BluetoothSerial SerialBT;
SoftwareSerial mySerial(34,32); // 
RTC_DS3231 rtc;

SPIClass sdSPI(VSPI);
#define IP5306_ADDR         0X75
#define IP5306_REG_SYS_CTL0 0x00d

#define button2 38
#define button1 39 

unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
String headerString = "time,pm1,pm2_5,pm10,BPM,AvgBPM";
String dataString = "";
String Timestamp = "";

uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x97, 0xA3, 0x30};

float incomingBPM;
int incomingAVG;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    float BPM;
    int AVG;
} struct_message;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  incomingBPM = incomingReadings.BPM;
  incomingAVG = incomingReadings.AVG;
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) ;
  mySerial.begin(9600);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  if (TFT_BL > 0) {
      pinMode(TFT_BL, OUTPUT);
      digitalWrite(TFT_BL, HIGH);
  }

  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  
  rtc.begin();
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  
  pinoutInit();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  SerialBT.begin("TTGO_T4"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  spisd_test(); 
  writeFile(SD, "/data.txt", "time,pm1,pm2_5,pm10,BPM,AvgBPM");
  SerialBT.println(headerString);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime time = rtc.now();
  Timestamp = time.timestamp(DateTime::TIMESTAMP_TIME);
  tft.fillScreen(BLACK);
  int index = 0;
  char value;
  char previousValue;

  while (mySerial.available()) 
  {
    value = mySerial.read();
    if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d))
    {
      Serial.println("Wachten");
      break;
    }
 
    if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) 
    {
      previousValue = value;
    }
    
    else if (index == 5) 
    {
      pm1 = 256 * previousValue + value;
      Serial.print("{ ");
      Serial.print(pm1);
      Serial.print(", ");      
    }
    else if (index == 7) 
    {
      pm2_5 = 256 * previousValue + value;
      Serial.print(pm2_5);
      Serial.print(", ");
    }
    else if (index == 9) 
    {
      pm10 = 256 * previousValue + value;
      Serial.print(pm10);  
      //test();    
    } 
    else if (index > 15) 
    {
      break;
    }
    index++;
  
 }
  while(mySerial.available()) mySerial.read();
  Serial.println(" }");
  dataString =Timestamp+"," + String(pm1) + "," + String(pm2_5) +"," + String(pm10) + "," + String(incomingBPM) +","+ String(incomingAVG);
  checking();
  battery_info();  
  
  SerialBT.println(dataString);

  delay(2000);
}
