#pragma once
#include <iostream>
#include "./User.hpp"
#include "./Driver.hpp"


using namespace std;

class Driver : public User{
    private:
        string driving_license_num;        
        Status status;
    public:
        static int DriverAttributesCount;

        Driver(){};
        Driver(string firstname, string lastname, string uuid, string dln, Status status = IDLE);

        string getDLN();
        Status getStatus();

        void toggle_driver_status();

        friend ostream& operator<<(ostream& output, const Driver& D);
        void print();

        // ~Driver();
};