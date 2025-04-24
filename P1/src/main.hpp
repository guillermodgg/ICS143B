#include <iostream>
#include "list.cpp"


using namespace std;

//fixed size of PCB data structure
int n;

//fixed size of RCB data structure
int r;

class Process{
public:
    int state; // 1 = ready, 0 = blocked, -1 = free space
    int parent; // index of running process when this process is created, parent < 0 = no parent
    LinkedList* children;
    LinkedList* resources;
};

class Resource{
public:
    int state; // 0 = free, 1 = allocated
    LinkedList* waitlist;
};

/*
PCB Data Structure, which is implemented in my program 
as a fixed array of "Process" objects, where each of these 
Prcoess objects contains the process's state, parent index, 
list of children, and list of resources.
*/
Process* PCB[];

/*
RCB Data Structure, which is implemented in my program 
as a fixed array of "Resource" objects, where each of these 
Resource objects contains the resource's state and waitlist.
*/
Resource* RCB[];

void create();

void destroy(int j);

int free_process(int j);

void request(int r);

void release(int r);

void timeout();

void scheduler();

void init();