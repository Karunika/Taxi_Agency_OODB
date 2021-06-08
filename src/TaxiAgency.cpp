#include <iostream>
#include <fstream>
#include <string>

#include "../include/TaxiAgency.hpp"

#include "../include/User.hpp"
#include "../include/Taxi.hpp"
#include "../include/Driver.hpp"
#include "../include/Customer.hpp"
#include "../include/Shift.hpp"

using namespace std;

int Taxi::TaxiAttributesCount = 5;
int Customer::CustomerDetailsCount = 5;
int Driver::DriverAttributesCount = 6;
int User::MaxUUIDLength = 32;


TaxiAgency::TaxiAgency(){
    DriverWagePerMonth = 1000;
    GarageLimit = 64;
    EachCarLimit = 4;
    DriverLimit = 64;

    taxies.reserve(GarageLimit);
    driver_db.reserve(DriverLimit);
    customer_db.reserve(DriverLimit);

    cout << rang::fg::yellow << "A Taxi Agency has been instantiated" << rang::fg::reset << endl;
};

TaxiAgency::~TaxiAgency(){
    cout << rang::fg::yellow << "Taxi Agency has been purged" << rang::fg::reset << endl;
};

ostream& operator<<(ostream& output, TaxiAgency& A){
    output << rang::fg::blue << "Taxi Agency Details:" << rang::fg::reset << endl;
    output << "{" <<
        "\n\tcapacity : " <<
            "\n\t\tGarage Limit : " << A.GarageLimit <<
            "\n\t\tEach Car Limit : " << A.EachCarLimit <<
            "\n\t\tDriver Limit : " << A.DriverLimit <<
            "\n\t\tCustomer Limit : " << A.DriverLimit <<
        "\n\tidol : " <<
            "\n\t\tDrivers : " << A.stats["drivers"] - A.stats["driver_vacancies"] <<
            "\n\t\tTaxies : " << A.stats["total_idol_taxies"] <<
        "\n\tshifts on going : " << A <<
            "\n\t\tDrivers : " << A.stats["drivers"] <<
            "\n\t\tTaxies : " << A.stats["total_idol_taxies"] <<
        "\n\t}" << endl;
    return output;
};

void TaxiAgency::print_agency_stats(){
    cout << *this;
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
static IndexInstance<T> search_by_uuid(string uuid, vector<T>& users_list){
    int high = 2*(users_list.size()-1);
    int low = 0;
    int mid;
    while(low < high){
        mid = (high+low)/2;
        if(users_list[mid] > uuid){
            low = mid;
        }else if(users_list[mid] < uuid){
            high = mid;
        }else if(users_list[mid] == uuid){
            return {mid, &users_list[mid]};
        }
    }
    throw invalid_argument("User with the provided uuid doesn't exist");
};

// Taxi Related functions
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
                        fields[2].substr(1, fields[2].length()-2),
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
    for(int i = 0; i < taxies.size(); i++){
        if(taxies[i].id == id){
            return {i, &taxies[i]};
        };
    };
    throw invalid_argument("Taxi with the id doesn't exist");
};

void TaxiAgency::insert_new_taxi_breed(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1){
    if(taxies.size() == GarageLimit)
        throw range_error("The limit of garage is reached. Need to upgrade the Agency!");
    taxies.push_back(Taxi(hybrid, id, manufacturer, fare_amount, number));
};

void TaxiAgency::add_taxi_by_id(string id, int num = 1){
    IndexInstance<Taxi> taxi = retrieve_taxi_by_id(id);
    if(num < 0)
        throw invalid_argument("Invalid Number provided");
    if(taxi.data->number + num >= EachCarLimit)
        throw invalid_argument("Number of a certain Taxi shouldn't increase beyond EachCarLimit.");
    taxi.data->number += num;
};

void TaxiAgency::remove_taxi_by_id(string id, int num = 1){;
    IndexInstance<Taxi> taxi = retrieve_taxi_by_id(id);
    if(num < 0)
        throw invalid_argument("Invalid Number provided");
    if(taxi.data->number - num < 0)
        throw invalid_argument("Not enough taxies to remove.");
    taxi.data->number -= num;
};

void TaxiAgency::export_taxies(const char* TAXIES_FILE){
    ofstream File;
    File.open(TAXIES_FILE);
    if(File.is_open()){
        File << "\"hybrid\",\"id\",\"manufacturer\",\"fare_amount\",\"number\"\n";
        for(auto taxi : taxies){
            File << "\"" << (taxi.hybrid ? "True" : "False") << "\",";
            File << "\"" << taxi.id << "\",";
            File << "\"" << taxi.manufacturer << "\",";
            File << taxi.fare_amount << ",";
            File << taxi.number << "\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }

};

//Customer Related functions
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
                        fields[2].substr(1, fields[2].length()-2),
                        stoi(fields[3]),
                        fields[4].substr(1, fields[4].length()-2) == "IDOL" ? IDOL : ONSHIFT);
            stats["customers"]++;
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

IndexInstance<Customer> TaxiAgency::search_customer_by_uuid(string uuid){
    return search_by_uuid(uuid, customer_db);
};

void TaxiAgency::add_customer(string firstname, string lastname, string uuid, int balance = 0, Status status = IDOL){
    if(customer_db.size() == DriverLimit)
        throw range_error("The maximum capacity of customer is reached. Need to upgrade the Agency!");
    for(int i = 0; i < customer_db.size(); i++){
        if(customer_db[i] == uuid){
            throw invalid_argument("User with the UUID already exist.");
        }
        if(customer_db[i] > uuid){
            Customer new_customer(firstname, lastname, uuid, balance, status);
            customer_db.insert(customer_db.begin() + i, new_customer);
            return;
        }
    };
    Customer new_customer(firstname, lastname, uuid, balance, status);
    customer_db.push_back(new_customer);
}

void TaxiAgency::delete_customer_user_by_uuid(string uuid){

};

void TaxiAgency::export_customer_db(const char* CUSTOMERS_FILE){
    ofstream File;
    File.open(CUSTOMERS_FILE);
    if(File.is_open()){
        File << "\"firtsname\",\"lastname\",\"uuid\",\"balance\",\"status\"\n";
        for(auto customer : customer_db){
            File << "\"" << customer.getFirstname() << "\",";
            File << "\"" << customer.getLastname() << "\",";
            File << "\"" << customer.getUUID() << "\",";
            File << customer.getBalance() << ",";
            File << "\"" << (customer.getStatus() == IDOL ? "IDOL" : "ONSHIFT") << "\"\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
}; // to be tested

// Drivers Related Functions
void TaxiAgency::populate_drivers_db(const char* DRIVERS_FILE){
    ifstream File;
    File.open(DRIVERS_FILE);
    Driver driver;
    if(File.is_open()){
        string t, fields[Driver::DriverAttributesCount];
        getline(File, t); // skip heading row
        while(getline(File, t)){
            populate_fields(t, fields, Driver::DriverAttributesCount);
            driver = Driver(fields[0].substr(1, fields[0].length()-2),
                        fields[1].substr(1, fields[1].length()-2),
                        fields[2].substr(1, fields[2].length()-2),
                        fields[3].substr(1, fields[3].length()-2),
                        fields[4].substr(1, fields[4].length()-2) == "IDOL" ? IDOL : ONSHIFT
                    );
            stats["drivers"]++;
            driver_db.push_back(driver);
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }

};

void TaxiAgency::print_drivers_db(){
    cout << rang::fg::blue << "Drivers List:" << rang::fg::reset << endl;
    cout << "[" << endl;
    for(auto driver: driver_db){
        driver.print();
    };
    cout << "]" << endl;
};

IndexInstance<Driver> TaxiAgency::search_driver_by_uuid(string uuid){
    return search_by_uuid(uuid, driver_db);
};

void TaxiAgency::add_driver(string firstname, string lastname, string uuid, string dln, Status status = IDOL){
    if(driver_db.size() == DriverLimit)
        throw range_error("The maximum vacancy of driver is reached. Need to upgrade the Agency!");
    for(int i = 0; i < driver_db.size(); i++){
        if(driver_db[i] == uuid){
            throw invalid_argument("User with the UUID already exist.");
        }
        if(driver_db[i] > uuid){
            Driver new_driver(firstname, lastname, uuid, dln, status);
            driver_db.insert(driver_db.begin() + i, new_driver);
            return;
        }
    };
    Driver new_driver(firstname, lastname, uuid, dln, status);
    driver_db.push_back(new_driver);
};

void TaxiAgency::delete_driver_user_by_uuid(string uuid){

};

void TaxiAgency::export_driver_db(const char* DRIVERS_FILE){
    ofstream File;
    File.open(DRIVERS_FILE);
    if(File.is_open()){
        File << "\"firtsname\",\"lastname\",\"uuid\",\"dln\",\"status\"\n";
        for(auto driver : driver_db){
            File << "\"" << driver.getFirstname() << "\",";
            File << "\"" << driver.getLastname() << "\",";
            File << "\"" << driver.getUUID() << "\",";
            File << "\"" << driver.getDLN() << "\",";
            File << "\"" << (driver.getStatus() == IDOL ? "IDOL" : "ONSHIFT") << "\"\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
}


int TaxiAgency::book_taxi(string customer_uuid, string car_id){
    try{
        IndexInstance<Taxi> taxi = this->retrieve_taxi_by_id(car_id);
        if(taxi.data->number == 0){
            throw booking_unsuccessful("Taxi Unavailable");
        }
        taxi.data->number--;
        IndexInstance<Customer> customer = search_customer_by_uuid(customer_uuid);
        if(customer.data->getStatus() == ONSHIFT){
            throw booking_unsuccessful("Can't Book a Taxi while already ONSHIFT");
        }
        // Agency revenue/finance

        // if(customer.data->getBalance() < taxi.data->fare_amount*12 + driver_waiting_charges*12 + driver_wage){

        // }
        // Shift shift(customer_uuid, );

    }catch(invalid_argument e){
        throw booking_unsuccessful("Invalid Taxi id");
    };
    // Shift();
    return 0;
}


// ostream& operator<<(ostream& output, const TaxiAgency& A){
//     output << rang::fg::blue << "Taxies" << rang::fg::reset <<
//         "\nTotal number of taxies: " << rang::style::bold << A.taxies.size() << rang::style::reset <<
//         "\nIdol Taxies: " << rang::style::bold << A.taxies.size() << rang::style::reset <<
//         "\nTaxies on shift: " <<
//         "\nMax Taxi Limit: " << A.taxies.size() << endl;
//     return output;
// };


// Getters using the subscript syntax
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



void TaxiAgency::upgrade_agency_assets(int garage_limit, int each_car_limit, int driver_vacancies){
    if(garage_limit < GarageLimit || each_car_limit < EachCarLimit || driver_vacancies < DriverLimit){
        return;
    }
    this->GarageLimit = garage_limit;
    this->EachCarLimit = each_car_limit;
    this->DriverLimit = driver_vacancies;
};

void TaxiAgency::export_all(const char* TAXIES_FILE, const char* CUSTOMERS_FILE, const char* DRIVERS_FILE){
    export_taxies(TAXIES_FILE);
    export_customer_db(CUSTOMERS_FILE);
    export_driver_db(DRIVERS_FILE);
};
