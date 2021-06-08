# Taxi Agency

 * [Introduction](#Introduction)
 * [Usage](#Introduction)
 * [About](#About)
   * [Class Design](#Class-Design)
   * [Testing](#Testing)
   * [Features & Examples](#features-examples)
 * [Dependencies](#Dependencies)


## Introduction
The motive of the project is to create an Object-oriented Database Model for a Taxi Agency. Each type of object in the problem space has been mapped to a certain class in the Object Oriented Solution Space. It's sort of an API wrapper which allows a programmer to create, read, update and erase (CRUD) object data using the interface provided by Taxi Agency class during the execution of the program. In simple terms, this app essentially allows a backend programmer to mimick an UI programmatically, rather than having a concrete graphical or text based UI.

## Usage
Run the following commands in the app root directory.

```cpp
make // compile tests
./output // run tests
```

```cpp
make reset // compile reset file
./output // run reset
```

```cpp
make clean // clean
```


## About
Yet to be done.
<!-- 
Service:
When customer books a taxi:
 * When taxi is still, the customer is charged per time the driver is waiting,
 * When taxi is moving, the customer is charged per km  -->


<img src="./assets/UML.png">

[Project Config](config.yaml)

## Class Design

Custom Classes:
 * [Taxi Agency](#taxi-agency)
 * [User](#user)
   * [Customer](#customer)
   * [Driver](#driver)
 * [Taxi](#taxi)
 * [Shift](#shift)

Standard Template Library Classes used:
 * [vector<T>](#vector)
 * [list<T>](#vector)
 * [unordered_map<T1, T2>](#vector)

<!-- ### Taxi Agency
An instance of Taxi Agency class behaves like a container to the list of all the entities (Driver, Customer, Taxi, Shift (ongoing, history)). It also stores basic stats like limits of the Agency (based on budget, which can be upgraded upon investment), employee vacancies, ongoing shifts, etc. It also maintains a record of the history of shifts.

Destruction of a Taxi Agency instance leads to the destruction of all the containers contained in it, thus, all the instances of the User, Customer, Taxi and Shift classes.

Note:
Taxi Agency stores a record of only its customer, employee and driver. Deleting their instance does not infer at deleting their existance.

### User
User reflects an ideal. Uses the concept of unique `uuid`s, allowing and efficient retrieval of data.

 * Customer
 * Driver -->

## Testing
The test relies on an initial static CSV data, which has been provided in the relative path `./data/sample`. However, the test only alters the CSV files present in `./data`. <br />
It is essential to reset the data back to the initial point in order for the tests to run successfully. <br />
`./config.hpp` contains the relative paths to all the CSV files.

## Dependencies
Dependencies for interactive console testings <br />
[agauniyal/rang](https://github.com/agauniyal/rang/blob/master/include/rang.hpp)

Sample Data Courtesy: [Taxi Data](https://corgis-edu.github.io/corgis/csv/cars/)
