#include <iostream>
#include <locale>
#include "../include/User.hpp"

using namespace std;

struct invalid_uuid : public exception {
    const char* msg;
    invalid_uuid(const char* msg) : msg(msg){
    };
    const char * what () const throw () {
        return msg;
    }
};
struct invalid_name : public exception {
    const char* msg;
    invalid_name(const char* msg) : msg(msg){
    };
    const char * what () const throw () {
        return msg;
    }
};

static void validate_uuid(string uuid){
    if(uuid.length() > User::MaxUUIDLength){
        throw out_of_range("UUID max character limit exceeded");
    }
    int i = 0;
    while(i < uuid.length()){
        if(isalnum(uuid[i]) || uuid[i] == '_'){
            i++;
        }else{
            throw invalid_uuid("Invalid UUID: only alphanumeric [a-zA-Z0-9_] characters are allowed");
        };
    }
};
static void validate_name(string name){
    if(name.length() > User::MaxNameLength){
        throw out_of_range("Name max character limit exceeded");
    }
    int i = 0;
    while(i < name.length()){
        if(isalpha(name[i])){
            i++;
        }else{
            throw invalid_name("Invalid Name: only standard english alphabets are allowed");
        };
    }
};

// 0-9 A-Z _ a-z
User::User(){};

User::User(string firstname, string lastname, string uuid)
    : firstname(firstname),
    lastname(lastname),
    uuid(uuid)
{
    validate_uuid(uuid);
    validate_name(firstname);
    validate_name(lastname);
};

string User::updateFirstname(string firstname){
    this->firstname = firstname;
    return firstname;
};

string User::updateLastname(string lastname){
    this->lastname = lastname;
    return lastname;
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

bool User::operator<(const string& uuid){
    return this->uuid < uuid;    
};

bool User::operator>(const string& uuid){
    return this->uuid > uuid;    
};

bool User::operator==(const string& uuid){
    return this->uuid == uuid;    
};

bool User::operator!=(const string& uuid){
    return this->uuid != uuid;    
};
