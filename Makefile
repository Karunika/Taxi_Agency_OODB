CC = g++

output: main.cpp ./src/User.cpp ./src/Driver.cpp ./src/Customer.cpp ./src/Shift.cpp ./src/TaxiAgency.cpp
	g++ main.cpp ./src/User.cpp ./src/Driver.cpp ./src/Customer.cpp ./src/Shift.cpp ./src/TaxiAgency.cpp -o output -std=c++11

clean:
	rm *.o output