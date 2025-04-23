#include <iostream>
#include "list.cpp"


using namespace std;

/*

PCB Data Structure, which is implemented in my program 
as a fixed array of "PCB" objects, where each of these 
PCB objects contains the process's state, parent index, 
list of children, and list of resources.

*/

class PCB{
    int state;
    int parent;
    Node* children;
    Node* resources;
};

/*
create()
allocate new PCB[j]
state = ready
insert j into children of i
parent = i
children = NULL
resources = NULL
insert j into RL
display: “process j created”
*/

/*
destroy(j)
for all k in children of j destroy(k)
remove j from parent's list
remove j from RL or waiting list
release all resources of j
free PCB of j
display: “n processes destroyed”
*/