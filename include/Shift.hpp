#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Shift{
    private:
        string customer_uuid;
        string driver_in_charge_uuid;
        string car_id;

        unordered_map<string, int> history_stats = {
            {"running_hours", 0},
            {"waiting_hours", 0},
            {"total_cost", 0},
        };
    public:
        static int ShiftAttributesCount;
        static int HistoryShiftAttributesCount;
        
        Shift(){};
        Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id);
        Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int running_hours, int waiting_hours, int total_cost);

        const string& getCustomerUUID() const;
        const string& getDriverUUID() const;
        const string& getCarID() const;
        const int& getRunningHours() const;
        const int& getWaitingHours() const;
        const int& getTotalCost() const;

        void setRunningHours(int running_hours);
        void setWaitingHours(int waiting_hours);
        void setTotalCost(int total_cost);

        friend ostream& operator<<(ostream& output, const Shift& S);
        void print_shift();
};