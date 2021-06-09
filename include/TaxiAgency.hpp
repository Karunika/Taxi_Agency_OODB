#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

#include "../dep/rang.hpp"

#include "./Taxi.hpp"
#include "./Driver.hpp"
#include "./Customer.hpp"
#include "./Shift.hpp"


using namespace std;

class Customer;

template <typename T>
struct IndexInstance{
    int index;
    T* data;
};

class TaxiAgency{
    private:
        vector<Taxi> taxies;
        vector<Driver> driver_db;
        vector<Customer> customer_db;

        list<Shift> current_shifts;
        list<Shift> shift_history;


        int DriverWagePerMonth; // 1000

        int GarageLimit; // 64 (Brand Limit)
        int EachCarLimit; // 4
        int DriverLimit; // 64

        IndexInstance<Driver> lastFreeDriver;
        
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

        TaxiAgency();
        ~TaxiAgency();
        void print_agency_stats();
        friend ostream& operator<<(ostream& output, TaxiAgency& A);

        void populate_taxies(const char* TAXIES_FILE);
        void populate_customer_db(const char* CUSTOMERS_FILE);
        void populate_drivers_db(const char* DRIVERS_FILE);

        void print_taxies();
        void print_customer_db();
        void print_drivers_db();

        IndexInstance<Taxi> retrieve_taxi_by_id(string id);
        IndexInstance<Driver> search_driver_by_uuid(string uuid);
        IndexInstance<Customer> search_customer_by_uuid(string uuid);

        void insert_new_taxi_breed(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1);
        void add_customer(string firstname, string lastname, string uuid, int balance, Status status);
        void add_driver(string firstname, string lastname, string uuid, string dln, Status status);

        IndexInstance<Taxi> add_taxi_by_id(string id, int num = 1);
        IndexInstance<Taxi> remove_taxi_by_id(string id, int num = 1);

        void delete_driver_user_by_uuid(string uuid);
        void delete_customer_user_by_uuid(string uuid);

        template <typename T>
        vector<T> operator[](string entity);
        template <typename T>
        list<T> operator[](string entity);
        unordered_map<string, int> operator[](string entity);


        int book_taxi(string customer_uuid, string car_id);


        // TODO
        void upgrade_agency_assets(int garage_limit, int each_car_limit, int driver_vacancies);
        void driver_promotion(int new_wage);
        
        void export_taxies(const char* TAXIES_FILE);
        void export_customer_db(const char* CUSTOMERS_FILE);
        void export_driver_db(const char* DRIVERS_FILE);

        void export_all(const char* TAXIES_FILE, const char* CUSTOMERS_FILE, const char* DRIVERS_FILE);

};