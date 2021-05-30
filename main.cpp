#include <iostream>
#include <exception>
#include <cassert>
#include "./include/TaxiAgency.hpp"
#include "./config.hpp"
#include "./dep/rang.hpp"

struct test_failure : public exception {
    const char* msg;
    test_failure(const char* msg) : msg(msg){
    };
    const char * what () const throw () {
        return msg;
    };
};

using namespace std;

TaxiAgency myTaxiAgency;

int main(){
    try{
        // Populate lists containers with sample CSV data
        myTaxiAgency.populate_taxies(TAXIES_FILE);
        myTaxiAgency.populate_customer_db(CUSTOMERS_FILE);
        myTaxiAgency.populate_drivers_db(DRIVERS_FILE);

        // Print
        myTaxiAgency.print_taxies();
        myTaxiAgency.print_customer_db();
        myTaxiAgency.print_drivers_db();


        if(myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Colorado Work Truck").index != 17)
            throw test_failure("Test Failed: Output was not correct");

        // Exception handling Tests
        try{
            myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Coloado Work Truck"); // mispelled
            cout << rang::style::italic << "This should not be printed" << rang::style::reset << endl;
        }catch(invalid_argument e){}catch(...){
            cout << rang::style::italic << "This should not be printed" << rang::style::reset << endl;
        }

        cout << rang::fg::green << "Tests successful!" << endl;

    }catch(std::exception& e){
        cout << rang::fg::red << e.what() << endl;
    }
    return 0;
}