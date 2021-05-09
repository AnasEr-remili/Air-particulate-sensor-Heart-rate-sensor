void pinoutInit(){
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
}

void drawingText(String text){
  tft.fillRect(0, 0, ICON_POS_X, ICON_HEIGHT,TFT_BLACK);
  tft.setTextDatum(5);
  tft.drawString(text, ICON_POS_X-2, STATUS_HEIGHT_BAR/2, 4);
}

void battery_info()

{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(40, 80);
    tft.print("PM1 ");
    tft.setTextSize(3);
    tft.setCursor(45, 130);
    tft.print(pm1);
    tft.setTextSize(2);
    tft.setCursor(110, 80);
    tft.print("PM2.5 ");
    tft.setTextSize(3);
    tft.setCursor(120, 130);
    tft.print(pm2_5);
    tft.setTextSize(2);
    tft.setCursor(205, 80);
    tft.print("PM10 ");
    tft.setTextSize(3);
    tft.setCursor(210, 130);
    tft.print(pm10);
    tft.setTextSize(2);
    tft.setCursor(200, 5);
    tft.print(Timestamp);
    tft.setTextSize(2);
    tft.setCursor(20, 200);
    tft.print("BPM: ");
    tft.print(incomingAVG);
    
      
    if(BL.getBatteryVolts() >= 4.40){
        int batteryLevel = BL.getBatteryChargeLevel();
        tft.pushImage(10, 5, battery_05Width, battery_05Height, battery_05);
        //drawingText("Chrg");
        tft.setTextSize(3);
        tft.setCursor(90, 12);
        tft.print(String(batteryLevel) + "%");
        tft.setTextSize(2);
        tft.setCursor(250, 40);
        tft.print("Start");
        tft.setTextSize(2);
        tft.setCursor(260, 180);
        tft.print("Stop");
      }
    
    else{
        int batteryLevel = BL.getBatteryChargeLevel();
        if(batteryLevel >=80){
          tft.pushImage(10, 5, battery_04Width, battery_04Height, battery_04);
        }else if(batteryLevel < 80 && batteryLevel >= 50 ){
          tft.pushImage(10, 5, battery_03Width, battery_03Height, battery_03);
        }else if(batteryLevel < 50 && batteryLevel >= 20 ){
          tft.pushImage(10, 5, battery_02Width, battery_02Height, battery_02);
        }else if(batteryLevel < 20 ){
          tft.pushImage(10, 5, battery_01Width, battery_01Height, battery_01);
        }
        tft.setTextSize(3);
        tft.setCursor(90, 12);
        tft.print(String(batteryLevel) + "%");
        //drawingText(String(batteryLevel) + "%");
        tft.setTextSize(2);
        tft.setCursor(250, 40);
        tft.print("Start");
        tft.setTextSize(2);
        tft.setCursor(260, 180);
        tft.print("Stop");
        //drawingText(String(batteryLevel) + "%");
        
    }     
}
