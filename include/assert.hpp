// Custom Assertion librarby containing funcitons for assertion failure exception handling in tests
#include <iostream>
#include <exception>

using namespace std;


struct assertion_failure : public exception {
    const char* msg;
    assertion_failure(const char* msg) : msg(msg){
    };
    const char * what () const throw () {
        return msg;
    };
};

template <class T>
void assert_eq(T val, T assumed_val, string keyword){
    if(val != assumed_val){
        string str = "Test Failed: Assertion \"" + keyword + "\" failure";
        const char* c = str.c_str();
        throw assertion_failure(c);
    }
};
