#pragma once
#include <iostream>
#include <string>

class Interface{
    protected:
        int id;
        std::string username;
        std::string passwordHash;
    public:
        // User(std::string username, std::string password, )
        // ~User();
};
