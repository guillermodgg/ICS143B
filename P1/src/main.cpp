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
    //recursively call function on j's children.
    while (PCB[j]->children->head != nullptr) {
        Node* temp = PCB[j]->children->head;
        PCB[j]->children->remove_from_head();
        destroy(temp->data);
    }
    //free the empty children list
    delete  PCB[j]->children;

    //remove j from parent's list
    int p = PCB[j]->parent;
    PCB[p]->children->remove(j);

    //remove j from ready list
    ready_list->remove(j);

    //TODO: implement RCB and waiting list & release each resource and remove j from each waiting list

    //go through each resource and remove from waiitng lists if present.
    for (int i = 0; i < r; ++i) {
        //if resource space is in use
        if (RCB[i]->state >= 0) {
            RCB[i]->waitlist->remove(j);
        }
    }

    //release each resource
    for (Node* p = PCB[j]->resources->head; p != nullptr; p = p->next) {
        release(p->data);
    }

    //free the resource list
    delete PCB[j]->resources;

    //free the PCB
    PCB[j]->state = -1;




}

void scheduler() {
    cout << "process " << ready_list->head->data << " running" << endl;
}

int main() {
    return 0;
}