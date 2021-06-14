#pragma once
#include <iostream>
#include <exception>

#include "./User.hpp"

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
        int balance;
        // One customer can book only one taxi at a time

        Status status;
    public:
        static int CustomerDetailsCount;

        Customer(){};
        Customer(string firstname, string lastname, string uuid, int balance, Status status);
        
        friend ostream& operator<<(ostream& output, const Customer& C);
        void print();

        Status getStatus();
        int getBalance();

        void makeTransaction(int amount);
        void transferCashToBalance(int amount);
        
        void toggle_customer_status();
};