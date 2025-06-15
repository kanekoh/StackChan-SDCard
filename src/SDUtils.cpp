#include "SDUtils.h"
#include <SD.h>
#include <ArduinoJson.h>

bool initSDCard() {
  if (!SD.begin(GPIO_NUM_4, SPI, 25000000)) {
    Serial.println("Failed to initialize SD card on GPIO_NUM_4");
    return false;
  }
  Serial.println("SD card initialized.");
  return true;
}

bool readLinesFromSD(const char* path, std::vector<String>& lines) {
  lines.clear();
  File file = SD.open(path, FILE_READ);
  if (!file) {
    Serial.printf("Failed to open file: %s\n", path);
    return false;
  }

  while (file.available()) {
    String line = file.readStringUntil('\n');
    line.trim();  // 改行・空白の除去
    if (!line.isEmpty()) {
      lines.push_back(line);
    }
  }

  file.close();
  return true;
}


bool writeJsonToSD(const char* path, const JsonDocument& doc) {
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("Failed to open file for writing: %s\n", path);
    return false;
  }

  if (serializeJson(doc, file) == 0) {
    Serial.printf("Failed to write JSON to file: %s\n", path);
    file.close();
    return false;
  }

  file.close();
  return true;
}

bool readJsonFromSD(const char* path, JsonDocument& doc) {
  File file = SD.open(path, FILE_READ);
  if (!file) {
    Serial.printf("Failed to open file for reading: %s\n", path);
    return false;
  }

  DeserializationError error = deserializeJson(doc, file);
  file.close();

  if (error) {
    Serial.printf("Failed to parse JSON from file: %s\n", path);
    return false;
  }

  return true;
}