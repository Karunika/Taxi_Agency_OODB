CC = g++

output: main.cpp ./src/User.cpp ./src/Customer.cpp ./src/TaxiAgency.cpp
	g++ main.cpp ./src/User.cpp ./src/Customer.cpp ./src/TaxiAgency.cpp -o output -std=c++11

clean:
	rm *.o output