#pragma once
#include <string>

class ClockConfig{
public:
    std::string timeFormat = "%H:%M:%S";
    std::string dateFormat = "%Y:%m:%d";
    std::string datetimeFormat = "%Y:%m:%d %H:%M:%S";

    bool showDate = false;
    bool showSeconds = true;
    bool showMilliseconds = false;
    bool use12HourFormat = false;
    
    int refreshRateMs = 1000;

    std::string textColor = "white";
    bool clearScreen = true;
};

class ClockPresets{
public:
    static ClockConfig minimal();
    static ClockConfig standard();
    static ClockConfig full();
    static ClockConfig american();
    static ClockConfig iso();
};