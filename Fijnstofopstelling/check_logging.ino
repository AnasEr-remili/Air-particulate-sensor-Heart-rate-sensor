// Voor het Checken de logstatus
// Wanneer men op de linkerknop drukt (38) start men het lokaal te loggen
// Wanneer men op de rechterknop drukt (39) stopt men het lokaal loggen.


#define button1 38
#define button2 39
bool logging;

void checking() {
  int buttonState1 = digitalRead(button1);
  if (buttonState1 == false) {
    logging = true;
  }

  int buttonState2 = digitalRead(button2);
  if (buttonState2 == false) {
    logging = false;
    tft.setTextSize(2);
    tft.setCursor(0, 90);
    tft.print("Ended    log");
  }
  if (logging == true) {
    Serial.println("ON EST LA");
    dataString = String(beatsPerMinute) + "," + String(beatAvg) + ";";
    appendFile(SD, "/data.txt", dataString);
    tft.setTextSize(2);
    tft.setCursor(0, 90);
    tft.print("Starting log");
  }

}
