#include <iostream>
#include <string>

// #include "../include/TaxiAgency.hpp"
#include "../include/User.hpp"
#include "../include/Customer.hpp"

using namespace std;

Customer::Customer(string firstname, string lastname, string uuid, long balance = 0)
    : User(firstname, lastname, uuid),
    balance(balance){

};

ostream& operator<<(ostream& output, const Customer& C){
    output << "\t{" <<
        "\n\t\tuuid : " << C.uuid <<
        "\n\t\tfirstname : " << C.firstname <<
        "\n\t\tlastname : " << C.lastname <<
        "\n\t\tbalance : " << C.balance <<
        "\n\t}" <<
        endl;
    return output;
};

void Customer::print(){
    cout << *this;
};

// int Customer::book_taxi(std::string car_id, TaxiAgency& A){
//     try{
//         IndexInstance<Taxi> taxi = A.retrieve_taxi_by_id(car_id);
//         if(taxi.data->number == 0){
//             throw booking_unsuccessful("Taxi Unavailable");
//         }

//     }catch(invalid_argument e){
//         throw booking_unsuccessful("Invalid Taxi id");
//     };
//     // Shift();
// };

// void Customer::book_taxi(string id ){

// };