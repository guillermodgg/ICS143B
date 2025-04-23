#include "main.hpp"
/*
Ready list: linked list data structure that links 
nodes storing the indexes of each PCB object in 
the "ready" state.
*/
LinkedList* ready_list = new LinkedList();

Process* PCB[];


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
            PCB[i]->children = nullptr;
            PCB[i]->resources = nullptr;

            ready_list->append(i);

            cout << "process " << i << " created" << endl;
            return;
        }
    }
}