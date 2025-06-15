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

bool initSDCardWithRetry(int maxAttempts = 3, int delayMs = 500) {
  for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
    Serial.printf("[SD INIT] Attempt %d/%d...\n", attempt, maxAttempts);
    if (initSDCard()) {
      Serial.println("[SD INIT] Success");
      return true;
    }
    Serial.println("[SD INIT] Failed. Retrying...");
    delay(delayMs);
  }
  Serial.println("[SD INIT] All attempts failed.");
  return false;
}

bool retrySDCardInit() {
  SD.end();  // 念のためアンマウント
  delay(100);
  return initSDCard();  // 再初期化試行
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