#include <iostream>
#include <string>
#include <unordered_map>

#include "../include/Shift.hpp"

using namespace std;

Shift::Shift(string customer_uuid, string driver_in_charge_uuid,  string taxi_id, int taxi_fare_amount, int waiting_charges)
    : customer_uuid(customer_uuid),
    driver_in_charge_uuid(driver_in_charge_uuid),
    car_id(taxi_id),
    taxi_fare_amount(taxi_fare_amount),
    waiting_charges(waiting_charges){
};

Shift::Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int taxi_fare_amount, int waiting_charges, int running_hours, int waiting_hours, int total_cost)
    : customer_uuid(customer_uuid),
    driver_in_charge_uuid(driver_in_charge_uuid),
    car_id(taxi_id),
    taxi_fare_amount(taxi_fare_amount),
    waiting_charges(waiting_charges){
    history_stats["running_hours"] = running_hours;
    history_stats["waiting_hours"] = waiting_hours;
    history_stats["total_cost"] = total_cost;
};

ostream& operator<<(ostream& output, const Shift& S){
    output << "\t{" <<
        "\n\t\tcustomer uuid : " << S.customer_uuid <<
        "\n\t\tdriver in charge uuid : " << S.driver_in_charge_uuid <<
        "\n\t\ttaxi id : " << S.car_id <<
        "\n\t\ttaxi fare amount (per kilometer) : " << S.taxi_fare_amount <<
        "\n\t\tdriver waitin charges : " << S.waiting_charges <<
        "\n\t}" <<
        endl;
    return output;
};

void Shift::print_shift(){
    cout << *this;
};

const string& Shift::getDriverUUID() const {
    return driver_in_charge_uuid;
};

const string& Shift::getCustomerUUID() const {
    return customer_uuid;
};

const string& Shift::getCarID() const{
    return car_id;
};

const int& Shift::getFareAmount() const{
    return taxi_fare_amount;
};

const int& Shift::getWaitingCharges() const{
    return waiting_charges;
};

const int& Shift::getRunningHours() const{
    return history_stats.at("running_hours");
};

const int& Shift::getWaitingHours() const{
    return history_stats.at("waiting_hours");
};

const int& Shift::getTotalCost() const{
    return history_stats.at("total_cost");
};

void Shift::setRunningHours(int running_hours){
    history_stats["running_hours"] = running_hours;
};

void Shift::setWaitingHours(int waiting_hours){
    history_stats["waiting_hours"] = waiting_hours;
};

void Shift::setTotalCost(int total_cost){
    history_stats["total_cost"] = total_cost;
};

void Shift::updateRunningHours(int del_running_hours){
    history_stats["running_hours"] += del_running_hours;
};

void Shift::updateWaitingHours(int del_waiting_hours){
    history_stats["waiting_hours"] += del_waiting_hours;
};

void Shift::updateTotalCost(int del_total_cost){
    history_stats["total_cost"] += del_total_cost;
};

void Shift::extend_tenure(int del_running_hours, int del_waiting_hours){
    updateRunningHours(del_running_hours);
    updateWaitingHours(del_waiting_hours);
    updateTotalCost(del_running_hours*taxi_fare_amount+del_waiting_hours*waiting_charges);
};
