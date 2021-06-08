CC = g++

output: main.cpp ./src/User.cpp ./src/Driver.cpp ./src/Customer.cpp ./src/Shift.cpp ./src/TaxiAgency.cpp
	g++ main.cpp ./src/User.cpp ./src/Driver.cpp ./src/Customer.cpp ./src/Shift.cpp ./src/TaxiAgency.cpp -o output -std=c++11

reset: reset.cpp
	g++ reset.cpp -o reset

clean:
	rm *.o output reset