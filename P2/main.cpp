#include "main.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

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

    //set whatever is in the memory to 0 so that everything is freed in our program
    for (int i = 0; i < pm_size; ++i) {
        PM[i] = 0;
    }

    //read each triplet and assign its respective values to the ST
    while (iss >> s >> z >> f) {
        // set segment size
        PM[2 * stoi(s)] = stoi(z);
        // set frame/block number (positive or negative) for pt of segment
        PM[2 * stoi(s) + 1] = stoi(f);
    }

    // pass through second line of init file
    getline(init_file, line);

    istringstream iss2(line);
    string s, p, f;

    while (iss2 >> s >> p >> f) {
        int pt_frame = PM[2 * stoi(s) + 1];

        // if the page table for this segment is resident: fill the PT in PM with corresponding frame for that page
        if (pt_frame > 0) {
            // set the frame/block number for corresponding page (positive or negative)
            PM[pt_frame * 512 + stoi(p)] = stoi(f);
        } else if (pt_frame < 0){
            // if negative, add page table to corresponding block on paging disk (absolute value of -b)
            // set the frame/block number for corresponding page (positive or negative)
            D[abs(pt_frame)][stoi(p)] = stoi(f);
        } else {
            //pt_frame is 0 so error somewhere
            cout << "Error: frame can't be 0: thats where ST resides. check your code!" << endl;
            return 1;
        }
    }

    return 0;
}