#pragma once
#include <clock_config.h>
#include <chrono>
#include <string>

class TimeFormatter{
private:
    ClockConfig config;
    void setTimezone(const std::string& tz);
    void restoreTimezone(const std::string& old_tz);

    std::string formatTimeInZone(const std::chrono::system_clock::time_point& time, const std::string& tz);
public:
    TimeFormatter(const ClockConfig& cfg = ClockConfig());
    std::string formatCurrentTime();
    void updateConfig(const ClockConfig& newConfig);
};