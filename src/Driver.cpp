#include <iostream>

#include "../include/User.hpp"
#include "../include/Driver.hpp"

using namespace std;

Driver::Driver(string firstname, string lastname, string uuid, string dln, Status status)
    : User(firstname, lastname, uuid),
    driving_license_num(dln), status(status){

};

ostream& operator<<(ostream& output, const Driver& D){
    output << "\t{" <<
        "\n\t\tuuid : " << D.uuid <<
        "\n\t\tfirstname : " << D.firstname <<
        "\n\t\tlastname : " << D.lastname <<
        "\n\t\tdriving license number : " << D.driving_license_num <<
        "\n\t\tStatus : " << (D.status == IDLE ? "IDLE" : "ONSHIFT") <<
        "\n\t}" <<
        endl;
    return output;
};

void Driver::print(){
    cout << *this;
};

void Driver::toggle_driver_status(){
    switch (status){
    case IDLE:
        status = ONSHIFT;
        break;
    case ONSHIFT:
        status = IDLE;
        break;
    }

};

string Driver::getDLN(){
    return driving_license_num;
};

Status Driver::getStatus(){
    return status;
};
