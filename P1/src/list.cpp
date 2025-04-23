#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Linked List class
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    // Append a new node at the end
    void append(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    // Destructor to free memory
    ~LinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};