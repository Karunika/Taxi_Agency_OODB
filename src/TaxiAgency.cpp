#include <iostream>
#include <fstream>
#include <string>

#include "../include/TaxiAgency.hpp"

#include "../include/User.hpp"
#include "../include/Taxi.hpp"
#include "../include/Customer.hpp"
#include "../include/Driver.hpp"

using namespace std;

int TaxiAgency::GarageLimit = 64;
int TaxiAgency::EachCarLimit = 4;
int TaxiAgency::DriverLimit = 64;

int Taxi::TaxiAttributesCount = 5;
int Customer::CustomerDetailsCount = 4;
int User::MaxUUIDLength = 32;


TaxiAgency::TaxiAgency(){

};

// splits line by commas
static void populate_fields(string line, string fields[], int length){
    for(int i = 0; i < length; i++){
        fields[i] = line.substr(0, line.find(","));
        line.erase(0, line.find(",")+1);
    }
};

// Binary search implementation (list arranged in ascending order)
template <typename T>
static IndexInstance<T> search_by_uuid(string uuid, vector<T> users_list){
    int high = 2*(users_list.size()-1);
    int low = 0;
    int mid;
    while(low < high){
        mid = (high+low)/2;
        if(users_list[mid].getUUID() > uuid){
            low = mid;
        }else if(users_list[mid].getUUID() < uuid){
            high = mid;
        }else if(users_list[mid].getUUID() == uuid){
            return {mid, &users_list[mid]};
        }
    }
};

void TaxiAgency::populate_taxies(const char* TAXIES_FILE){
    ifstream File;
    File.open(TAXIES_FILE);
    Taxi taxi;
    if(File.is_open()){
        string t, fields[Taxi::TaxiAttributesCount];
        getline(File, t); // skip heading row
        while(getline(File, t)){
            populate_fields(t, fields, Taxi::TaxiAttributesCount);
            taxi = Taxi(fields[0] == "\"True\"" ? true : false,
                        fields[1].substr(1, fields[1].length()-2),
                        fields[2].substr(1, fields[1].length()-2),
                        stoi(fields[3]),
                        stoi(fields[4]));

            stats["total_idol_taxies"] += taxi.number;
            taxies.push_back(taxi);
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }

};

void TaxiAgency::print_taxies(){
    cout << rang::fg::blue << "Taxies List:" << rang::fg::reset << endl;
    cout << "[" << endl;
    for(auto taxi: taxies){
        taxi.print();
    };
    cout << "]" << endl;
};

IndexInstance<Taxi> TaxiAgency::retrieve_taxi_by_id(string id){
    for(long i = 0; i < taxies.size(); i++){
        if(taxies[i].id == id){
            return {i, &taxies[i]};
        };
    };
    throw invalid_argument("Taxi with the id doesn't exist");
};

void TaxiAgency::add_taxi(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1){
    try{
        retrieve_taxi_by_id(id).data->number += number;
    }catch(...){
        taxies.push_back(Taxi(hybrid, id, manufacturer, fare_amount, number));
    }
};


void TaxiAgency::populate_customer_db(const char* CUSTOMERS_FILE){
    ifstream File;
    File.open(CUSTOMERS_FILE);
    Customer customer;
    if(File.is_open()){
        string t, fields[Customer::CustomerDetailsCount];
        getline(File, t); // skip heading row
        while(getline(File, t)){
            populate_fields(t, fields, Customer::CustomerDetailsCount);
            customer = Customer(fields[0].substr(1, fields[0].length()-2),
                        fields[1].substr(1, fields[1].length()-2),
                        fields[2].substr(1, fields[1].length()-2),
                        stol(fields[3]));

            customer_db.push_back(customer);
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

void TaxiAgency::print_customer_db(){
    cout << rang::fg::blue << "Customers List:" << rang::fg::reset << endl;
    cout << "[" << endl;
    for(auto customer: customer_db){
        customer.print();
    };
    cout << "]" << endl;
};


int TaxiAgency::set_total_idol_taxies(){
    int total_idol_taxies = 0;
    for(auto taxi: taxies){
        total_idol_taxies += taxi.number;
    }
};

ostream& operator<<(ostream& output, const TaxiAgency& A){
    output << rang::fg::blue << "Taxies" << rang::fg::reset <<
        "\nTotal number of taxies: " << rang::style::bold << A.taxies.size() << rang::style::reset <<
        "\nIdol Taxies: " << rang::style::bold << A.taxies.size() << rang::style::reset <<
        "\nTaxies on shift: " <<
        "\nMax Taxi Limit: " << A.taxies.size() << endl;
    return output;
};

template <typename T>
vector<T> TaxiAgency::operator[](string entity){
    if(entity == "customer"){
        return customer_db;
    } else if(entity == "driver"){
        return driver_db;
    } else if(entity == "taxies"){
        return taxies;
    }
    throw out_of_range("The subscript parameter is invalid");
};

template <typename T>
list<T> TaxiAgency::operator[](string entity){
    if(entity == "shifts"){
        return current_shifts;
    } else if(entity == "shift_history"){
        return shift_history;
    }
    throw out_of_range("The subscript parameter is invalid");
};

unordered_map<string, int> TaxiAgency::operator[](string entity){
    if(entity == "stats"){
        return stats;
    }
    throw out_of_range("The subscript parameter is invalid");
};