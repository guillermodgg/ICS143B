#include "main.hpp"
/*
Ready list: linked list data structure that links 
nodes storing the indexes of each PCB object in 
the "ready" state.
*/
LinkedList* ready_list = new LinkedList();

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
        if (PCB[i]->state < 0) {
            //set its state to ready
            PCB[i]->state = 1;
            //if ready_list is empty, process 0 is being created
            if (ready_list->head == nullptr) {
                PCB[i]->parent = -1; // no parent
            // else, the current running process is the parent (implicitly defined as the head of ready_list)
            } else {
                PCB[i]->parent = ready_list->head->data;
            }
            PCB[i]->children = new LinkedList();
            PCB[i]->resources = new LinkedList();
            //add i to ready_list
            ready_list->append(i);

            cout << "process " << i << " created" << endl;
            return;
        }
    }
}

/*
destroy(j)
for all k in children of j destroy(k)
remove j from parent's list3
remove j from RL or waiting list
release all resources of j
free PCB of j
display: “n processes destroyed”
*/

void destroy(int j) {
    //abstracted away freeing process so that a total sum of processes freed could be accumulated
    int destroyed = free_process(j);
    
    cout << destroyed << " processes destroyed" << endl;
}

int free_process(int j) {
    int process_count = 1;

    //recursively call function on j's children.
    while (PCB[j]->children->head != nullptr) {
        Node* temp = PCB[j]->children->head;
        PCB[j]->children->remove_from_head();
        process_count += free_process(temp->data);
    }

    //free the empty children list
    delete  PCB[j]->children;

    //remove j from parent's list
    int p = PCB[j]->parent;
    PCB[p]->children->remove(j);

    //remove j from ready list
    ready_list->remove(j);

    //go through each resource and remove from waiitng lists if present.
    for (int i = 0; i < r; ++i) {
        RCB[i]->waitlist->remove(j);
    }

    //release each resource
    for (Node* p = PCB[j]->resources->head; p != nullptr; p = p->next) {
        release(p->data);
    }

    //free the resource list
    delete PCB[j]->resources;

    //free the PCB
    PCB[j]->state = -1;

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
    //if r is free
    if (RCB[r]->state == 0) {
        //set state to allocated
        RCB[r]->state = 1;
        //insert r into i(current running process)'s resource list
        PCB[ready_list->head->data]->resources->append(r);
        cout << "resource " << r << " allocated" << endl;
    } else {
        //state of current running process is now blocked
        PCB[ready_list->head->data]->state = 0;
        //keep track of i so we can remove it safely from reeady list
        int i = ready_list->head->data;
        //remove i from ready list
        ready_list->remove_from_head();
        //i is now added to the waitlist of r
        RCB[r]->waitlist->append(i);

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
    //remove r from resource list of i
    PCB[ready_list->head->data]->resources->remove(r);
    //if r's waitlist is empty, free the resource
    if (RCB[r]->waitlist->is_empty()) {
        RCB[r]->state = 0;
    } else {
        //keep track of j
        int j = RCB[r]->waitlist->head->data;
        //remove j from waitlist of r
        RCB[r]->waitlist->remove_from_head();
        //add j to ready list
        ready_list->append(j);
        //set state of j to ready
        PCB[j]->state = 1;
        //insert r into resources list of j
        PCB[j]->resources->append(r);
    }
    cout << "resource " << r << " released" << endl;
}

void scheduler() {
    cout << "process " << ready_list->head->data << " running" << endl;
}

int main() {
    return 0;
}