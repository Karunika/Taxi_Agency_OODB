#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Taxi{
    static int TaxiAttributesCount;

    bool hybrid;
    string id;
    string manufacturer;
    int fare_amount;
    int number;

    Taxi(){};
    Taxi(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1)
        : hybrid(hybrid),
        id(id),
        manufacturer(manufacturer),
        fare_amount(fare_amount),
        number(number)
    {};
    friend ostream& operator<<(ostream& output, const Taxi& T){
        output << "\t{" <<
            "\n\t\thybrid : " << (T.hybrid ? "True" : "False") <<
            "\n\t\tid : " << T.id <<
            "\n\t\tmanufacturer : " << T.manufacturer <<
            "\n\t\tfare amount : " << T.fare_amount <<
            "\n\t}" <<
            endl;
        return output;
    };
    void print(){
        cout << *this;
    };

};