#include <iostream>
#include <exception>
#include "./include/TaxiAgency.hpp"
#include "./include/assert.hpp"
#include "./config.hpp"
#include "./dep/rang.hpp"

using namespace std;

int main(){
    TaxiAgency myTaxiAgency;
    try{
        // Populate lists containers with sample CSV data
        myTaxiAgency.populate_taxies(TAXIES_FILE);
        myTaxiAgency.populate_customer_db(CUSTOMERS_FILE);
        myTaxiAgency.populate_drivers_db(DRIVERS_FILE);

        // myTaxiAgency.print_taxies();
        // myTaxiAgency.print_customer_db();
        // myTaxiAgency.print_drivers_db();

        {
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 3.2").index, 0, "First Taxi");
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 2.0 T AT").index, 1, "Second Taxi");
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Colorado Work Truck").index, 17, "Random Taxi near start");
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2011 Chevrolet Express LS 2500").index, 30, "Random Taxi in the middle");
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2011 Nissan 370Z NISMO").index, 40, "Random Taxi near end");
            assert_eq(myTaxiAgency.retrieve_taxi_by_id("2012 Bentley Continental Supersports Convertible").index, 48, "Last Taxi");

            IndexInstance<Taxi> taxi =  myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 3.2");

            assert_eq(taxi.data->hybrid, true, "First Taxi Details");
            assert_eq(taxi.data->manufacturer, (string) "Audi", "First Taxi Details");
            assert_eq(taxi.data->fare_amount, 23, "First Taxi Details");
            assert_eq(taxi.data->number, 4, "First Taxi Details");

            taxi = myTaxiAgency.retrieve_taxi_by_id("2011 Chevrolet Express LS 2500");

            assert_eq(taxi.data->hybrid, true, "Middle Taxi Details");
            assert_eq(taxi.data->manufacturer, (string) "Chevrolet", "Middle Taxi Details");
            assert_eq(taxi.data->fare_amount, 32, "Middle Taxi Details");
            assert_eq(taxi.data->number, 4, "Middle Taxi Details");
            
            taxi = myTaxiAgency.retrieve_taxi_by_id("2012 Bentley Continental Supersports Convertible");

            assert_eq(taxi.data->hybrid, true, "Last Taxi Details");
            assert_eq(taxi.data->manufacturer, (string) "Bentley", "Last Taxi Details");
            assert_eq(taxi.data->fare_amount, 36, "Last Taxi Details");
            assert_eq(taxi.data->number, 4, "Last Taxi Details");

        }

        // Exception handling Tests
        try{
            myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Coloado Work Truck"); // mispelled
            cout << rang::style::italic << "This should not be printed" << rang::style::reset << endl;
        }catch(invalid_argument e){}catch(...){
            cout << rang::style::italic << "This should not be printed" << rang::style::reset << endl;
        }

        myTaxiAgency.export_taxies(TAXIES_FILE);
        myTaxiAgency.export_driver_db(DRIVERS_FILE);

        cout << rang::fg::green << "Tests successful!" << endl;

    }catch(std::exception& e){
        cout << rang::fg::red << e.what() << endl;
    }
    return 0;
}