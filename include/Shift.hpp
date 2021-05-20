#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

#include "./TaxiAgency.hpp"
#include "./Taxi.hpp"
#include "./Driver.hpp"

class Shift{
    private:
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> endTime;
        bool running;
        long time_limit;
        long kms_rode;

        Driver driver_in_charge;
        Taxi car;

        int driver_idol_cost;

    public:
        Shift();
        void clockIn(){
            startTime = std::chrono::system_clock::now();
            running = true;
        }
        void clockOut(){
            endTime = std::chrono::system_clock::now();
            running = false;
        }       
};