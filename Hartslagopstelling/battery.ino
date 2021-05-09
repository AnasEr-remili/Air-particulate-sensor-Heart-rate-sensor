// Voor het weergeven van de batterijspanning en batterijpercentage op het scherm


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
    tft.setCursor (0, STATUS_HEIGHT_BAR);
    tft.println("");
    tft.print("Volts: ");
    tft.println(BL.getBatteryVolts());
    tft.print("Charge level: ");
    tft.println(BL.getBatteryChargeLevel());
    tft.setCursor(100,180);
    tft.setTextSize(5);
    tft.print(beatAvg);
  
    
    if(BL.getBatteryVolts() >= 4.40){
        tft.pushImage(170, 5, battery_05Width, battery_05Height, battery_05);
        drawingText("Chrg");
        
      }
    
    else{
        int batteryLevel = BL.getBatteryChargeLevel();
        if(batteryLevel >=80){
          tft.pushImage(170, 5, battery_04Width, battery_04Height, battery_04);
        }else if(batteryLevel < 80 && batteryLevel >= 50 ){
          tft.pushImage(170, 5, battery_03Width, battery_03Height, battery_03);
        }else if(batteryLevel < 50 && batteryLevel >= 20 ){
          tft.pushImage(170, 5, battery_02Width, battery_02Height, battery_02);
        }else if(batteryLevel < 20 ){
          tft.pushImage(170, 5, battery_01Width, battery_01Height, battery_01);
        }
        tft.setTextSize(3);
        tft.setCursor(90, 10);
        tft.print(String(batteryLevel) + "%");
        tft.setTextSize(3);
        tft.setCursor(0, 290);
        tft.print("Start");
        tft.setTextSize(3);
        tft.setCursor(165, 290);
        tft.print("Stop");


        
        
        

        
        
        
        
    }     
}
