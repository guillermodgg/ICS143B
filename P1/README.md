Guillermo Garcia Gutierrez
Student ID: 10918627
UCInetID: guilledg

My program is written in C++ 23, so a C++ compiler is required to run it. I personally used g++ to compile my code. My code source, input, output, and executable files are all in src. The default executable I provided is a.out, but a new executable can be compiled through "main.cpp" ("g++ src/main.cpp" for g++).

Input for my program is provided from the command line as default, but an input file can be specified through the bash command line in the format "{executable (ususally "src/a.out")} < {input file i.e. "src/input.txt"}". My program outputs user-readable messages and errors to the terminal, and writes integer outputs to the output file "output.txt". The program does not end on its own, unless an input file is provided and end of file is reached, or unless the process is terminated from the command line.

Notes on implementation:
My ready list is implemented as one singly-linked list, different than specified, but the three tiers of priority are still functional and implemented through appending. For instance, the append fucntion will traverse through the list until the end of the desired priority is reached and the process will be added to the end of its section, simulating three seperate lists.
Other than that, my implementation should closely follow the way the specification demonstrates.