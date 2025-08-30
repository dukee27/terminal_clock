#pragma once
#include <clock_config.h>
#include <chrono>
#include <string>

class TimeFormatter{
private:
    ClockConfig config();
public:
    TimeFormatter(const ClockConfig& cfg = ClockConfig());
    std::string formatCurrentTime();
    void updateConfig(const ClockConfig& newConfig);
};