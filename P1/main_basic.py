#Start of Project 1
from list import *
from process import Process

ready_list = LinkedList()

"""

PCB Data Structure, which is implemented in my program
as a standard python list of "Process" objects, where each of these
process objects contains the process's state, parent index, 
list of children, and list of resources.

"""
PCB = []

def create(i : int):
    """
    TODO: 
    1. Allocate new PCB
    2. set its state to ready.
    3. insert it into its parent's children list
    4. set its parent
    5. intitialize its children list
    6. initialize its resources list
    7. Insert into ready list
    8. display "Process j Created"
    """