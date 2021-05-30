#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

#include "./Taxi.hpp"
#include "./Driver.hpp"

class Shift{
    private:
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> endTime;
        bool running;
        long time_limit;
        long kms_rode;

        Taxi car;

        // uuids
        string driver_in_charge_uuid;
        string customer_uuid;

        int driver_idol_cost;

    public:
        Shift();
        Shift(string customer_uuid, string dirver_in_charge_uuid);
        
        // friend void Customer::clockIn(const Shift& S);
        void clockIn();
        void clockOut();
};