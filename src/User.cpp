#include <iostream>
#include <locale>
#include "../include/User.hpp"

using namespace std;

void User::validate_uuid(string uuid){
    if(uuid.length() > User::MaxUUIDLength){
        throw out_of_range("UUID max character limit exceeded");
    }
    int i = 0;
    while(i < uuid.length()){
        if(isalnum(uuid[i]) || uuid[i] == '_'){
            i++;
        }else{
            throw ("Invalid UUID: only alphanumeric [a-zA-Z0-9_] characters are allowed");
        };
    }
};

User::User(){};

User::User(string firstname, string lastname, string uuid)
    : firstname(firstname),
    lastname(lastname),
    uuid(uuid)
{
    validate_uuid(uuid);
};

bool operator<(const User& u1, const User& u2){
    return u1.uuid < u2.uuid;
};

bool operator>(const User& u1, const User& u2){
    return u1.uuid > u2.uuid;
};

bool operator==(const User& u1, const User& u2){
    return u1.uuid == u2.uuid;
};

bool operator!=(const User& u1, const User& u2){
    return u1.uuid != u2.uuid;
};

