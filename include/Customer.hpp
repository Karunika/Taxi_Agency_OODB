#pragma once
#include <iostream>
#include "./User.hpp"

using namespace std;

class Customer : public User{
    private:
        long balance;
        // One customer can book only one taxi at a time
    public:
        static int CustomerDetailsCount;

        Customer(){};
        Customer(string firstname, string lastname, string uuid, long balance);
        void book_taxi();
        int bookTaxi(std::string car_name);

        friend ostream& operator<<(ostream& output, const Customer& C);
        void print();

        ~Customer(){};
};