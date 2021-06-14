# Design & Analysis

## Introduction
The motive of the project is to create an Object-oriented Database Model for a Taxi Agency. Each type of object in the problem space has been mapped to a certain class in the Object Oriented Solution Space. It's sort of an API wrapper which allows a programmer to create, read, update and erase (CRUD) object data using the interface provided by Taxi Agency class during the execution of the program. In simple terms, this app essentially allows a backend programmer to mimick an UI programmatically, rather than having a concrete graphical or text based UI.

The data is stored in `CSV` file format. Upon the commencement of the program, the pre-existing `CSV` data is fetched, parsed and stored in dynamic arrays or list. During the execution of program, this data can be manipulated in accordance to the request made and eventaully exported back to `CSV`. The exported `CSV` can be used in the next round of program execution.

## Taxi Booking Design
Each Shift is instantiated upon the request of a customer with their preferential Taxi. This is called __Taxi Booking__. A Taxi Booking can fail under the following circumstances:
 * The User is not registered with the Taxi Agency
 * The User fails to ensure that it has a minimum Account Balance of being able to pay 12 hours of driver waiting charges and 12 hours of taxi ride ([more info on how the total cost is evaluated](#Total_Cost))
 * The car id provided by user is either invalid or unavailable
 * The User is already on a shift
 * The Agency has ran out of drivers

Once a Shift is instantiated with a minimum tenure of 12 waiting hours and 12 riding hours, the tenure of the Shift can be renewed by the customer as long as the Shift is open. The customer has to make its payment in arrear.

## Total Cost
The expense of a shift/ride is evaluated on the following basis:
 * If the taxi is moving, the customer is charged based on the fare amount (per kilometer) of a particular kind of taxi
 * If the taxi is at a stop, the customer is charged based on the waiting time of the driver

## User Constraints
Each User is recognised by a unique key called __`uuid`__. An uuid is recognised as a valid uuid if it meets the following requirements:
 * It should contain only alphanumeric characters or an underscore (`_`)
 * It should be atmost 32 characters long
 * It should be atleast 3 characters long

## `vector<User>` Features
The `vector<Driver>` and `vector<Customer>` are always sorted in lexicographical (with a slight variation) ascending order by `uuid`.
This open oppurtunitites to implement `O(log(n))` efficient binary search algorithm on them.

## `IndexInstance<T>` struct
The concept of template struct `IndexInstance<T>` is introduced to increase the efficiency of the program by avoiding looping over the arrays contained in the Taxi Agency class over and over again.

`IndexInstance<T>` interface:
```cpp
template <typename T>
struct IndexInstance{
    int index;
    T* data;
};
```

## Member Function Description
Checkout <br />
[Taxi Agency](./Taxi_Agency.md) <br />
[User | Customer | Driver](./User.md) <br />
[Shift](./Shift.md)
