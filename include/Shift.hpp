#pragma once
#include <iostream>
#include <chrono>
#include <cmath>

#include "./Taxi.hpp"
#include "./Driver.hpp"

class Shift{
    private:
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
        
        void clockIn();
        void clockOut();
};