#pragma once
#include <Arduino.h>
#include <vector>

bool initSDCard();
bool readLinesFromSD(const char* path, std::vector<String>& lines);
bool writeJsonToSD(const char* path, const DynamicJsonDocument& doc);
bool readJsonFromSD(const char* path, DynamicJsonDocument& doc);
