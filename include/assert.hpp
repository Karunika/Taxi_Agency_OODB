#include <iostream>
#include <exception>
#include <functional>

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

void test_partition(string test_description, const function<void()>& tests){
    cout << "-- " << test_description;
    cout << rang::fg::blue << " - successful" << rang::fg::reset << endl;
    tests();
};

void print_prompt(string prompt, const function<void()>& callback){
    char boolean = 'N';
    cout << prompt << " [Y/N] (Default N) : ";
    cin >> boolean;
    if(boolean == 'Y' || boolean == 'y'){
        callback();
    }
};