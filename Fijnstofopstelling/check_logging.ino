#define button2 38
#define button1 39
bool logging;

void checking() {
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  
  if (buttonState1 == false) {
    logging = true;
  }

  if (buttonState2 == false) {
    logging = false;
    tft.setTextSize(2);
    tft.setCursor(10, 170);
    tft.print("Ended   log");
  }
  
  if (logging == true) {
    Serial.println("ON EST LA");
    //dataString =Timestamp+"," + String(pm1) + "," + String(pm2_5) +"," + String(pm10) + "," + String(incomingBPM) +","+ String(incomingAVG);
    appendFile(SD, "/data.txt", dataString);
    tft.setTextSize(2);
    tft.setCursor(10, 170);
    tft.print("Started log");
  }

}
