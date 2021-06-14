# User
```cpp
User();
```
User Default Constructor: Instantiates a brand new User object; no arguments required.

```cpp
User(string firstname, string lastname, string uuid);
```
Instantiates an User Object, requires following details:
 1. `firstname: string`
 2. `lastname: string`
 3. `uuid: string` - primary key

The function internally is responsible to check the correctness of `uuid` and the name, and thus, throw errors accordingly.
[Valid UUID](./README.md#User_Constraints)

## Getter Methods
```cpp
string getFirstname(){ return firstname; };
```
Returns the firstname of the associated user.

```cpp
string getLastname(){ return lastname; };
```
Returns the lastname of the associated user.

```cpp
string getUUID(){ return uuid; };
```
Returns the `uuid` of the associated user.

## Setters

```cpp
string updateFirstname(string firstname);
```
Updates the firstname of the user by the name passed in as argument.

```cpp
string updateLastname(string lastname);
```
Updates the firstname of the user by the name passed in as argument.


## Operators
```cpp
friend bool operator<(const User& u1, const User& u2);
friend bool operator>(const User& u1, const User& u2);
friend bool operator==(const User& u1, const User& u2);
friend bool operator!=(const User& u1, const User& u2);
```
Comparison operators overloding to compare two users `uuid` lexicographically.

```cpp
bool operator<(const string& uuid);
bool operator>(const string& uuid);
bool operator==(const string& uuid);
bool operator!=(const string& uuid);
```
Comparison operators overloding to compare current users `uuid` with another `uuid` operand lexicographically. (Used in Binary Search implementation)

## `Status` Enumeration
Status of user (Driver, Customer). An user can either be idle, or on a shift. An user on shift is not allowed to book a taxi.

```cpp
enum Status{
    ONSHIFT,
    IDLE
};
```


# Customer 
```cpp
Customer();
```
Customer Default Constructor: Instantiates a brand new Customer object; no arguments required.

```cpp
Customer(string firstname, string lastname, string uuid, int balance, Status status);
```
Instantiates a Customer Object, requires following details:
 1. `firstname: string`
 2. `lastname: string`
 3. `uuid: string` - primary key
 4. `balance: int` - account balance
 5. `status: Status (IDLE | ONSHIFT)` - whether or not the customer is on a shift

```cpp
friend ostream& operator<<(ostream& output, const Customer& C);
```
Insertion operator overloading to print Customers' details in the standard output.

```cpp
void print();
```
Prints all the Customers` details.

```cpp
Status getStatus();
```
Getter function to get the current `Status` of the current customer.

```cpp
int getBalance();
```
Getter function to get the current `Balance` of the current customer.

```cpp
void toggle_customer_status();
```
To change the status of customer from `ONSHIFT` to `IDLE` and vice versa.

```cpp
void makeTransaction(int amount);
```
Makes payment on behalf of the customer. The amount passed in as an argument is deducted from the customer's current balance.

```cpp
void transferCashToBalance(int amount);
```
Adds amount to the customer's balance.


# Driver

```cpp
Driver();
```
Driver Default Constructor: Instantiates a brand new Driver object; no arguments required.

```cpp
Driver(string firstname, string lastname, string uuid, string dln, Status status = IDLE);
```
Instantiates a Driver Object, requires following details:
 1. `firstname: string`
 2. `lastname: string`
 3. `uuid: string` - primary key
 4. `dln: string` - drvier license number issued by the government
 5. `status: Status (IDLE | ONSHIFT)` - whether or not the driver is on a shift

```cpp
friend ostream& operator<<(ostream& output, const Driver& D);
```
Insertion operator overloading to print Drivers' details in the standard output.

```cpp
void print();
```
Prints all the Drivers` details.

```cpp
string getDLN();
```
Getter function to get the drvier license number (issued by the government) of the current driver.

```cpp
Status getStatus();
```
Getter function to get the current `Status` of the current driver.

```cpp
void toggle_driver_status();
```
To change the status of customer from `ONSHIFT` to `IDLE` and vice versa.
