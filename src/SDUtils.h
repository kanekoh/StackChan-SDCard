#pragma once
#include <Arduino.h>
#include <vector>

bool initSDCard();
bool readLinesFromSD(const char* path, std::vector<String>& lines);
