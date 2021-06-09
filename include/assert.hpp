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
void assert_eq(T val, T assumed_val, const char* keyword = ""){
    if(val != assumed_val){
        throw assertion_failure(keyword);
    }
};

void test_partition(string test_description, const function<void()>& tests){
    cout << "-- " << test_description << endl;
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