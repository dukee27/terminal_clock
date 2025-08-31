#pragma once
#include <string>
#include <vector>
class ClockConfig{
public:
    std::string timeFormat = "%H:%M:%S";
    std::string dateFormat = "%Y:%m:%d";
    std::string datetimeFormat = "%Y:%m:%d %H:%M:%S";

    bool showDate = false;
    bool showSeconds = true;
    bool showMilliseconds = false;
    bool use12HourFormat = false;

    std::string timezone = "local";

    bool showTimezone = false;
    bool showMultipleTimezone = false;
    
    std::vector<std::string> additionalZones;
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
    static ClockConfig withTimezone(const std::string& tz);
    static ClockConfig worldClock();
};