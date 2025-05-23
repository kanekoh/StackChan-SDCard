
#include <M5Unified.h>
#include <Avatar.h>

#include "SDUtils.h"

using namespace m5avatar;

Avatar avatar;

void outputMessage(String message)
{
  Serial.println(message);
  M5.Display.println(message);
}

void setup()
{
  std::vector<String> wifiLines;
  M5.begin();

  outputMessage("SD card initialization...");
  bool sdCardInitialized = initSDCard();
  if (!sdCardInitialized) {
    outputMessage("SD card initialization failed.");
    return;
  }
  outputMessage("SD card initialization succeeded.");
  delay(2000);

  outputMessage("Reading Wi-Fi settings from SD card...");
  bool readSuccess = readLinesFromSD("/wifi.txt", wifiLines);
  if (readSuccess && wifiLines.size() >= 2) {
    String ssid = wifiLines[0];
    String pass = wifiLines[1];

    outputMessage("SSID: " + ssid);
    outputMessage("Password: xxxxxxx"); // パスワードは表示しない
    outputMessage("Reading Wi-Fi settings from SD card succeeded.");
  } else {
    outputMessage("Failed to read Wi-Fi settings from SD card.");
  }
  delay(2000);

  avatar.init(); // 描画を開始します。
}

void loop()
{
  // アバターの描画は別のスレッドで行われるので、
  // loopループの中で毎回描画をする必要はありません。
}