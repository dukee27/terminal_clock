#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>

int main(){
    while(true){
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);

        system("cls");
        std::cout<< std::put_time(std::localtime(&time_t),"%H:%M:%S");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}