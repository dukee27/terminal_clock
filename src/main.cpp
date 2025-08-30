#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <atomic>
#include "time_formatter.h"
#include "clock_config.h"


class InteractiveClockApp{
private:
    ClockConfig config;
    TimeFormatter formatter;
    std::atomic<bool> running{true};
    std::atomic<bool> configChanged{false};
    std::mutex configMutex;
public:
    InteractiveClockApp() : config(ClockPresets::standard()),formatter(config) {}

    void showInstruction(){
        std::cout << "\n=== Terminal Clock === \n";
        std::cout << "Commands:\n";
        std::cout << "1. Minimal (HH:MM) | 2. standard (HH:MM::SS) | 3. Full (date + time + ms) \n";
        std::cout << "4. American (12 hour format) | 5. iso\n | 6. Custom Format\n";
        std::cout << "q = quite \n\n";
    }

    void handleUserChoice(int choice){
        
        formatter.updateConfig(config);
    }

    void handleCustomFormat(){
        std::cout<<"enter custom format(eg. %H:%M:%S)";
        std::string customFormat;
        std::getline(std::cin,customFormat);
        config.timeFormat = customFormat;
    }
    void inputThread(){
        std::string input;
        while(running){
            std::getline(std::cin,input);
            if(input.empty()) continue;
            char choice = input[0];

            std::lock_guard<std::mutex> lock(configMutex);

            switch(choice) {
            case '1': config = ClockPresets::minimal();configChanged = true; break;
            case '2': config = ClockPresets::standard();configChanged = true;break;
            case '3': config = ClockPresets::full();configChanged = true;break;
            case '4': config = ClockPresets::american();configChanged = true;break;
            case '5': config = ClockPresets::iso();configChanged = true;break;
            case '6': handleCustomFormat();configChanged = true;break;
            case 'Q':
            case 'q':
                running = false;
                std::cout << "clock is turned off..";
                break;
            }
        }
    }
    void run(){
        showInstruction();
        std::thread inputHandler(&InteractiveClockApp::inputThread,this);

        while(running){
            {
                std::lock_guard<std::mutex> lock(configMutex);
                if(configChanged){
                    formatter.updateConfig(config);
                    configChanged = false;
                }
            }
            if(config.clearScreen){
                system("cls");
                showInstruction();
            }

            std::cout << "Curren Time : " << formatter.formatCurrentTime() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(config.refreshRateMs));
        }
        if(inputHandler.joinable()){
            inputHandler.join();
        }
    }
};
int main(){
    InteractiveClockApp app;
    app.run();
    return 0;
}