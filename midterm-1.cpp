// COMSC-210 | Midterm #1 | Annie Morales
// IDE used: Visual Studio Code

#include <iostream> 
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //These are the constants that determine the min and max

class DoublyLinkedList { // A class named DoublyLinkedList, holding private and public members and functions that make up the linked list.
private:
    struct Node { // A declared structure named node, containing private data members.
        int data; // This integer is named data
        Node* prev; // This pointer points to the previous node in this linked list.
        Node* next; // This pointer points to the next node in this linked list.
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // This node takes a full parameter constructer as an argument
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // This points to the head node of the doubly linked list.
    Node* tail; // This points to the tail node of the doubly linked list.

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // This is the linked list, with the parameter as 
                                                            // the initialized values of head and tail which point to nullptr.

    void insert_after(int value, int position) { // This inserts a node at the head, tail, or any valid position in the linked list.
        if (position < 0) { // This if statement puts out an error if the user input is less than zero.
            cout << "Position must be >= 0." << endl; 
            return;
        }

        Node* newNode = new Node(value);
        if (!head) { // If there's no head, the list is empty.
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) { // A value isnt found, therefore we must've reached past the end of the linked list.
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // This deletes the node after the error.
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) { // This function deletes a value from the doubly linked list.
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) { // This function deletes a number by its position in the linked list.
        if (!head) { // If there's no head, the list must be empty.
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { // If the position is 1
            pop_front(); // This removes the first element.
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){ // Goes through the linked list to check if the position is valid.
            if (!temp) { // If position isn't valid and are past bounds, it doesn't exist.
                cout << "Position doesn't exist." << endl;
                return;
            }
            else // If the position is valid, we move onto the next element in the list.
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { // If we can't move to the next element
            pop_back(); // This removes the last element in the list.
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp; // Deletes the nodes
    }

    void push_back(int v) { // This function inserts an element at the end of the linked list.
        Node* newNode = new Node(v); // A new node pointer, equal to a new node with v as a parameter.
        if (!tail) // If there's no tail, the list is empty.
            head = tail = newNode;
        else { // This will add a new node at the end of the list
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {  // This function puts an element at the head of the linked list.
        Node* newNode = new Node(v);
        if (!head) // If there's no head, the list is empty.
            head = tail = newNode;
        else { // This puts a new node at the head of the list.
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() { // This function removes the first element from the linked list.

        if (!head) { // If there's no head, the list is empty.
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() { // This function removes the last element in the linked list.
        if (!tail) { // If there's no tail, the list is empty.
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) { // If tail points to previous
            tail = tail->prev; // Tail goes to previous
            tail->next = nullptr; // Then tail goes to next on the list to delete the last element.
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() { // This is the destructor to delete the entire linked list.
        while (head) { // We traverse through the list to delete, using two pointers while head is valid.
            Node* temp = head; // Temp points to head
            head = head->next; // Head advances to the next node
            delete temp; // Temp is deleted entirely
        }
    }
    void print() { // This function uses the print method
        Node* current = head; // Current is set to the head of the list.
        if (!current) { //The list is empty if there's no current, which is pointing to head.
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // We go through the list while current is in a valid position.
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() { // This function prints the list in reverse.
        Node* current = tail; // The current is set at tail.
        if (!current) {  //The list is empty if there's no current, which is pointing to tail.
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // We go through the list backwards while current is in a valid position.
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element()
    {
        int counter = 1; // Keeps count
        Node *current = head; // Current is at the head of the list.
        if(!current) // If there's no head where currrent can be, there's nothing in the list.
        {
            cout << "List is empty." << endl;
            return;
        }
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}