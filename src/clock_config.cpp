#include <clock_config.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
void ClockConfig::loadFromJson(const std::string& filename ){
    std::ifstream file(filename);
    if(!file){
        return;
    }

    json j;
    file >> j;

    if(j.contains("timeFormat")) timeFormat = j["timeFormat"].get<std::string>();
    if(j.contains("dateFormat")) dateFormat = j["dateFormat"].get<std::string>();
    if (j.contains("showDate")) showDate = j["showDate"].get<bool>();
    if (j.contains("showMilliseconds")) showMilliseconds = j["showMilliseconds"].get<bool>();
    if (j.contains("timezone")) timezone = j["timezone"].get<std::string>();
    if (j.contains("showTimezone")) showTimezone = j["showTimezone"].get<bool>();
    if (j.contains("refreshRateMs")) refreshRateMs = j["refreshRateMs"].get<int>();
    if (j.contains("textColor")) textColor = j["textColor"].get<std::string>();
    if (j.contains("clearScreen")) clearScreen = j["clearScreen"].get<bool>();
}

void ClockConfig::saveToJson(const std::string& filename) const{
    json j;
    j["timeFormat"] = timeFormat;
    j["dateFormat"] = dateFormat;
    j["showDate"] = showDate;
    j["showMilliseconds"] = showMilliseconds;
    j["timezone"] = timezone;
    j["showTimezone"] = showTimezone;
    j["refreshRateMs"] = refreshRateMs;
    j["textColor"] = textColor;
    j["clearScreen"] = clearScreen;

    std::ofstream file(filename);
    if (file) {
        file << j.dump(4); 
    }
}

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

ClockConfig ClockPresets::withTimezone(const std::string& tz){
    ClockConfig config;
    config.timezone = tz;
    config.showTimezone = true;
    return config;
}

ClockConfig ClockPresets::worldClock(){
    ClockConfig config;
    config.showMultipleTimezone = true;
    config.additionalZones = {"UTC","America/New_York","Europe/London","Asia/Tokyo"};
    return config;
}