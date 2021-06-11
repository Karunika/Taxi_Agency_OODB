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
    int available_number;

    Taxi(){};
    Taxi(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1, int available_number = 1)
        : hybrid(hybrid),
        id(id),
        manufacturer(manufacturer),
        fare_amount(fare_amount),
        number(number),
        available_number(available_number)
    {
        if(available_number > number)
            throw invalid_argument("Available taxies can't be more than total taxies");
    };
    friend ostream& operator<<(ostream& output, const Taxi& T){
        output << "\t{" <<
            "\n\t\thybrid : " << (T.hybrid ? "True" : "False") <<
            "\n\t\tid : " << T.id <<
            "\n\t\tmanufacturer : " << T.manufacturer <<
            "\n\t\tfare amount : " << T.fare_amount <<
            "\n\t\tcount : " << T.number <<
            "\n\t\tavailable count : " << T.available_number <<
            "\n\t\ton shift count : " << T.number - T.available_number <<
            "\n\t}" <<
            endl;
        return output;
    };
    void check_num(){
        if(number < available_number)
            throw invalid_argument("Available taxies can't be more than total taxies");
    };
    void print(){
        cout << *this;
    };

};