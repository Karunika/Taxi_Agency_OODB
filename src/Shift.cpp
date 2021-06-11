#include <iostream>
#include <string>
#include <unordered_map>

#include "../include/Shift.hpp"

using namespace std;

Shift::Shift(string customer_uuid, string driver_in_charge_uuid,  string taxi_id)
    : customer_uuid(customer_uuid),
    driver_in_charge_uuid(driver_in_charge_uuid),
    car_id(taxi_id){

};

Shift::Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int running_hours, int waiting_hours, int total_cost)
    : customer_uuid(customer_uuid),
    driver_in_charge_uuid(driver_in_charge_uuid),
    car_id(taxi_id){
    history_stats["running_hours"] = running_hours;
    history_stats["waiting_hours"] = waiting_hours;
    history_stats["total_cost"] = total_cost;
};

ostream& operator<<(ostream& output, const Shift& S){
    output << "\t{" <<
        "\n\t\tcustomer uuid : " << S.customer_uuid <<
        "\n\t\tdriver in charge uuid : " << S.driver_in_charge_uuid <<
        "\n\t\ttaxi id : " << S.car_id <<
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
