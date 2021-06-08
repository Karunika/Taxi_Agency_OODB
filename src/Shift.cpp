#include <iostream>
#include <string>
#include "../include/User.hpp"
#include "../include/Customer.hpp"
#include "../include/Shift.hpp"

using namespace std;

Shift::Shift(string customer_uuid, string driver_in_charge_uuid)
    : customer_uuid(customer_uuid),
    driver_in_charge_uuid(driver_in_charge_uuid){

}