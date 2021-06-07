#include <iostream>
#include <string>

#include "../include/User.hpp"
#include "../include/Customer.hpp"

using namespace std;

Customer::Customer(string firstname, string lastname, string uuid, long balance = 0, Status status = IDOL)
    : User(firstname, lastname, uuid),
    balance(balance), status(status){

};

ostream& operator<<(ostream& output, const Customer& C){
    output << "\t{" <<
        "\n\t\tuuid : " << C.uuid <<
        "\n\t\tfirstname : " << C.firstname <<
        "\n\t\tlastname : " << C.lastname <<
        "\n\t\tbalance : " << C.balance <<
        "\n\t\tstatus : " << (C.status == IDOL ? "IDOL" : "ONSHIFT") <<
        "\n\t}" <<
        endl;
    return output;
};

void Customer::print(){
    cout << *this;
};