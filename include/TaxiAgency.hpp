#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

#include "../dep/rang.hpp"

#include "./Taxi.hpp"
// #include "./Driver.hpp"
#include "./Shift.hpp"
#include "./Customer.hpp"


using namespace std;

template <typename T>
struct IndexInstance{
    long index;
    T* data;
};

class TaxiAgency{
    private:
        vector<Taxi> taxies;
        // vector<Driver> driver_db;

        // list<Shift> current_shifts;
        // list<Shift> shift_history;

        vector<Customer> customer_db;


        unordered_map<string, int> stats = {
            {"total_idol_taxies", 0},
            {"taxies_on_shift", 0},
            {"customers", 0},
            {"drivers", 0},
            {"driver_vacancies", 0},
            {"ongoing_shifts", 0},
            {"shifts_closed", 0}
        };


    public:
        static int GarageLimit; // 64
        static int EachCarLimit; // 4
        static int DriverLimit; // 64

        TaxiAgency();
        // TaxiAgency(string TAXIES_FILE, string SHIFT_FILE_KEYWORD);

        int set_total_idol_taxies();

        void populate_taxies(const char* TAXIES_FILE);
        void populate_customer_db(const char* CUSTOMERS_FILE);
        void populate_drivers_idol(const char* DRIVERS_FILE);

        void print_taxies();
        void print_customer_db();
        IndexInstance<Taxi> retrieve_taxi_by_id(string id);
        void add_taxi(bool hybrid, string id, string manufacturer, int fare_amount, int number);
        void add_customer(string firstname, string lastname, string uuid, int balance);

        IndexInstance<Driver> search_driver_by_uuid(string uuid);
        IndexInstance<Customer> search_customer_by_uuid(string uuid);

        void print_agency_details(){
        };

        friend ostream& operator<<(ostream& output, const TaxiAgency& A);

        template <typename T>
        vector<T> operator[](string entity);
        template <typename T>
        list<T> operator[](string entity);

        unordered_map<string, int> operator[](string entity);

        // Customer add_customer(string firstname, string lastname, string uuid, double balance);

        // IndexInstance<> search_by_uuid();

};