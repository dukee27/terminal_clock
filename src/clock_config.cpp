#include <clock_config.h>

ClockConfig ClockPresets::minimal(){
    ClockConfig config;
    config.timeFormat = "%H:%M";
    config.showSeconds = false;
    return config;
}

ClockConfig ClockPresets::standard(){
    ClockConfig config;
    config.timeFormat = "%H:%M:%S";
    return config;
}

ClockConfig ClockPresets::full(){
    ClockConfig config;
    config.timeFormat = "%H:%M:%S";
    config.showDate = true;
    config.showMilliseconds = true;
    return config;
}

ClockConfig ClockPresets::american(){
    ClockConfig config;
    config.use12HourFormat = true;
    config.dateFormat = "%m/%d/%Y";
    config.showDate = true;
    return config;
}

ClockConfig ClockPresets::iso(){
    ClockConfig config;
    config.datetimeFormat = "%Y:%m:%dT%H:%M:%S";
    config.showDate = true;
    return config;
}