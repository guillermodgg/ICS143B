#include "main.hpp"
#include <string>
#include <sstream>

/*
Ready list: linked list data structure that links 
nodes storing the indexes of each PCB object in 
the "ready" state.
*/

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
void create() {
    for (int i = 0; i < n; i++) {
        // if state is neither 1 or 0, the space is free, initialize space
        if (PCB[i].state < 0) {
            //set its state to ready
            PCB[i].state = 1;
            //if ready_list is empty, process 0 is being created
            if (ready_list->head == nullptr) {
                PCB[i].parent = -1; // no parent
            // else, the current running process is the parent (implicitly defined as the head of ready_list)
            } else {
                PCB[i].parent = ready_list->head->data;
            }
            PCB[i].children = new LinkedList();
            PCB[i].resources = new LinkedList();
            //add i to ready_list
            ready_list->append(i);

            cout << "process " << i << " created" << endl;
            return;
        }
    }
    //error for max amount of processes
    cout << "Error: max amount of processes created" << endl;
}

/*
destroy(j)
for all k in children of j destroy(k)
remove j from parent's list
remove j from RL or waiting list
release all resources of j
free PCB of j
display: “n processes destroyed”
*/

void destroy(int j) {
    //error if j is not an existing process
    if (j < 0 || j >= n) {
        cout << "Error: process " << j << " not an existing process." << endl;
        return;
    }

    //check to see if j is the same process as i
    if (j == ready_list->head->data) {
        //abstracted away freeing process so that a total sum of processes freed can be accumulated
        int destroyed = free_process(j);
    
        cout << destroyed << " processes destroyed" << endl;

        return;
    }
    
    //if not, check to see if j is a child of i
    for (Node* p = PCB[ready_list->head->data].children->head; p != nullptr; p = p->next) {
        if (p->data == j) {
            int destroyed = free_process(j);
    
            cout << destroyed << " processes destroyed" << endl;

            return;
        }
    }
    //if j is not a child of i: error
    cout << "Error: process " << j << " is not a child of process of " << ready_list->head->data << ". Cannot destroy process " << j << "." << endl;
}

int free_process(int j) {
    int process_count = 1;

    //recursively call function on j's children.
    while (PCB[j].children->head != nullptr) {
        Node* temp = PCB[j].children->head;
        PCB[j].children->remove_from_head();
        process_count += free_process(temp->data);
    }

    //free the empty children list
    delete  PCB[j].children;

    //remove j from parent's list
    int p = PCB[j].parent;
    PCB[p].children->remove(j);

    //remove j from ready list
    ready_list->remove(j);

    //go through each resource and remove from waiitng lists if present.
    for (int i = 0; i < m; ++i) {
        RCB[i].waitlist->remove(j);
    }

    //release each resource
    for (Node* p = PCB[j].resources->head; p != nullptr; p = p->next) {
        release(p->data);
    }

    //free the resource list
    delete PCB[j].resources;

    //free the PCB
    PCB[j].state = -1;

    return process_count;
}

/*
request(r)
if state of r is free
state of r = allocated
insert r into list of resources of process i
display: “resource r allocated”
else
state of i = blocked
move i from RL to waitlist of r
display: “process i blocked”
scheduler()
*/
void request(int r) {
    //error if r is not an existing resource
    if (r < 0 || r >= m) {
        cout << "Error: " << r << " is not an existing resource." << endl;
        return;
    }

    //error if process 0 requests a resource
    if (ready_list->head->data == 0) {
        cout << "Error: Process 0 cannot request resources" << endl;
        return;
    }

    //error if i already holds r
    for (Node* p = PCB[ready_list->head->data].resources->head; p != nullptr; p = p->next) {
        if (p->data == r) {
            cout << "Error: Process " << ready_list->head->data << " already holds resource " << r << "." << endl;
            return;
        }
    }

    //if r is free
    if (RCB[r].state == 0) {
        //set state to allocated
        RCB[r].state = 1;
        //insert r into i(current running process)'s resource list
        PCB[ready_list->head->data].resources->append(r);
        cout << "resource " << r << " allocated" << endl;
    } else {
        //state of current running process is now blocked
        PCB[ready_list->head->data].state = 0;
        //keep track of i so we can remove it safely from reeady list
        int i = ready_list->head->data;
        //remove i from ready list
        ready_list->remove_from_head();
        //i is now added to the waitlist of r
        RCB[r].waitlist->append(i);

        cout << "process " << i << " blocked" << endl;

        scheduler();

    }

}

/*
release(r)
remove r from resources list of process i
if waitlist of r is empty
state of r = free
else
move process j from the head of waitlist of r to RL
state of j = ready
insert r into resources list of process j
display: “resource r released”
*/
void release(int r) {
    //error if r is not an existing resource
    if (r < 0 || r >= m) {
        cout << "Error: " << r << " is not an existing resource." << endl;
        return;
    }

    //error if i is not holding r
    if(PCB[ready_list->head->data].resources->find(r) == nullptr) {
        cout << "Error: process " << ready_list->head->data << " is not holding resource " << r << "." << endl;
        return;
    }

    //remove r from resource list of i
    PCB[ready_list->head->data].resources->remove(r);
    //if r's waitlist is empty, free the resource
    if (RCB[r].waitlist->is_empty()) {
        RCB[r].state = 0;
    } else {
        //keep track of j
        int j = RCB[r].waitlist->head->data;
        //remove j from waitlist of r
        RCB[r].waitlist->remove_from_head();
        //add j to ready list
        ready_list->append(j);
        //set state of j to ready
        PCB[j].state = 1;
        //insert r into resources list of j
        PCB[j].resources->append(r);
    }
    cout << "resource " << r << " released" << endl;
}

void timeout() {
    //keep track of i
    int i = ready_list->head->data;
    //remove i from head of ready list
    ready_list->remove_from_head();
    //add i back to the end of ready list
    ready_list->append(i);

    scheduler();
}

void scheduler() {
    cout << "process " << ready_list->head->data << " running" << endl;
}

/*
Init() function must be implemented, which initializes all data structures:
All PCB entries are initialized to free except PCB[0].
PCB[0] is initialized to be a running process with no parent, no children, and no resources.
All RCB entries are initialized to free.
RL contains process 0

The init function should always perform the following tasks:
• Erase all previous contents of the data structures PCB, RCB, RL
• Create a single running process at PCB[0] with priority 0
• Enter the process into the RL at the lowest-priority level 0
*/
void init() {
    //clear ready list;
    delete ready_list;

    ready_list = new LinkedList();

    //set all process states to free & free any memory that may have been allocated
    for (int i = 0; i < n; ++i) {
        PCB[i].state = -1;
        delete PCB[i].children;
        delete PCB[i].resources;
    }
    //make PCB[0] (create() handles the case where PCB[0] is made and sets parent to -1)
    create();
    //set all resource states to free & delete existing waitlist & allocate space for their new waitlists;
    for (int i = 0; i < m; ++i) {
        RCB[i].state = 0;
        delete RCB[i].waitlist;
        RCB[i].waitlist = new LinkedList();
    }


}

bool is_number(string param) {
    try {
        size_t pos;
        stoi(param, &pos);
        return pos == param.size();
    } catch (...) {
        return false;
    }
}

int main() {
    //max processes = 16
    n = 16;
    //max resources = 4
    m = 4;
    //create the ready list
    ready_list = new LinkedList();
    //initialize PCB array
    PCB = new Process[n];
    //initialize RCB array
    RCB = new Resource[m];
    //ensure data structures are ready and process 0 is created
    init();

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string command, param;

        iss >> command >> param;

        if (command == "cr") {
            create();
        } else if (command == "de") {
            if (param.empty() || !is_number(param)) {
                cout << "Error: please specify a valid process to delete" << endl;
                continue;
            }
            destroy(stoi(param));
        } else if (command == "rq") {
            if (param.empty() || !is_number(param)) {
                cout << "Error: please specify a valid resource to request" << endl;
                continue;
            }
            request(stoi(param));
        } else if (command == "rl") {
            if (param.empty() || !is_number(param)) {
                cout << "Error: please specify a valid resource to release" << endl;
                continue;
            }
            release(stoi(param));
        } else if (command == "to") {
            timeout();
        } else if (command == "in") {
            init();
        }
    }


    return 0;
}