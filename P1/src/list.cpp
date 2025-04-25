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
        Node* newNode = new Node{val, nullptr};

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

    void remove_from_head() {
        if (head == nullptr) {
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    Node* find(int val) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == val) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;  // Not found
    }

    void remove(int val) {
        if (head == nullptr) {
            return;
        }

        // If head needs to be removed
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Search for the node to remove
        Node* prev = head;
        Node* curr = head->next;

        while (curr != nullptr) {
            if (curr->data == val) {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    bool is_empty() {
        return (head == nullptr);
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