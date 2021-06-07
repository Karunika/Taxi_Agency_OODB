#pragma once
#include <iostream>
#include "./User.hpp"
#include "./Driver.hpp"


using namespace std;

class Driver : public User{
    private:
        string driving_license_num;
        // ID number or alphanumeric code usually found on a government-issued license
        
        Status status;
    public:
        static int DriverAttributesCount;

        Driver(){};
        Driver(string firstname, string lastname, string uuid, string dln, Status status);

        string getDLN(){ return driving_license_num; };
        Status getStatus(){ return status; };

        friend ostream& operator<<(ostream& output, const Driver& D);
        void print();

        // ~Driver();
};