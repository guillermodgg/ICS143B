#include <iostream>
#include "list.cpp"


using namespace std;

int n;

/*

PCB Data Structure, which is implemented in my program 
as a fixed array of "Process" objects, where each of these 
Prcoess objects contains the process's state, parent index, 
list of children, and list of resources.

*/

class Process{
public:
    int state; // 1 = ready, 0 = blocked, -1 = free space
    int parent; // index of running process when this process is created, parent < 0 = no parent
    Node* children;
    Node* resources;
};

void create();

/*
destroy(j)
for all k in children of j destroy(k)
remove j from parent's list
remove j from RL or waiting list
release all resources of j
free PCB of j
display: “n processes destroyed”
*/