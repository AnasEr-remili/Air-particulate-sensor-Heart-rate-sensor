void test(){
  Serial.println("OK");
}

void spisd_test() {
    tft.fillScreen(TFT_BLACK);
    if (SD_CS >  0) {
        tft.setTextDatum(MC_DATUM);
        sdSPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
        if (!SD.begin(SD_CS, sdSPI)) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.drawString("SDCard MOUNT FAIL", tft.width() / 2, tft.height() / 2);
        } else {
            uint32_t cardSize = SD.cardSize() / (1024 * 1024);
            String str = "SDCard OK!    Size: " + String(cardSize) + "MB";
            tft.setTextColor(TFT_GREEN, TFT_BLACK);
            tft.drawString(str, tft.width() / 2, tft.height() / 2);
        }
        delay(1000);
    }
}

void writeFile(fs::FS &fs, const char * path, String message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.println(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, String message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.println(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}
