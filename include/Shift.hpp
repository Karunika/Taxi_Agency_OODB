#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Shift{
    private:
        string customer_uuid;
        string driver_in_charge_uuid;
        string car_id;

        int taxi_fare_amount;
        int waiting_charges;

        unordered_map<string, int> history_stats = {
            {"running_kms", 0},
            {"waiting_hours", 0},
            {"total_cost", 0},
        };
    public:
        static int ShiftAttributesCount;
        static int HistoryShiftAttributesCount;
        
        Shift(){};
        Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int taxi_fare_amount, int waiting_charges);
        Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int taxi_fare_amount, int waiting_charges, int running_hours, int waiting_hours, int total_cost);

        const string& getCustomerUUID() const;
        const string& getDriverUUID() const;
        const string& getCarID() const;
        const int& getFareAmount() const;
        const int& getWaitingCharges() const;
        const int& getRunningKms() const;
        const int& getWaitingHours() const;
        const int& getTotalCost() const;

        void setRunningKms(int running_kms);
        void setWaitingHours(int waiting_hours);
        void setTotalCost(int total_cost);

        void updateRunningKms(int del_running_kms);
        void updateWaitingHours(int del_waiting_hours);
        void updateTotalCost(int del_total_cost);

        void extend_tenure(int del_running_kms, int del_waiting_hours);
        
        friend ostream& operator<<(ostream& output, const Shift& S);
        void print_shift();
};