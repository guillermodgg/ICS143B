#include "main.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int translate(int VA) {
    int s, p, w, pw;

    //extract each component from the virtual address
    s = VA >> 18;
    w = VA & 0x1FF;
    p = (VA >> 9) & 0x1FF;
    pw = VA & 0x3FFFF;

    // if PW exceeds size of segment: invalid address
    if (pw >= PM[2*s]) {
        return -1;
    }

    // if PT is not resident:
    if (PM[2*s + 1] < 0) {
       // allocate free frame f1 using list of free frames
       int free_frame = free_frames.head->data;
       // update list of free frames
       free_frames.remove_from_head();
       // read disk block b = |PM[2s + 1]| into PM staring at location f1*512: read_block(b, f1*512)
       int b = abs(PM[2*s + 1]);
       read_block(b, free_frame * 512);
       // update ST entry
       PM[2*s + 1] = free_frame;
    }
    // if page p is not resident:
    if (PM[PM[2*s + 1]*512 + p] < 0) {
        // allocate free frame f2 using list of free frames
        int free_frame = free_frames.head->data;
        // update list of free frames
        free_frames.remove_from_head();
        // read disk block b = |PM[PM[2s + 1]*512 + p]| into PM staring at location f2*512: read_block(b, f2*512)
        int b = abs(PM[PM[2*s + 1]*512 + p]);
        read_block(b, free_frame * 512);
        // update PT entry
        PM[PM[2*s + 1]*512 + p] = free_frame;
    }

    return PM[PM[2*s + 1]*512 + p]*512 + w;


}

void read_block(int b, int m) {
    //copy everythign in block b to PM starting at address m
    for (int i = 0; i < 512; ++i) {
        PM[m + i] = D[b][i];
    }
}

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

    //create linked list of free frames

    for (int i = 1023; i > 1; --i) {
        free_frames.add(i);
    }

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

        if (stoi(f) > 0) {
                free_frames.remove(stoi(f));
        }
    }

    // pass through second line of init file
    getline(init_file, line);

    istringstream iss2(line);
    string p;

    while (iss2 >> s >> p >> f) {
        int pt_frame = PM[2 * stoi(s) + 1];
        int f_val = stoi(f);

        // if the page table for this segment is resident: fill the PT in PM with corresponding frame for that page
        if (pt_frame > 0) {
            // set the frame/block number for corresponding page (positive or negative)
            PM[pt_frame * 512 + stoi(p)] = f_val;
        } else if (pt_frame < 0){
            // if negative, add page table to corresponding block on paging disk (absolute value of -b)
            // set the frame/block number for corresponding page (positive or negative)
            D[abs(pt_frame)][stoi(p)] = f_val;
        } else {
            //pt_frame is 0 so error somewhere
            cout << "Error: frame can't be 0: thats where ST resides. check your code!" << endl;
            return 1;
        }
        // is a frame was allocated from PM, remove from free_frames list
        if (f_val > 0) {
                free_frames.remove(f_val);
        }
    }

    ofstream outf("output.txt");

    // extract the addresses from input file and translate
    while (input_file >> line) {
        int pa = translate(stoi(line));
        outf << pa << " ";
    }

    return 0;
}