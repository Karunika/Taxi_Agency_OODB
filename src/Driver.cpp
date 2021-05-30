#include <iostream>

#include "../include/User.hpp"
#include "../include/Driver.hpp"

using namespace std;

Driver::Driver(string firstname, string lastname, string uuid, string dln)
    : User(firstname, lastname, uuid),
    driving_license_num(dln){

};

ostream& operator<<(ostream& output, const Driver& D){
    output << "\t{" <<
        "\n\t\tuuid : " << D.uuid <<
        "\n\t\tfirstname : " << D.firstname <<
        "\n\t\tlastname : " << D.lastname <<
        "\n\t\tdriving license number : " << D.driving_license_num <<
        "\n\t}" <<
        endl;
    return output;
};

void Driver::print(){
    cout << *this;
};
