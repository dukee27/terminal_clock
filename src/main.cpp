#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include "time_formatter.h"
#include "clock_config.h"


class InteractiveClockApp{
private:
    ClockConfig config;
    TimeFormatter formatter;
public:
    InteractiveClockApp() : config(ClockPresets::standard()),formatter(config) {}

    void showMenu(){
        std::cout << "\n=== Clock Format Options === \n";
        std::cout << "1. Minimal (HH:MM)\n";
        std::cout << "2. standard (HH:MM::SS)\n";
        std::cout << "3. Full (date + time + ms)\n";
        std::cout << "4. American (12 hour format)\n";
        std::cout << "5. iso \n";
        std::cout << "6. Custom Format\n";
        std::cout << "choose ...";
    }

    void handleUserChoice(int choice){
        switch(choice) {
            case 1: config = ClockPresets::minimal();break;
            case 2: config = ClockPresets::standard();break;
            case 3: config = ClockPresets::full();break;
            case 4: config = ClockPresets::american();break;
            case 5: config = ClockPresets::iso();break;
            case 6: handleCustomFormat();break;
        }
        formatter.updateConfig(config);
    }

    void handleCustomFormat(){
        std::cout<<"enter custom format(eg. %H:%M:%S)";
        std::string customFormat;
        std::getline(std::cin,customFormat);
        config.timeFormat = customFormat;
    }

    void run(){
        std::cout<<"Terminal Clock - Press Ctrl+C to exit\n";

        while(true){
            if(config.clearScreen){
                system("cls");
            }

            std::cout << "Curren Time : " << formatter.formatCurrentTime() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(config.refreshRateMs));
        }
    }

};
int main(){
    ClockConfig config = ClockPresets::full();
    TimeFormatter formatter(config);

    std::cout << "Terminal Clock - Press Ctrl+C to exit\n";
    std::cout << "Current format: Full (Date + Time + Milliseconds)\n\n";

    while(true){
        if(config.clearScreen){
            system("cls");
        }

        std::cout << "Current Time : " << formatter.formatCurrentTime() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(config.refreshRateMs));
    }
    return 0;
}