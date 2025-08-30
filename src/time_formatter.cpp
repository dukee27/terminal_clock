#include "time_formatter.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>


TimeFormatter::TimeFormatter(const ClockConfig& cfg ) : config(cfg){};

std::string TimeFormatter::formatCurrentTime(){
    using namespace std::chrono;

    auto now = system_clock::now();
    auto time_t = system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&time_t);

    std::ostringstream result;

    if(config.showDate){
        char dateBuffer[100];
        std::strftime(dateBuffer,sizeof(dateBuffer),config.dateFormat.c_str(),timeinfo);
        result << dateBuffer << " ";
    }

    char timeBuffer[100];
    std::string activeTimeFormat = config.use12HourFormat ? "%I:%M:%S %p" : config.timeFormat;
    std::strftime(timeBuffer,sizeof(timeBuffer),activeTimeFormat.c_str(),timeinfo);
    result << timeBuffer ;

    if(config.showMilliseconds){
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        result << "." << std::setfill('0') << std::setw(3) << ms.count();
    }
    return result.str();
}

void TimeFormatter::updateConfig(const ClockConfig& newConfig){
    config = newConfig;
}