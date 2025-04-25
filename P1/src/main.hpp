#include <iostream>
#include "list.cpp"


using namespace std;

//fixed size of PCB data structure
int n;

//fixed size of RCB data structure
int m;

/*
Ready List, implemented as a singly linked list,
with its three priority tiers accounted for when appending to the list.
*/


class Ready_list {
public:
    LinkedList* three_tier = nullptr;

    Node* head = nullptr;

    Ready_list();

    void append(int val);

    void remove(int j);

    void remove_from_head();

};

Ready_list* ready_list = nullptr;

class Process{
public:
    int state; // 1 = ready, 0 = blocked, -1 = free space
    int parent; // index of running process when this process is created, parent < 0 = no parent
    int priority; // 0, 1, 2 levels of priority
    LinkedList* children = nullptr;
    PairList* resources = nullptr;
};

class Resource{
public:
    int state; // counter to keep track of units available
    int inventory; // # of total units possible
    PairList* waitlist = nullptr;
};

/*
PCB Data Structure, which is implemented in my program 
as a fixed array of "Process" objects, where each of these 
Process objects contains the process's state, parent index, 
list of children, and list of resources.
*/
Process* PCB;

/*
RCB Data Structure, which is implemented in my program 
as a fixed array of "Resource" objects, where each of these 
Resource objects contains the resource's state and waitlist.
*/
Resource* RCB;

class PairList {
public:

    LinkedList* processes;

    int requested[16];

    Node* head;

    PairList();

    void append(int val, int units);

    void remove(int j);

    void remove_from_head();

    bool is_empty();
};

void create(int p);

void destroy(int j);

int free_process(int j);

void request(int r, int k);

void release(int r, int k);

void timeout();

void scheduler();

void init();

bool is_number(string param);