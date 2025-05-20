#include "main.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    // checks that the correct number of command line arguments are provided when ran
    if(argc < 3 || argc > 3) {
        cerr << "Please specify valid input in command line arguments: {program} {init_file} {input_file}" << endl;
        return 1;
    }

    // open the initialization file
    ifstream init_file(argv[1]);

    // check if the file was opened correctly
    if (!init_file.is_open()) {
        cerr << "Could not open initialization file \"" << argv[1] << "\"" << endl;
        return 1;
    }

    // open the input file
    ifstream input_file(argv[2]);

    // check if the file was opened correctly
    if (!input_file.is_open()) {
        cerr << "Could not open input file \"" << argv[2] << "\"" << endl;
        return 1;
    }

    // initialize PM

    string line;

    // pass through the first line of init file
    getline(init_file, line);
    istringstream iss(line);
    string s, z, f;

    //read each triplet and assign its respective values to the ST
    while (iss >> s >> z >> f) {
        // set segment size
        PM[2 * stoi(s)] = stoi(z);
        // set frame number (positive or negative)
        PM[2 * stoi(s) + 1] = stoi(f);
    }

    return 0;
}