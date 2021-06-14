# Shift
```cpp
Shift();
```
Shift Default Constructor: Instantiates a brand new Shift object; no arguments required.

```cpp
Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int taxi_fare_amount, int waiting_charges);
```
Instantiates a Shift Object, with the following paramters:
 * customer_uuid - uuid of the customer who booked the Shift
 * driver_in_charge_uuid - uuid of the driver in charge for the Shift
 * taxi_id - id of the taxi demanded by the customer upon successful booking
 * taxi_fare_amount
 * waiting_charges

[Total Ride Cost](./README.md#Total_Cost)

```cpp
Shift(string customer_uuid, string driver_in_charge_uuid, string taxi_id, int taxi_fare_amount, int waiting_charges, int running_hours, int waiting_hours, int total_cost);
```
Instantiates a Shift Object, with the following paramters:
 * customer_uuid - uuid of the customer who booked the Shift
 * driver_in_charge_uuid - uuid of the driver in charge for the Shift
 * taxi_id - id of the taxi demanded by the customer upon successful booking
 * taxi_fare_amount
 * waiting_charges
 * running_kms - kilometers ran by the taxi up until the current time
 * waiting_hours - hours driver waited up until the current time
 * total_cost - the amoun to be paid by the customer based on the total running and waiting time up until now

```cpp
friend ostream& operator<<(ostream& output, const Shift& S);
```
Insertion opertaor overloading to print the details of the Shift.

```cpp
void print_shift();
```
Prints the details of the current Shift.

## Getter Methods
```cpp
const string& getCustomerUUID() const;
```
Returns the customer uuid associated with the Shift.

```cpp
const string& getDriverUUID() const;
```
Returns the driver uuid associated with the Shift.

```cpp
const string& getCarID() const;
```
Returns the taxi id associated with the Shift.

```cpp
const int& getFareAmount() const;
```
Returns the fare_amount of the Taxi associated with the Shift.

```cpp
const int& getWaitingCharges() const;
```
Returns the waiting charges associated with the Taxi Agency.

```cpp
const int& getRunningKms() const;
```
Returns the number of kilometers ran by the taxi up until the current time.

```cpp
const int& getWaitingHours() const;
```
Returns the number of hours driver waited up until the current time.

```cpp
const int& getTotalCost() const;
```
Returns the total cost of the shift up until the current time.

## Setter Methods
```cpp
void setRunningKms(int running_kms);
```
Set the number of kilometers ran by the Taxi.

```cpp
void setWaitingHours(int waiting_hours);
```
Set the number Hours waited by the Driver.

```cpp
void setTotalCost(int total_cost);
```
Set the total cost of the Shift.

## Update Methods
```cpp
void updateRunningKms(int del_running_kms);
```
Update the number of kilometers ran by the Taxi to eventually compute the cost of the Shift. The running kms passed in as argument is added to the number of kilometer Taxi has already ran.

```cpp
void updateWaitingHours(int del_waiting_hours);
```
Update the number Hours waited by the Driver to eventually compute the cost of the Shift. The waiting hours passed in as argument is added to the number of hours the Driver has already waited on a stop.

```cpp
void updateTotalCost(int del_total_cost);
```
Update the total cost of the Shift.

```cpp
void extend_tenure(int del_running_kms, int del_waiting_hours);
```
Extend the Tenure of the Shift.