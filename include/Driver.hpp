#pragma once
#include <iostream>
#include "./User.hpp"

using namespace std;

enum Status{
    ONSHIFT,
    IDOL
};

class Driver : public User{
    private:
        Status status;

        string driving_license_num;
        // ID number or alphanumeric code usually found on a government-issued license
    public:
        Driver(int id, string firstname, string lastname, string uuid, string dln);

        friend ostream& operator<<(ostream& output, const Customer& C);
        void print();

        ~Driver();

};