#pragma once
#include <iostream>
#include <exception>

#include "./User.hpp"
// #include "./TaxiAgency.hpp"

using namespace std;

struct booking_unsuccessful : public exception {
    const char* msg;
    booking_unsuccessful(const char* msg) : msg(msg){
    };
    const char * what () const throw () {
        return msg;
    }
};

class Customer : public User{
    private:
        long balance;
        // One customer can book only one taxi at a time

        Status status;
    public:
        static int CustomerDetailsCount;

        Customer(){};
        Customer(string firstname, string lastname, string uuid, long balance);
        // int book_taxi(string car_id, TaxiAgency& A);

        // int start_shift(){};
        int start_taxi();
        int stop_taxi();
        int end_shift();

        //nope ig

        friend ostream& operator<<(ostream& output, const Customer& C);
        void print();


        // int book_taxi(string car_id, TaxiAgency& A);

        // ~Customer(){};
};
//hello yes

// ayt wait