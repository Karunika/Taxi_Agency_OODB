#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum Status{
    ONSHIFT,
    IDLE
};

class User {
    protected:
        string firstname;
        string lastname;
        string uuid;
    public:
        static int MaxUUIDLength;
        static int MaxNameLength;
        User();
        User(string firstname, string lastname, string uuid);

        string getFirstname(){ return firstname; };
        string getLastname(){ return lastname; };
        string getUUID(){ return uuid; };

        string updateFirstname(string firstname);
        string updateLastname(string lastname);

        // Comparing uuids
        friend bool operator<(const User& u1, const User& u2);
        friend bool operator>(const User& u1, const User& u2);
        friend bool operator==(const User& u1, const User& u2);
        friend bool operator!=(const User& u1, const User& u2);

        bool operator<(const string& uuid);
        bool operator>(const string& uuid);
        bool operator==(const string& uuid);
        bool operator!=(const string& uuid);
};