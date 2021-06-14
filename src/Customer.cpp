#include <iostream>
#include <string>

#include "../include/User.hpp"
#include "../include/Customer.hpp"

using namespace std;

Customer::Customer(string firstname, string lastname, string uuid, int balance = 0, Status status = IDLE)
    : User(firstname, lastname, uuid),
    balance(balance), status(status){

};

ostream& operator<<(ostream& output, const Customer& C){
    output << "\t{" <<
        "\n\t\tuuid : " << C.uuid <<
        "\n\t\tfirstname : " << C.firstname <<
        "\n\t\tlastname : " << C.lastname <<
        "\n\t\tbalance : " << C.balance <<
        "\n\t\tstatus : " << (C.status == IDLE ? "IDLE" : "ONSHIFT") <<
        "\n\t}" <<
        endl;
    return output;
};

void Customer::print(){
    cout << *this;
};

void Customer::toggle_customer_status(){
    switch (status){
    case IDLE:
        status = ONSHIFT;
        break;
    case ONSHIFT:
        status = IDLE;
        break;
    }
};

Status Customer::getStatus(){
    return status;
};

int Customer::getBalance(){
    return balance;
};

void Customer::makeTransaction(int amount){
    balance -= amount;
};
void Customer::transferCashToBalance(int amount){
    balance += amount;
};