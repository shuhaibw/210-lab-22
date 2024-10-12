// COMSC-210 | Lab 22 | Shuhaib Walahi
// IDE used: VS Code

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20, DT_POS = 2;

class DoublyLinkedList 
{
private:

    struct Node 
    {
        int data;
        Node* prev;
        Node* next;

        Node(int val, Node* p = nullptr, Node* n = nullptr) 
        {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:

    // constructor
    DoublyLinkedList() 
    { 
        head = nullptr; 
        tail = nullptr; 
    }

    void push_back(int value) 
    {
        Node* newNode = new Node(value);

        if (!tail) // if there's no tail, the list is empty
        {
            head = tail = newNode;
        } 
        else 
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) 
    {
        Node* newNode = new Node(value);

        if (!head) // if there's no head, the list is empty
        {
            head = tail = newNode;
        } 
        else 
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) 
    {
        if (position < 0) 
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);

        if (!head) 
        {
            head = tail = newNode;
            return;
        }

        Node* temp = head;

        for (int i = 0; i < position && temp; ++i) 
        {
            temp = temp->next;
        }

        if (!temp) 
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next) 
        {
            temp->next->prev = newNode;
        } 
        else 
        {
            tail = newNode; // Inserting at the end
        }

        temp->next = newNode;
    }

    void delete_value(int value) 
    {
        if (!head) 
        {
            return; // Empty list
        }

        Node* temp = head;

        while (temp && temp->data != value) 
        {
            temp = temp->next;
        }

        if (!temp) 
        {
            return; // Value not found
        }

        // if temp is not the head
        if (temp->prev) 
        {
            temp->prev->next = temp->next;
        } 
        // else if temp is pointing at head
        else 
        {
            head = temp->next; // Deleting the head, list becomes empty
        }

        if (temp->next) 
        {
            temp->next->prev = temp->prev;
        } 
        else 
        {
            tail = temp->prev; // Deleting the tail, list becomes empty
        }

        delete temp;
    }

    void delete_pos(int position)
    {
        if (!head) 
        {
            cout << "List is empty" << endl;
            return; // Empty list
        }

        Node *temp = head;

        // point temp exactly at node to delete
        for (int i = 0; temp && i < position; i++)
        {
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Position out of range" << endl;
            return; 
        }
        
        // adjusting pointers
        if (temp->prev)
        {
            // link prev node to the next node
            temp->prev->next = temp->next;
        }
        else
        {
            // delete old head
            head = temp->next;
        }

        if (temp->next)
        {
            // link next node to the prev node
            temp->next->prev = temp->prev;
        }
        else 
        {
            // delete old tail
            tail = temp->prev;
        }

        delete temp;
    }

    void pop_front()
    {
        if (!head) 
        {
            cout << "List is empty" << endl;
            return; // Empty list
        }

        Node *temp = head;
        // move head to next node
        head = head->next;

        if(head)
        {
            // set new heads prev pointer to nullptr
            head->prev = nullptr;
        }
        // delete the old head
        delete temp;
    }

    void pop_back()
    {
        if(!tail)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node *temp = tail;
        // set new tail to prev node
        tail = tail->prev;

        if(tail)
        {
            tail->next = nullptr;
        }
        // delete old tail
        delete temp;
    }

    void print() 
    {
        Node* current = head;

        if (!current) 
        {
            return;
        }

        while (current) 
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    void print_reverse() 
    {
        Node* current = tail;

        if (!current) 
        {
            return;
        }

        while (current) 
        {
            cout << current->data << " ";
            current = current->prev;
        }

        cout << endl;
    }

    ~DoublyLinkedList() 
    {
        while (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() 
{
    // seed random num generator
    srand(static_cast<unsigned>(time(0)));

    DoublyLinkedList list;

    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;

    for (int i = 0; i < size; ++i) 
    {
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    }

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    // pop the front
    cout << "Popping the front... " << endl;
    list.pop_front();
    cout << "List after popping the front: ";
    list.print();

    // pop the back
    cout << "Popping the back... " << endl;
    list.pop_back();
    cout << "List after popping the back: ";
    list.print();

    // delete from specified position
    cout << "Deleting node at position " << DT_POS << "..."<< endl;
    list.delete_pos(DT_POS);
    cout << "List after deleting position " << DT_POS << ": ";
    list.print();

    // try to delete a position that doesn't exist
    int invalidPos = size; 
    cout << "Trying to delete node at position " << invalidPos << "..." << endl;
    list.delete_pos(invalidPos);

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();

    cout << "List forward: ";
    list.print();

    return 0;
}
