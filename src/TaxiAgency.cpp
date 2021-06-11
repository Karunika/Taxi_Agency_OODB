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

int Taxi::TaxiAttributesCount = 6;
int Customer::CustomerDetailsCount = 5;
int Driver::DriverAttributesCount = 6;
int Shift::ShiftAttributesCount = 3;
int Shift::HistoryShiftAttributesCount = 6;
int User::MaxUUIDLength = 32;
int User::MaxNameLength = 256;


TaxiAgency::TaxiAgency(){
    DriverWagePerMonth = 1000;
    GarageLimit = 64;
    EachCarLimit = 4;
    DriverLimit = 64;
    WaitingCharges = 10;

    taxies.reserve(GarageLimit+1);
    driver_db.reserve(DriverLimit+1);
    customer_db.reserve(DriverLimit+1);

    cout << rang::fg::yellow << "A Taxi Agency has been instantiated" << rang::fg::reset << endl;
};

TaxiAgency::~TaxiAgency(){
    cout << rang::fg::yellow << "Taxi Agency has been purged" << rang::fg::reset << endl;
};

ostream& operator<<(ostream& output, TaxiAgency& A){
    output << rang::fg::blue << "Taxi Agency Details:" << rang::fg::reset << endl;
    output << "{" <<
        "\n\tcapacity : " <<
            "\n\t\tgarage Limit : " << A.GarageLimit <<
            "\n\t\teach Car Limit : " << A.EachCarLimit <<
            "\n\t\tdriver Limit : " << A.DriverLimit <<
            "\n\t\tcustomer Limit : " << A.DriverLimit <<
        "\n\tdriver stats : " <<
        // driver_limit = (driver_onshift + driver_idol) + drvier_vacancy
            "\n\t\tdriver limit : " << A.DriverLimit <<
            "\n\t\tdrivers on shift : " << A.current_shifts.size() <<
            "\n\t\tdrivers IDLE : " << A.driver_db.size() - A.current_shifts.size() <<
            "\n\t\tdriver vacancy : " << A.DriverLimit - A.driver_db.size() <<
        "\n\ttaxies : " <<
            "\n\t\ttotal : " << A.stats["total_taxies"] <<
            "\n\t\tavailable : " << A.stats["total_idol_taxies"] <<
            "\n\t\ton shifts : " << A.stats["taxies on shift"] <<
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

template <typename T>
static IndexInstance<T> search_by_uuid(string uuid, vector<T>& users_list){
    int high = 2*(users_list.size()-1);
    int low = 0;
    int mid;
    if(users_list[users_list.size()-1] < uuid)
        throw invalid_argument("User with the provided uuid doesn't exist");
    // cout << rang::fg::red << uuid << rang::fg::reset << endl;
    // cout << rang::fg::red << users_list.size() << rang::fg::reset << endl;
    while(low <= high){
        mid = (high+low)/2;
        // cout << rang::fg::blue << low << rang::fg::reset << " - " << mid << " - " << rang::fg::blue << high << rang::fg::reset << endl;
        if(users_list[mid] == uuid){
            // cout << endl;
            return {mid, &users_list[mid]};
        }else if(users_list[mid] < uuid){
            low = mid + 1;
        }else if(users_list[mid] > uuid){
            high = mid - 1;
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
                        stoi(fields[4]),
                        stoi(fields[5]));

            stats["total_taxies"] += taxi.number;
            stats["total_idol_taxies"] += taxi.available_number;
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

void TaxiAgency::insert_new_taxi_breed(bool hybrid, string id, string manufacturer, int fare_amount, int number){
    if(taxies.size() == GarageLimit+1)
        throw range_error("The limit of garage is reached. Need to upgrade the Agency!");
    try{
        retrieve_taxi_by_id(id);
        throw ("Taxi with the provided id already exist. Id should be unique.");
    }catch(invalid_argument){
        taxies.push_back(Taxi(hybrid, id, manufacturer, fare_amount, number, number));
    }
};

IndexInstance<Taxi> TaxiAgency::add_taxi_by_id(string id, int num){
    IndexInstance<Taxi> taxi = retrieve_taxi_by_id(id);
    if(num < 0)
        throw invalid_argument("Invalid Number provided");
    if(taxi.data->number + num >= EachCarLimit)
        throw range_error("Number of a certain Taxi shouldn't increase beyond EachCarLimit.");
    taxi.data->number += num;
    taxi.data->available_number += num;
    return taxi;
};

IndexInstance<Taxi> TaxiAgency::remove_taxi_by_id(string id, int num){;
    IndexInstance<Taxi> taxi = retrieve_taxi_by_id(id);
    if(num < 0)
        throw invalid_argument("Invalid Number provided");
    if(taxi.data->number - num < 0)
        throw range_error("Not enough taxies to remove.");
    taxi.data->number -= num;
    if(taxi.data->available_number != 0)
        taxi.data->available_number -= num;
    if(taxi.data->number == 0)
        taxies.erase(taxies.begin() + taxi.index);
    return taxi;
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
            File << taxi.number << ",";
            File << taxi.available_number << "\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }

};

// Customer Related functions
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
                        fields[4].substr(1, fields[4].length()-2) == "IDLE" ? IDLE : ONSHIFT);
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

void TaxiAgency::add_customer(string firstname, string lastname, string uuid, int balance, Status status){
    if(customer_db.size() == DriverLimit+1)
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
    IndexInstance<Customer> customer = search_customer_by_uuid(uuid);
    if(customer.data->getStatus() == ONSHIFT)
        throw invalid_argument("Can't delete a customer while its ONSHIFT");
    customer_db.erase(customer_db.begin() + customer.index);
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
            File << "\"" << (customer.getStatus() == IDLE ? "IDLE" : "ONSHIFT") << "\"\n";
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
                        fields[4].substr(1, fields[4].length()-2) == "IDLE" ? IDLE : ONSHIFT
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

void TaxiAgency::add_driver(string firstname, string lastname, string uuid, string dln, Status status){
    if(driver_db.size() == DriverLimit+1)
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
    IndexInstance<Driver> driver = search_driver_by_uuid(uuid);
    if(driver.data->getStatus() == ONSHIFT)
        throw invalid_argument("Can't delete a driver while its ONSHIFT");
    driver_db.erase(driver_db.begin() + driver.index);
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
            File << "\"" << (driver.getStatus() == IDLE ? "IDLE" : "ONSHIFT") << "\"\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

// Shifts
void TaxiAgency::import_current_shifts(const char* CURRENT_SHIFTS_FILE){
    ifstream File;
    File.open(CURRENT_SHIFTS_FILE);
    Shift shift;
    if(File.is_open()){
        string t, fields[Shift::ShiftAttributesCount];
        getline(File, t); // skip heading row
        while(getline(File, t)){
            populate_fields(t, fields, Shift::ShiftAttributesCount);
            shift = Shift(fields[0].substr(0, fields[0].length()-2),
                        fields[1].substr(1, fields[1].length()-2),
                        fields[2].substr(1, fields[2].length()-2));

            current_shifts.push_back(shift);
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

void TaxiAgency::import_shift_history(const char* SHIFT_HISTORY_FILE){
    ifstream File;
    File.open(SHIFT_HISTORY_FILE);
    Shift shift;
    if(File.is_open()){
        string t, fields[Shift::HistoryShiftAttributesCount];
        getline(File, t); // skip heading row
        while(getline(File, t)){
            populate_fields(t, fields, Shift::HistoryShiftAttributesCount);
            shift = Shift(fields[0].substr(0, fields[0].length()-2),
                        fields[1].substr(1, fields[1].length()-2),
                        fields[2].substr(1, fields[2].length()-2),
                        stoi(fields[3]),
                        stoi(fields[4]),
                        stoi(fields[5]));

            shift_history.push_back(shift);
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

void TaxiAgency::export_shift_history(const char* SHIFT_HISTORY_FILE){
    ofstream File;
    File.open(SHIFT_HISTORY_FILE);
    if(File.is_open()){
        File << "\"customer_uuid\",\"driver_uuid\",\"taxi_id\",\"running_hours\",\"waiting_hours\",\"total_cost\"\n";
        for(list<Shift>::iterator shift = shift_history.begin(); shift != shift_history.end(); ++shift){
            File << "\"" << shift->getCustomerUUID() << "\",";
            File << "\"" << shift->getDriverUUID() << "\",";
            File << "\"" << shift->getCarID() << ",\"";
            File << shift->getRunningHours() << ",";
            File << shift->getWaitingHours() << ",";
            File << shift->getTotalCost() << "\n";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

void TaxiAgency::export_ongoing_shifts(const char* CURRENT_SHIFTS_FILE){
    ofstream File;
    File.open(CURRENT_SHIFTS_FILE);
    if(File.is_open()){
        File << "\"customer_uuid\",\"driver_uuid\",\"taxi_id\"\n";
        for(list<Shift>::iterator shift = current_shifts.begin(); shift != current_shifts.end(); ++shift){
            File << "\"" << shift->getCustomerUUID() << "\",";
            File << "\"" << shift->getDriverUUID() << "\",";
            File << "\"" << shift->getCarID() << "\"";
        }
        File.close();
    }else{
        throw runtime_error("File couldn't be resolved");
    }
};

void TaxiAgency::book_taxi(string customer_uuid, string car_id){
    IndexInstance<Taxi> taxi;
    try{
        taxi = this->retrieve_taxi_by_id(car_id);
        if(taxi.data->available_number == 0)
            throw booking_unsuccessful("Taxi demanded Unavailable");
    }catch(invalid_argument e){
        throw booking_unsuccessful("Invalid Taxi id");
    };
    taxi.data->available_number--;
    
    IndexInstance<Customer> customer = search_customer_by_uuid(customer_uuid);
    if(customer.data->getStatus() == ONSHIFT)
        throw booking_unsuccessful("Can't Book a Taxi while already ONSHIFT");

    if(customer.data->getBalance() < 12*taxi.data->fare_amount + 12*WaitingCharges)
        throw booking_unsuccessful("Not enough balance to book a Taxi");

    customer.data->toggle_customer_status();

    string driver_uuid;
    for(int i = 0; i < driver_db.size(); i++){
        if(driver_db[i].getStatus() == IDLE){
            driver_uuid = driver_db[i].getUUID();
            driver_db[i].toggle_driver_status();
            Shift shift(customer_uuid, driver_uuid, car_id);
            current_shifts.push_back(shift);
            return;
        }
    }
    throw booking_unsuccessful("Running out of drivers.");
};

Shift TaxiAgency::retrieve_shift_details_by_customer(string customer_uuid){
    for(list<Shift>::iterator i = current_shifts.begin(); i != current_shifts.end(); ++i)
        if(i->getCustomerUUID() == customer_uuid)
            return *i;
    throw ("Customer with the supplied UUID is IDLE");
};

void TaxiAgency::end_shift(string customer_uuid, int running_hours, int waiting_hours){
    for(list<Shift>::iterator i = current_shifts.begin(); i != current_shifts.end(); ++i)
        if(i->getCustomerUUID() == customer_uuid){
            IndexInstance<Taxi> taxi = retrieve_taxi_by_id(i->getCarID());
            int total_cost = running_hours*taxi.data->fare_amount + waiting_hours*WaitingCharges;
            i->setRunningHours(running_hours);
            i->setWaitingHours(waiting_hours);
            i->setTotalCost(total_cost);
            shift_history.push_back(*i);
            current_shifts.erase(i);
            search_customer_by_uuid(customer_uuid).data->makeTransaction(total_cost);
            return;
        }
    throw invalid_argument("Customer with the supplied UUID is IDLE");
};

void TaxiAgency::print_ongoing_shifts(){
    cout << "[" << endl;
    for (list<Shift>::iterator i = current_shifts.begin(); i != current_shifts.end(); ++i)
        cout << *i;
    cout << "]" << endl;
};

void TaxiAgency::print_shift_history(){
    cout << "[" << endl;
    for (list<Shift>::iterator i = shift_history.begin(); i != shift_history.end(); ++i)
        cout << *i;
    cout << "]" << endl;
};

// Others
void TaxiAgency::upgrade_agency_assets(int garage_limit, int each_car_limit, int driver_vacancies){
    if(garage_limit < GarageLimit || each_car_limit < EachCarLimit || driver_vacancies < DriverLimit){
        return;
    }
    this->GarageLimit = garage_limit;
    this->EachCarLimit = each_car_limit;
    this->DriverLimit = driver_vacancies;

    taxies.reserve(GarageLimit+1);
    driver_db.reserve(DriverLimit+1);
    customer_db.reserve(DriverLimit+1);
};

void TaxiAgency::driver_promotion(int new_wage){
    if(new_wage < DriverWagePerMonth){
        return;
    }
    DriverWagePerMonth = new_wage;
}

void TaxiAgency::export_all(const char* TAXIES_FILE, const char* CUSTOMERS_FILE, const char* DRIVERS_FILE){
    export_taxies(TAXIES_FILE);
    export_customer_db(CUSTOMERS_FILE);
    export_driver_db(DRIVERS_FILE);
};