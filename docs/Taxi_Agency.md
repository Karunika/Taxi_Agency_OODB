# Taxi Agency

## Member Function Description:

```cpp
TaxiAgency(); 
```
Taxi Agency Default Constructor: Instantiates a brand new Taxi Agency object; no arguments required.

```cpp
~TaxiAgency();
```
Taxi Agency Destructor: Invoked whenever a Taxi Agency Instance is destroyed.

```cpp
void print_agency_stats();
```
Prints Agency related statistics in the terminal.

```cpp
friend ostream& operator<<(ostream& output, TaxiAgency& A);
```
Insertion Operator overloading to print the Agency Statistics.



## Taxi Related Methods

```cpp
void populate_taxies(const char* TAXIES_FILE);
```
Populates a STL vector container with taxi objects whose details are supplied in the form of `CSV` data. 
Takes in the relative path `TAXIES_FILE` of the file containing the `CSV` data as its argument.

```cpp
void print_taxies();
```
Prints a list of all the taxies owned by the Agency along with its details in the standard output.

```cpp
IndexInstance<Taxi> retrieve_taxi_by_id(string id);
```
Returns an `IndexInstance` of the taxi with the id `id`, which is supposed to be passed as an argument.

```cpp
void insert_new_taxi_breed(bool hybrid, string id, string manufacturer, int fare_amount, int number = 1);
```
Pushes a brand new Taxi Object onto the Taxi List, with the following details:
 1. `hybrid: bool` - whether or not the car is hybrid
 2. `id: int` - primary key
 3. `manufacturer: string` - brand name
 4. `fare_amount: int` - fare per kilometer
 5. `number: int` - number of the breed of taxi owned by the Agency

```cpp
IndexInstance<Taxi> add_taxi_by_id(string id, int num = 1);
```
Increases the count of taxi with id `id` by `num` and returns an `IndexInstance` struct of it.
If the resulting count of taxi exceeds the paramter `EachCarLimit`, an exception is thrown.

```cpp
IndexInstance<Taxi> remove_taxi_by_id(string id, int num = 1);
```
Decrease the count of taxi with id `id` by `num` and returns an `IndexInstance` struct of it.
If the resulting count of taxi preceeds `0`, an exception is thrown. If it becomes `0`, the taxi is permanently deleted.

```cpp
void export_taxies(const char* TAXIES_FILE);
```
Stringifies the Taxi list into raw `CSV` data and injects it into a file, whose relative path has to be provided as an argument. If the file doesn't already exist, a new file is created.




## Customer Related Methods
```cpp
void populate_customer_db(const char* CUSTOMERS_FILE);
```
Populates a STL vector container with customer objects whose details are supplied in the form of `CSV` data. 
Takes in the relative path `CUSTOMERS_FILE` of the file containing the `CSV` data as its argument.

```cpp
void print_customer_db();
```
Prints a list of all the customers registered with the Agency in the standard output.

```cpp
IndexInstance<Customer> search_customer_by_uuid(string uuid);
```
Returns an `IndexInstance` of the customer object by the given `uuid`.

```cpp
void add_customer(string firstname, string lastname, string uuid, int balance = 0, Status status = IDLE);
```
Pushes a brand new Taxi Object onto the Taxi List, with the following details:
 1. `firstname: string`
 2. `lastname: string`
 3. `uuid: string` - primary key
 4. `balance: int` - account balance
 5. `status: Status (IDLE | ONSHIFT)` - whether or not the customer is on a shift

```cpp
void delete_customer_user_by_uuid(string uuid);
```
Deletes the driver asscoiated with the `uuid` passed in as argument from the customer database.

```cpp
void export_customer_db(const char* CUSTOMERS_FILE);
```
Stringifies the Customer list into raw `CSV` data and streams it into a file, whose relative path has to be provided as an argument. If the file doesn't already exist in the given relative path, a new file is created.






## Driver Related Methods
```cpp
void populate_drivers_db(const char* DRIVERS_FILE);
```
Populates a STL vector container with driver objects whose details are supplied in the form of `CSV` data. 
Takes in the relative path `DRIVERS_FILE` of the file containing the `CSV` data as its argument.

```cpp
void print_drivers_db();
```
Prints a list of all the drivers recruited in the Agency in the standard output.

```cpp
IndexInstance<Driver> search_driver_by_uuid(string uuid);
```
Returns an `IndexInstance` of the driver object by the given `uuid`.

```cpp
void add_driver(string firstname, string lastname, string uuid, string dln, Status status = IDLE);
```
Pushes a brand new Taxi Object onto the Taxi List, with the following details:
 1. `firstname: string`
 2. `lastname: string`
 3. `uuid: string` - primary key
 4. `dln: string` - drvier license number issued by the government
 5. `status: Status (IDLE | ONSHIFT)` - whether or not the driver is on a shift

```cpp
void delete_driver_user_by_uuid(string uuid);
```
Deletes the driver asscoiated with the `uuid` passed in as argument from the driver database.

```cpp
void export_driver_db(const char* DRIVERS_FILE);
```
Stringifies the Driver list into raw `CSV` data and streams it into a file, whose relative path has to be provided as an argument. If the file doesn't already exist in the given relative path, a new file is created.



## Shifts Related Methods
```cpp
void import_current_shifts(const char* CURRENT_SHIFTS_FILE);
```
Imports all the ongoing shifts from the file located at the relative path passed in as an argument and populates a STL List container accordingly.

```cpp
void import_shift_history(const char* SHIFT_HISTORY_FILE);
```
Imports all the shifts taken place in the history of the Agency, from the file located at the relative path passed in as an argument and populates a STL List container accordingly.

```cpp
void export_shift_history(const char* SHIFT_HISTORY_FILE);
```
Stringifies the record of all the shifts into raw `CSV` data and injects it into a file, whose relative path has to be provided as an argument. If the file doesn't already exist in the given relative path, a new file is created.

```cpp
void export_ongoing_shifts(const char* CURRENT_SHIFTS_FILE);
```
Stringifies the ongoing shift list into raw `CSV` data and injects it into a file, whose relative path has to be provided as an argument. If the file doesn't already exist in the given relative path, a new file is created.

```cpp
void book_taxi(string customer_uuid, string car_id);
```
Instantiates a brand new Shift based on the request of a customer, whose `uuid` has to be provided as the first argument followed by the `id` of car being demanded. If the car `id` is invalid or no drivers are available or the customer doesn't have enough balance, an exception is thrown. Thereafter, the status of the customer is toggled to `ONSHIFT`.

```cpp
void extend_shift_tenure(string customer_uuid, int del_running_km = 12, int del_waiting_hours = 12)
```
Increase the `Running kms` and `Waiting Hours` of the of the shift corresponding to the customer with provided `uuid`.

```cpp
Shift retrieve_shift_details_by_customer(string customer_uuid);
```
Returns an `Shift` object of the shift corresponding to the customer with provided `uuid`.

```cpp
void end_shift(string customer_uuid);
```
A shift is bought to an end, and the customer is asked to make transaction.

```cpp
void print_ongoing_shifts();
```
Prints a list of all the ongoing shifts along with its details i.e., the customer who booked it, the driver in charge, and the Taxi in use.

```cpp
void print_shift_history();
```
Prints a list of all the shifts taken placce in the past along with its details.


## Other Methods
```cpp
void upgrade_agency_assets(int garage_limit, int each_car_limit, int driver_vacancies);
```
Upgrades the Agency, i.e., capacity of the vector containers and thus, allows more customers to be served.

```cpp
void driver_promotion(int new_wage);
```
Updated the Monthly wage of driver based on the amount passed in as argument.


```cpp
void export_all(const char* TAXIES_FILE, const char* CUSTOMERS_FILE, const char* DRIVERS_FILE);
```
Exports stringified Taxi, Customer and Driver list in their resptive filer. Expects their relative paths as argument.