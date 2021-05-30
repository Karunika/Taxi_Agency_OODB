#pragma once
#include <iostream>

using namespace std;

enum Status{
    ONSHIFT,
    IDOL
};

class User {
    protected:
        string firstname;
        string lastname;
        string uuid;
    public:
        static int MaxUUIDLength;
        User();
        User(string firstname, string lastname, string uuid);
        void validate_uuid(string uuid);

        string getUUID(){ return uuid; };

        // Comparing uuids
        friend bool operator<(const User& u1, const User& u2);
        friend bool operator>(const User& u1, const User& u2);
        friend bool operator==(const User& u1, const User& u2);
        friend bool operator!=(const User& u1, const User& u2);
};