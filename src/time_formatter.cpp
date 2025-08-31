#include "time_formatter.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

//this initializes directly to default
TimeFormatter::TimeFormatter(const ClockConfig& cfg ) : config(cfg){};

void TimeFormatter::setTimezone(const std::string& tz){
    #ifdef _WIN32
        std::string tz_string = "TZ=" + tz;;
        _putenv(tz_string.c_str());
    #else 
        setenv("TZ",tz.c_str(),1);
    #endif
    tzset();
}

void TimeFormatter::restoreTimezone(const std::string& old_tz){
    #ifdef _WIN32
        std::string tz_string = "TZ=" + old_tz;;
        _putenv(tz_string.c_str());
    #else 
        setenv("TZ",old_tz.c_str(),1);
    #endif
    tzset();
}

std::string TimeFormatter::formatTimeInZone(const std::chrono::system_clock::time_point& time, const std::string& tz){
    const char* current_tz = getenv("TZ");
    std::string old_tz = current_tz ? current_tz:"";

    if(tz != "local"){
        setTimezone(tz);
    }

    auto time_t = std::chrono::system_clock::to_time_t(time);
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
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) % 1000;
        result << "." << std::setfill('0') << std::setw(3) << ms.count();
    }
    if(config.showTimezone){
        char tzbuffer[16];
        std::strftime(tzbuffer,sizeof(tzbuffer)," %Z",timeinfo);
        result<<tzbuffer;
    }
    restoreTimezone(old_tz);
    return result.str();
}
std::string TimeFormatter::formatCurrentTime(){
    using namespace std::chrono;

    auto now = system_clock::now();
    auto time_t = system_clock::to_time_t(now);
    if(!config.showMultipleTimezone){
        return formatTimeInZone(now,config.timezone);
    }
    else{
        std::ostringstream oss;
        std::vector<std::pair<std::string,std::string>> zones;

        zones.emplace_back("Local","local");
        for(const auto& tz: config.additionalZones){
            std::string displayName = tz;
            if(tz == "America/New_York") displayName = "New York";
            else if(tz == "Europe/London") displayName = "London";
            else if(tz == "Asia/Tokyo") displayName = "Tokyo";
            
            zones.emplace_back(displayName,tz);
        }

        for(size_t i = 0 ; i < zones.size(); ++i){
            oss << std::setw(10) << zones[i].first <<": " << formatTimeInZone(now,zones[i].second) ;
            if(i < zones.size() -1){
                oss << "\n";
            }
        }
        return oss.str();
    }
}

void TimeFormatter::updateConfig(const ClockConfig& newConfig){
    config = newConfig;
}