# Taxi Agency

 * [Introduction](#Introduction)
 * [About](#About)
 * [Class Design](#Class-Design)
 * [Features & Examples](#features-examples)
 * [Dependencies](#Dependencies)


## Introduction
The motive of the project is to create an Object-oriented Database Model for a Taxi Agency.

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

Standard Classes:
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


## Dependencies
Dependencies for interactive console testings
[agauniyal/rang](https://github.com/agauniyal/rang/blob/master/include/rang.hpp)

Sample Data Courtesy: [Taxi Data](https://corgis-edu.github.io/corgis/csv/cars/)
