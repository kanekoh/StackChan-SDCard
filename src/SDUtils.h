#pragma once
#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>

bool initSDCard();
bool initSDCardWithRetry(int maxAttempts, int delayMs);
bool retrySDCardInit();
bool readLinesFromSD(const char* path, std::vector<String>& lines);
bool writeJsonToSD(const char* path, const JsonDocument& doc);
bool readJsonFromSD(const char* path, JsonDocument& doc);
