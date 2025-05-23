#include "SDUtils.h"
#include <SD.h>

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
