#include "main.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // checks that the correct number of command line arguments are provided when ran
    if(argc < 3 || argc > 3) {
        cerr << "Please specify valid input in command line arguments: {program} {init_file} {input_file}" << endl;
        return 1;
    }

    ifstream init_file(argv[1]);

    if (!init_file.is_open()) {
        cerr << "Could not open initialization file \"" << argv[1] << "\"" << endl;
        return 1;
    }

    ifstream input_file(argv[2]);

    if (!input_file.is_open()) {
        cerr << "Could not open input file \"" << argv[2] << "\"" << endl;
        return 1;
    }

    return 0;
}