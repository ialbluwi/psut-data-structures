#pragma once

#include<iostream>
using std::cout;
using std::string;

/*
 A Node in a singly linked list.
 Every node has a value and a pointer to one adjacent node.
 
 +-------+--+
 |       |  | 
 | Value |*-|-->
 |       |  |
 +-------+--+
 */
class Node {
public:
    int val;
    Node* next;

    Node(int val, Node* next) {
        this->val = val;
        this->next = next;
    }
};
    
// COMMON ERROR: Defining a destructor and adding the statement 'delete next;'
// WHY IS THIS WRONG?
//      - Class Node does not allocate memory, so it is not responsible for
//        deallocating memory.
//      - The statement 'delete next;' deallocates the node pointed at by 'next'
//        which in turn will call the destructor for that node and will 
//        deallocate the next of the next node, etc. This will cascade until all the list
//        nodes are deallocated.



/*
 A Singly Linked List is a group of nodes connected to each other:
 - Each node is connected to only one next node.
 - The "head" pointer points to the first node in the list.
 - The "tail" pointer points to the last node in the list.
        * In an empty list: the head and tail are null pointers.
        * In a list with one node, the head and tail point to the same node.
        * The next pointer of the tail is a null pointer.
 
 
 +-------+--+    +-------+--+    +-------+--+
 |       |  |    |       |  |    |       |  | 
 | Value |*-|--> | Value |*-|--> | Value |*-|--> nullptr
 |       |  |    |       |  |    |       |  |
 +-------+--+    +-------+--+    +-------+--+
     ^                               ^
     |                               |
    head                            tail
 */
class List {
public:
    List();
    ~List();

    Node* get_head() const;
    Node* get_tail() const;
    bool is_empty() const;

    bool contains(int val) const;
    int get_at(int index) const;
    
    void add_to_head(int val);
    void add_to_tail(int val);
    
    void remove_head();
    void remove_tail();
    bool remove(int val);

    void print() const;

private:
    Node* head;
    Node* tail;
};

// Constructor. 
// Initializes the head and tail to nullptr. 
// Without this step, we can't tell if the list is empty or not.
List::List()
{
    head = nullptr;
    tail = nullptr;
}


// Destructor.
// Deletes every node in the list. 
// --- Asymptotic complexity: O(n)
List::~List()
{    
    Node* curr = head;
    Node* del_node;
    
    while (curr != nullptr) {
        del_node = curr;
        curr = curr->next;
        delete del_node;
    }
}

// Checks if the list is empty.
bool List::is_empty() const
{
    // Can also be implemented as: return tail == nullptr;
    return head == nullptr;
}

Node* List::get_head() const 
{ 
    return head; 
}

Node* List::get_tail() const 
{ 
    return tail; 
}

// Adds a node to the beginning of the list.
// Steps:
//    1) Create a new node whose value is "val" and "next" is the list head.
//    2) Make the "head" point at the new node.
//    3) If the list "was" empty, set the tail  also to point at the new node.
// --- Asymptotic complexity: O(1)
void List::add_to_head(int val)
{
    Node* new_node = new Node(val, head);

    head = new_node;
    if (tail == nullptr) 
        tail = new_node;
}

// Adds a node to the end of the list.
// Steps:
//    1) Create a node whose value is "val" and "next" is nullptr.
//    2) If the list is empty, set the "head" to point at the new node.
//    3) If the list is not empty, set tail->next to point at the new node.
//    4) Move the tail to point at the new node.
// --- Asymptotic complexity: O(1)
void List::add_to_tail(int val)
{
    Node* new_node = new Node(val, nullptr);

    if (tail == nullptr) 
        head = new_node;
    else 
        tail->next = new_node;
        
    tail = new_node;
}

// Deletes the head node.
//    * If the list is empty, there is nothing to delete.
//    * If there is only one node, the head and tail should 
//      become null pointers.
//    * If the list has more than one node, the head should 
//      move to the node after the current head.
//
// --- Asymptotic complexity: O(1)
void List::remove_head()
{
    if (is_empty())
        return;

    Node* del_node = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else
        head = del_node->next;

    delete del_node;
}

// Deletes the tail node.
//    * If the list is empty there is nothing to do.
//    * If there is only one node, both the head become null pointers.
//    * If there is more than one node, the node before the tail should
//      become the new tail. Therefore, we need to use a temporary pointer
//      and move it from the beginning of the list until we reach the node
//      that is before the tail.
// --- Asymptotic complexity: O(n)
void List::remove_tail()
{
    // if the list is empty or has one node
    if (head == tail) {
        remove_head();
        return;
    }

    // get to the node before the tail
    Node* prev = head;
    while (prev->next != tail)
        prev = prev->next;

    // remove the tail
    delete tail;
    tail = prev;
    tail->next = nullptr;
}



// Serches for the first occurrence of "val" and deletes it.
//    * If the list is empty, there is nothing to do.
//    * If "val" is at the head or the tail, then use remove_head or 
//      remove_tail.
//    * If "val" is not at the head or the tail, then search for val.
//      If val is found, we need to delete the node and link the node 
//      before it to the node after it. But once we reach a node, we 
//      cannot access the node before it. Therefore, as we traverse the
//      list, we will move two pointers: a pointer to check for val, 
//      and a pointer to point at the node preceding the node we check.
//
//                        ++------------------------------++
//                        ||                              ||
//                        ||                 X            \/
//    +-------+--+    +-------+--+    +-------+--+    +-------+--+
//    |       |  |    |       |  |    |       |  |    |       |  | 
//    |    $  |*-|--->|   $   |*-|-X->|  val  |*-|-X->|    $  |*-|--> NULL
//    |       |  |    |       |  |    |       |  |    |       |  |
//    +-------+--+    +-------+--+    +-------+--+    +-------+--+
//        ^                ^               ^              ^
//        |                |               |              |
//       head             pred            node           tail

//
// --- Asymptotic complexity: 
//        * Best Case:    O(1) If the value is at the head or the tail.
//        * Worst Case:    O(n) If the value is at the node before the tail.
//        COMMON ERROR: Considering an empty list as the best case.
//        WHY IS THIS WRONG? Specifying the best and worst cases is
//                         done independently of the input size. 
bool List::remove(int val)
{
    if (is_empty())
        return false;

    if (val == head->val) {
        remove_head();
        return true;
    }

    if (val == tail->val) {
        remove_tail();
        return true;
    }

    Node* node = head->next;
    Node* pred = head;

    while (node != nullptr) {
        if (node->val == val) {
            pred->next = node->next; 
            delete node;
            return true;
        }

        node = node->next;
        pred = pred->next;
    }
    
    return false;
}

// Returns true if "val" exists in the list and false otherwise.
// Uses linear search.
// --- Asymptotic complexity: 
//        * Best Case: O(1) If val is at the head node.
//        * Worst Case: O(n) If val is not in the list.
bool List::contains(int val) const
{
    for (Node* curr = head; curr != nullptr; curr = curr->next)
        if (curr->val == val)
            return true;

    return false;
}


// Returns the value at the given index.
// If the given index is invalid, the program outputs an error message and
// terminates.
//
// --- Asymptotic complexity: 
//        * Best Case: O(1) If the given index is 0.
//        * Worst Case: O(n) If the given index is the last index in the list.
int List::get_at(int index) const {
    if (is_empty() || index < 0)    
        throw string("ERROR: Invalid argument in function get_at(int)");
    
    int count = 0;
    Node* curr = head;
    
    while (count != index && curr != nullptr) {
        curr = curr->next;
        count++;
    }
            
    if (curr != nullptr)
        return curr->val;
    else
        throw string("ERROR: Invalid argument in function get_at(int)");
}


// Prints the list to standard out according to the
// following format: [item1, item2, item3, ...]
void List::print() const 
{
    cout << "[";

    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->val;

        if (curr->next != nullptr)
            cout << ", ";

        curr = curr->next;
    }

    cout << "]";
}


