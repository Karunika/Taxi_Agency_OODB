#include <iostream>
#include <exception>

#include "./include/TaxiAgency.hpp"
#include "./include/assert.hpp"
#include "./config.hpp"

using namespace std;

int main(){
    try{
        {
            TaxiAgency myTaxiAgency;
            cout << endl;

            test_partition("Import CSV data", [&]() {
                myTaxiAgency.populate_taxies(TAXIES_FILE);
                myTaxiAgency.populate_customer_db(CUSTOMERS_FILE);
                myTaxiAgency.populate_drivers_db(DRIVERS_FILE);
            });
            
            test_partition("Print Lists?", [&]() {
                print_prompt("Print List?", [&]() {
                    myTaxiAgency.print_taxies();
                    myTaxiAgency.print_customer_db();
                    myTaxiAgency.print_drivers_db();
                });
            });

            test_partition("Retrieve Taxi by ID", [&]() {
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 3.2").index, 0, "First Taxi");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 2.0 T AT").index, 1, "Second Taxi");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Colorado Work Truck").index, 17, "Random Taxi near start");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2011 Chevrolet Express LS 2500").index, 30, "Random Taxi in the middle");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2011 Nissan 370Z NISMO").index, 40, "Random Taxi near end");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2012 Bentley Continental Supersports Convertible").index, 48, "Last Taxi");

                test_partition("-- Correctness of Taxi Details", [&]() {
                    IndexInstance<Taxi> taxi =  myTaxiAgency.retrieve_taxi_by_id("2009 Audi A3 3.2");

                    assert_eq(taxi.data->hybrid, true, "First Taxi Details");
                    assert_eq(taxi.data->manufacturer, (string) "Audi", "First Taxi Details");
                    assert_eq(taxi.data->fare_amount, 9, "First Taxi Details");
                    assert_eq(taxi.data->number, 1, "First Taxi Details");

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
                });

                test_partition("-- Taxi Retrieval Exception Handling", [&]() {
                    try{
                        myTaxiAgency.retrieve_taxi_by_id("2012 Chevrolet Coloado Work Truck"); // mispelled
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
            });

            test_partition("Insert New Taxi", [&]() {
                myTaxiAgency.insert_new_taxi_breed(true, "2010 Volvo XC60 3.2", "Volvo", 14, 4);
                myTaxiAgency.insert_new_taxi_breed(true, "2011 Volvo XC70 3.2", "Volvo", 20);
                test_partition("-- Insert Taxi with repeated id", [&]() {
                    try{
                        myTaxiAgency.insert_new_taxi_breed(true, "2011 Volvo XC70 3.2", "Volvo", 20, 2);
                        cout << "This should not be printed" << endl;
                    }catch(...){}
                });
                myTaxiAgency.insert_new_taxi_breed(true, "2011 Volvo XC70 T6 AWD", "Volvo", 20, 3);
                myTaxiAgency.insert_new_taxi_breed(true, "2010 Volvo XC70 T6 AWD", "Volvo", 20);
                myTaxiAgency.insert_new_taxi_breed(true, "2010 Volvo XC70 3.2", "Volvo", 20, 2);
                test_partition("-- Taxi Limit exceeded", [&]() {
                    try{
                        myTaxiAgency.insert_new_taxi_breed(true, "2011 Toyota 4Runner SR5", "Toyota", 20, 2);
                        cout << "This should not be printed" << endl;
                    }catch(range_error e){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Increase existing Taxi count", [&]() {
                    assert_eq(myTaxiAgency.add_taxi_by_id("2009 Audi A3 3.2").data->number, 2, "First Taxi count increased");
                    assert_eq(myTaxiAgency.add_taxi_by_id("2010 Volvo XC70 3.2").data->number, 3, "Last Taxi count increased");
                    assert_eq(myTaxiAgency.add_taxi_by_id("2011 Chevrolet Colorado Work Truck", 2).data->number, 3, "Last Taxi count increased");

                    test_partition("-- -- Taxi count range Exception", [&]() {
                        try{
                            myTaxiAgency.add_taxi_by_id("2011 Chevrolet Colorado Crew Cab 1LT");
                            cout << "This should not be printed" << endl;
                        }catch(range_error){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                        try{
                            myTaxiAgency.add_taxi_by_id("2011 Chevrolet Express LS 1500", 3);
                            cout << "This should not be printed" << endl;
                        }catch(range_error){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                    test_partition("-- -- Invalid increase factor Exception", [&]() {
                        try{
                            myTaxiAgency.add_taxi_by_id("2011 Chevrolet Colorado Crew Cab 1LT", -3);
                            cout << "This should not be printed" << endl;
                        }catch(invalid_argument){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                });
            });

            test_partition("Decrease existing Taxi count", [&]() {
                assert_eq(myTaxiAgency.remove_taxi_by_id("2009 Audi A3 2.0 T AT").data->number, 3, "Second Taxi count decreased");
                test_partition("-- Taxi count range below zero", [&]() {
                    try{
                        myTaxiAgency.remove_taxi_by_id("2009 Audi A4 Sedan 2.0 T Quattro", 5);
                        cout << "This should not be printed" << endl;
                    }catch(range_error){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Deleting existing Taxi", [&]() {
                    assert_eq(myTaxiAgency.retrieve_taxi_by_id("2012 Acura TL SH-AWD").data->number, 2, "Count Decreament Deletion");
                    myTaxiAgency.remove_taxi_by_id("2012 Acura TL SH-AWD", 2);
                    try{
                        myTaxiAgency.retrieve_taxi_by_id("2012 Acura TL SH-AWD");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
            });

            test_partition("Search User by UUID", [&]() {
                test_partition("-- Search Customer by UUID", [&]() {
                    
                    assert_eq(myTaxiAgency.search_customer_by_uuid("1woonaa").index, 0, "First Customer");
                    assert_eq(myTaxiAgency.search_customer_by_uuid("278marian").index, 1, "Second Customer");
                    assert_eq(myTaxiAgency.search_customer_by_uuid("Janusz").index, 11, "Random Customer near start");
                    assert_eq(myTaxiAgency.search_customer_by_uuid("behind_you218").index, 28, "Random Customer in the middle");
                    assert_eq(myTaxiAgency.search_customer_by_uuid("maja78wojtek").index, 50, "Random Customer near end");
                    assert_eq(myTaxiAgency.search_customer_by_uuid("zula_bula").index, 59, "Last Customer");

                    test_partition("-- -- Correctness of Customer Details", [&]() {
                        IndexInstance<Customer> customer =  myTaxiAgency.search_customer_by_uuid("1woonaa");

                        assert_eq(customer.data->getFirstname(), (string) "Iwona", "First Customer Details");
                        assert_eq(customer.data->getLastname(), (string) "Wislawa", "First Customer Details");
                        assert_eq(customer.data->getBalance(), 561, "First Customer Details");
                        assert_eq(customer.data->getStatus(), IDLE, "First Customer Details");

                        customer = myTaxiAgency.search_customer_by_uuid("behind_you218");

                        assert_eq(customer.data->getFirstname(), (string) "Wlodek", "Middle Customer Details");
                        assert_eq(customer.data->getLastname(), (string) "Jagoda", "Middle Customer Details");
                        assert_eq(customer.data->getBalance(), 556, "Middle Customer Details");
                        assert_eq(customer.data->getStatus(), IDLE, "Middle Customer Details");
                    
                        customer = myTaxiAgency.search_customer_by_uuid("zula_bula");

                        assert_eq(customer.data->getFirstname(), (string) "Natasza", "Last Customer Details");
                        assert_eq(customer.data->getLastname(), (string) "Zula", "Last Customer Details");
                        assert_eq(customer.data->getBalance(), 887, "Last Customer Details");
                        assert_eq(customer.data->getStatus(), IDLE, "Last Customer Details");
                    });
                    test_partition("-- -- Customer Retrieval Exception Handling", [&]() {
                        try{
                            myTaxiAgency.search_customer_by_uuid("random_nonexistant_uuid");
                            cout << "This should not be printed" << endl;
                        }catch(invalid_argument){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                });             
                
                test_partition("-- Search Driver by UUID", [&]() {
                    
                    assert_eq(myTaxiAgency.search_driver_by_uuid("0kku").index, 0, "First Customer");
                    assert_eq(myTaxiAgency.search_driver_by_uuid("12seweryn").index, 1, "Second Customer");
                    assert_eq(myTaxiAgency.search_driver_by_uuid("Emil_").index, 11, "Random Customer near start");
                    assert_eq(myTaxiAgency.search_driver_by_uuid("Urban").index, 28, "Random Customer in the middle");
                    assert_eq(myTaxiAgency.search_driver_by_uuid("krzesimir").index, 50, "Random Customer near end");
                    assert_eq(myTaxiAgency.search_driver_by_uuid("ramirolaz").index, 59, "Last Customer");

                    test_partition("-- -- Correctness of Driver Details", [&]() {
                        IndexInstance<Driver> driver =  myTaxiAgency.search_driver_by_uuid("0kku");

                        assert_eq(driver.data->getFirstname(), (string) "Wiktoria", "First Driver Details");
                        assert_eq(driver.data->getLastname(), (string) "Seweryna", "First Driver Details");
                        assert_eq(driver.data->getDLN(), (string) "2026/9598325693", "First Driver Details");
                        assert_eq(driver.data->getStatus(), IDLE, "First Driver Details");

                        driver = myTaxiAgency.search_driver_by_uuid("Urban");

                        assert_eq(driver.data->getFirstname(), (string) "Urban", "Middle Driver Details");
                        assert_eq(driver.data->getLastname(), (string) "Pola", "Middle Driver Details");
                        assert_eq(driver.data->getDLN(), (string) "2026/0809430679", "Middle Driver Details");
                        assert_eq(driver.data->getStatus(), IDLE, "Middle Driver Details");
                    
                        driver = myTaxiAgency.search_driver_by_uuid("ramirolaz");

                        assert_eq(driver.data->getFirstname(), (string) "Ramiro", "Last Driver Details");
                        assert_eq(driver.data->getLastname(), (string) "Lazzari", "Last Driver Details");
                        assert_eq(driver.data->getDLN(), (string) "2045/5095962113", "Last Driver Details");
                        assert_eq(driver.data->getStatus(), IDLE, "Last Driver Details");
                    });
                    test_partition("-- -- Driver Retrieval Exception Handling", [&]() {
                        try{
                            myTaxiAgency.search_driver_by_uuid("random_nonexistant_uuid");
                            cout << "This should not be printed" << endl;
                        }catch(invalid_argument){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                });
            });

            test_partition("Creating & Inserting User", [&]() {
                test_partition("-- Inserting new Customer", [&]() {
                    myTaxiAgency.add_customer("Antonina", "Jolanta", "Aaantonio1", 879);
                    myTaxiAgency.add_customer("Waleria", "Anastazy", "Waleria");
                    myTaxiAgency.add_customer("Ziemowit", "Izabela", "Ziemowit_", 546, IDLE);
                    test_partition("-- -- Customer with invalid Registration Details", [&]() {
                        try{
                            myTaxiAgency.add_customer("Franciszka", "Sonia", "<Son!a>", 346, IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_customer("Eustachy", "Ida", "Ida__#_", 980, IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_customer("Zachariasz ", "Sonia", "Sonia", 245, IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_customer("Mirek", "Radz\\im", "Mirek", 345, IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                    });
                    test_partition("-- -- Insert Customer with repeating UUID", [&]() {
                        try{
                            myTaxiAgency.add_customer("Ziemowit", "Izabela", "Ziemowit_", 2);
                            cout << "This should not be printed" << endl;
                        }catch(invalid_argument){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                    myTaxiAgency.add_customer("Jaroslawa", "Mariusz", "Mariusz", 189);
                    myTaxiAgency.add_customer("Kunegunda", "Fryderyka", "fryderyka7", 235, IDLE);
                    test_partition("-- -- Capacity to server customer exceeded", [&]() {
                        try{
                            myTaxiAgency.add_customer("Miloslaw", "Dymitr", "miloslaw", 245, IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(range_error){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                });
                
                test_partition("-- Inserting new Driver", [&]() {
                    myTaxiAgency.add_driver("Sybilla", "Lucyna", "Sybillalalala", "2026/7341063757");
                    myTaxiAgency.add_driver("Juliusz", "Karina", "god_", "2026/1179926045", IDLE);
                    myTaxiAgency.add_driver("Celestyna", "Serafina", "Celestyna", "2026/6610130546");
                    test_partition("-- -- Driver with invalid Registration Details", [&]() {
                        try{
                            myTaxiAgency.add_driver("Teresa", "Beniamin", "T.r.sa", "2026/0302475846", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_driver("Waldek", "Teodozja", "...%&*?$!...", "2026/2065376078", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_driver("Marzanna$", "Sabina", "Sabina", "2049/7036077301", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                        try{
                            myTaxiAgency.add_driver("Dr.", "Krystyn", "dr_krystyn", "2078/5639892413", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(...){};
                    });
                    test_partition("-- -- Insert Customer with repeating UUID", [&]() {
                        try{
                            myTaxiAgency.add_driver("Celestyna", "Krystian", "Celestyna", "2026/5908677321", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(invalid_argument){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                    myTaxiAgency.add_driver("Aneta", "Krystiana", "bub", "2026/0466706457", IDLE);
                    myTaxiAgency.add_driver("Antonie", "Dunn", "pablo", "2026/4358330581", IDLE);
                    test_partition("-- -- Insertion Exception Handling", [&]() {
                        try{
                            myTaxiAgency.add_driver("Pawel", "Marek", "pawe_nata", "2026/6688939310", IDLE);
                            cout << "This should not be printed" << endl;
                        }catch(range_error){}catch(...){
                            cout << "This should not be printed" << endl;
                        }
                    });
                });
            });

            test_partition("Deleting User by UUID", [&]() {
                test_partition("-- Deleting Customer", [&]() {
                    myTaxiAgency.delete_customer_user_by_uuid("1woonaa");
                    try{
                        myTaxiAgency.search_customer_by_uuid("1woonaa");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                    myTaxiAgency.delete_customer_user_by_uuid("Jackeveneo");
                    try{
                        myTaxiAgency.search_customer_by_uuid("Jackeveneo");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                    myTaxiAgency.delete_customer_user_by_uuid("zula_bula");
                    try{
                        myTaxiAgency.search_customer_by_uuid("zula_bula");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Deleting Driver", [&]() {
                    myTaxiAgency.delete_driver_user_by_uuid("0kku");
                    try{
                        myTaxiAgency.delete_driver_user_by_uuid("0kku");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                    myTaxiAgency.delete_driver_user_by_uuid("amato_ap782");
                    try{
                        myTaxiAgency.delete_driver_user_by_uuid("amato_ap782");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                    myTaxiAgency.delete_driver_user_by_uuid("ramirolaz");
                    try{
                        myTaxiAgency.delete_driver_user_by_uuid("ramirolaz");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
            });

            test_partition("Booking Taxi", [&]() {
                myTaxiAgency.book_taxi("Renata", "2009 Audi A5 3.2 AT");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A5 3.2 AT").data->available_number, 3);
                test_partition("-- Re-Booking Taxi Exception", [&]() {
                    try{
                        myTaxiAgency.book_taxi("Renata", "2011 BMW X6 M");
                        cout << "This should not be printed" << endl;
                    }catch(booking_unsuccessful){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Booking without enough Balance", [&]() {
                    try{
                        myTaxiAgency.book_taxi("Ireneusz", "2009 Audi A5 3.2 AT");
                        cout << "This should not be printed" << endl;
                    }catch(booking_unsuccessful){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Booking instigated by an unregistered Customer", [&]() {
                    try{
                        myTaxiAgency.book_taxi("AlkaBalka", "2011 BMW X6 M");
                        cout << "This should not be printed" << endl;
                    }catch(invalid_argument){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                myTaxiAgency.book_taxi("JJJJ8888", "2009 Audi A5 3.2 AT");
                assert_eq(myTaxiAgency.retrieve_taxi_by_id("2009 Audi A5 3.2 AT").data->available_number, 2);
                myTaxiAgency.book_taxi("Aaantonio1", "2009 Audi A5 3.2 AT");
                myTaxiAgency.book_taxi("fryderyka7", "2009 Audi A5 3.2 AT");
                test_partition("-- Booking an Unavailable Taxi", [&]() {
                    try{
                        myTaxiAgency.book_taxi("8brunomars", "2009 Audi A5 3.2 AT");
                        cout << "This should not be printed" << endl;
                    }catch(booking_unsuccessful){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                test_partition("-- Providing an Invalid Taxi Id", [&]() {
                    try{
                        myTaxiAgency.book_taxi("8brunomars", "2012 ura TL"); // mispelled
                        cout << "This should not be printed" << endl;
                    }catch(booking_unsuccessful){}catch(...){
                        cout << "This should not be printed" << endl;
                    }
                });
                myTaxiAgency.book_taxi("Roland_o_o_o_", "2012 Chevrolet Colorado Crew Cab 1LT");
                myTaxiAgency.book_taxi("_get_me_", "2010 Chevrolet Express LS 1500 AWD");
                myTaxiAgency.book_taxi("ilona", "2010 Volvo V50 R-Design");
            });

            test_partition("Printing Ongoing Shifts", [&]() {
                print_prompt("Print a list of Ongoing Shifts?", [&]() {
                    myTaxiAgency.print_ongoing_shifts();
                });
            });

            test_partition("Extending Shift Tenure", [&]() {
                myTaxiAgency.extend_shift_tenure("ilona");
                myTaxiAgency.extend_shift_tenure("ilona", 2, 4);
                myTaxiAgency.extend_shift_tenure("Roland_o_o_o_", 1, 2);
                myTaxiAgency.extend_shift_tenure("_get_me_", 4, 6);
            });

            test_partition("Closing Shifts", [&]() {
                myTaxiAgency.end_shift("Renata");
                myTaxiAgency.end_shift("Roland_o_o_o_");
                myTaxiAgency.end_shift("_get_me_");
                myTaxiAgency.end_shift("ilona");
            });

            test_partition("Printing Shift History", [&]() {
                print_prompt("Print a Record of all Shifts?", [&]() {
                    myTaxiAgency.print_shift_history();
                });
            });

            test_partition("Upgrade Taxi Agency", [&]() {
                myTaxiAgency.upgrade_agency_assets(128, 6, 128);
            });

            test_partition("Exporting CSV Data", [&]() {
                myTaxiAgency.export_taxies(TAXIES_FILE);
                myTaxiAgency.export_driver_db(DRIVERS_FILE);
                myTaxiAgency.export_customer_db(CUSTOMERS_FILE);
                myTaxiAgency.export_ongoing_shifts(CURRENT_SHIFTS_FILE);
                myTaxiAgency.export_shift_history(SHIFT_HISTORY_FILE);
            });

            cout << endl;
        } // End of scope to trigger the destructure

        {
            TaxiAgency myTaxiAgency;
            cout << endl;

            test_partition("Import Shift CSV Data", [&]() {
                myTaxiAgency.import_current_shifts(CURRENT_SHIFTS_FILE);
                myTaxiAgency.import_shift_history(SHIFT_HISTORY_FILE); // fine
            });

            test_partition("Printing Shift Lists", [&]() {
                print_prompt("Print List?", [&]() {
                    myTaxiAgency.print_ongoing_shifts();
                    myTaxiAgency.print_shift_history();
                });
            });

            cout << endl;
        }

        cout << "Tests successful!" << endl;


    }catch(assertion_failure& e){
        cout << "Test Failed: Assertion \"" << e.what() << endl;
    }catch(std::exception& e){
        cout << e.what() << endl;
    }
    return 0;
}