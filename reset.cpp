#include <iostream>
#include <fstream>

#include "./config.hpp"

using namespace std;

int main(){
    string line;
    ifstream File_r;
    ofstream File_w;

    // reset files data
    File_r.open(SAMPLE_TAXIES_FILE);
    File_w.open(TAXIES_FILE);
    if(File_r.is_open() && File_w.is_open()){
        while(getline(File_r, line)){
            File_w << line << endl;
        }
    }else{
        throw runtime_error("File couldn't be resolved");
    }
    File_r.close();
    File_w.close();

    File_r.open(SAMPLE_CUSTOMERS_FILE);
    File_w.open(CUSTOMERS_FILE);
    // string line;
    if(File_r.is_open() && File_w.is_open()){
        while(getline(File_r, line)){
            File_w << line << endl;
        }
    }else{
        throw runtime_error("File couldn't be resolved");
    }
    File_r.close();
    File_w.close();

    File_r.open(SAMPLE_DRIVERS_FILE);
    File_w.open(DRIVERS_FILE);
    // string line;
    if(File_r.is_open() && File_w.is_open()){
        while(getline(File_r, line)){
            File_w << line << endl;
        }
    }else{
        throw runtime_error("File couldn't be resolved");
    }
    File_r.close();
    File_w.close();

    return 0;
}