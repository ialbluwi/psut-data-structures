#pragma once

#include <iostream>
using std::string;
using std::ostream;

template <class T>
class DLList;

/*
 A Node in a doubly-linked list.
 Every node has a value and a pointer to the next and previous nodes.
 
    +--+-------+--+
    |  |       |  | 
 <--|-*| Value |*-|-->
    |  |       |  |
    +--+----+--+--+
 */
template <class T>
class DLLNode {
public:
    DLLNode(const T& val, DLLNode* next, DLLNode* prev);

    T get_val() const { return val; }
    DLLNode* get_next() const { return next; }
    DLLNode* get_prev() const { return prev; }
    
private:
    T val;
    DLLNode* next;
    DLLNode* prev;

    friend class DLList<T>;
};

template <class T>
DLLNode<T>::DLLNode(const T& val, DLLNode* next, DLLNode* prev)
{
    this->val = val;
    this->next = next;
    this->prev = prev;
}



/*
  A Doubly-Linked List is a group of nodes connected to each other.
    - Each node is connected to the next and previous nodes in the list.
    - The previous pointer of the head node is a null pointer.
    - The next pointer of the tail node is a null pointer.
    - The rest of the properties are similar to the properties of the 
      Singly-Linked List.
 
 
        +--+-------+--+   +--+-------+--+   +--+-------+--+ 
        |  |       |*-|-->|  |       |*-|-->|  |       |*-|--> null
        |  | Value |  |   |  | Value |  |   |  | Value |  |
null <--|-*|       |  |<--|-*|       |  |<--|-*|       |  |
        +--+-------+--+   +--+-------+--+   +--+-------+--+
               ^                                  ^
               |                                  |
              head                               tail
 */
template <class T>
class DLList {
public:
    DLList();
    DLList(const DLList& other);
    ~DLList();

    bool is_empty() const;
    
    DLLNode<T>* head_node() const;
    DLLNode<T>* tail_node() const;
    T head_val() const;
    T tail_val() const;

    void add_to_head(const T& val);
    void add_to_tail(const T& val);
    void append(const DLList& otherList);
    
    void remove_head();
    void remove_tail();
    bool remove(const T& val);
    void clear();    
    
    bool contains(const T& val) const;
    DLList& operator=(const DLList& other);

private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
};


template <class T>
DLList<T>::DLList()
{
    head = nullptr;
    tail = nullptr;
}

// Copy constructor. Performs a deep copy of the other list.
template <class T>
DLList<T>::DLList(const DLList<T>& other) {
    head = nullptr;
    tail = nullptr;

    // function append adds each value of 
    // "other" to the tail of this list
    append(other);
}



// Destructor: Deletes all the nodes in the list.
// Delegates the work to function clear().
// --- Asymptotic complexity: O(n).
template <class T>
DLList<T>::~DLList()
{
    clear();
}


// Deletes all the nodes in the list.
// --- Asymptotic complexity: O(n).
template <class T>
void DLList<T>::clear()
{
    DLLNode<T>* tmp = head;
    DLLNode<T>* del_node;

    while (tmp != nullptr) {
        del_node = tmp;
        tmp = tmp->next;
        delete del_node;
    }

    head = nullptr;
    tail = nullptr;
}



// Checks if the list is empty.
template <class T>
bool DLList<T>::is_empty() const
{
    return head == nullptr;
}

template <class T>
DLLNode<T>* DLList<T>::head_node() const
{
    return head;
}

template <class T>
DLLNode<T>* DLList<T>::tail_node() const 
{
    return tail;
}

template <class T>
T DLList<T>::head_val() const
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve a value of the head from an empty list.");
    
    return head->val;
}

template <class T>
T DLList<T>::tail_val() const 
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve a value of the tail from an empty list.");

    return tail->val;
}

// Adds a node to the beginning of the list.
// Steps:
//  1) Create a node with value "val". Set the next pointer to point at the 
//     head and prev to be nullptr.
//  2) Set the prev pointer of the current head to point at the new node.
//  3) If the list is empty, move the tail to point at the new node.
//  4) Move the head to point at the new node.
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::add_to_head(const T& val)
{
    DLLNode<T>* new_node = new DLLNode<T>(val, head, nullptr);

    if (head != nullptr)
        head->prev = new_node;

    head = new_node;
    if (tail == nullptr)
        tail = new_node;
}



// Adds a node to the end of the list.
// Steps:
//  1) Create a node with value "val". Set the next pointer to nullptr
//     and prev to point at the current tail.
//  2) Set the next pointer of the current tail to point at the new node.
//  3) If the list is empty, move the head to point at the new node.
//  4) Move the tail to point at the new node.
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::add_to_tail(const T& val)
{
    DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, tail);

    if (tail != nullptr)
        tail->next = new_node;

    tail = new_node;
    if (head == nullptr)
        head = new_node;
}




// Deletes the head node.
//  * If the list is empty, there is nothing to delete.
//  * If there is only one node, the node is deleted 
//    and the head and tail are set to null.
//  * If the list has more than one node:
//     - Create a node del_node to point at the current head.
//     - Move the current head to the next node.
//     - Set the prev pointer of the new head to null.
//     - Delete the node pointed at by del_node.
//     
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::remove_head()
{
    DLLNode<T>* del_node = head;

    if (is_empty())
        return;

    if (head == tail) // if only one node in list
        head = tail = nullptr;
    else {
        head = del_node->next;
        head->prev = nullptr;
    }
    delete del_node;
}


// Deletes the tail node.
//  * If the list is empty, there is nothing to delete.
//  * If there is only one node, the node is deleted 
//    and the head and tail are set to null.
//  * If the list has more than one node:
//        - Create a node del_node to point at the current tail.
//        - Move the current tail to the previous node.
//        - Set the next pointer of the new tail to null.
//        - Delete the node pointed at by del_node.
//
// --- Asymptotic complexity: O(1)
// --- Note that this operation was O(n) in the singly-linked list.
// --- The prev pointer allows moving the tail easily one step backward, which
// --- was not possible in the SLL without traversing the list upto the node
// --- preceding the tail.
template <class T>
void DLList<T>::remove_tail()
{
    if (is_empty())
        return;

    DLLNode<T>* del_node = tail;

    if (head == tail) // if only one node in list
        head = tail = nullptr;
    else {
        tail = del_node->prev;
        tail->next = nullptr;    
    }

    delete del_node;
}



// Serches for the first occurrence of "val" and deletes it. 
//  * If the list is empty, there is nothing to do.
//  * If "val" is at the head or the tail, then use remove_head() or 
//    remove_tail().
//  * If "val" is not at the head or the tail, then search for val.
//    If val is found, we need to delete the node and link the node before it
//    to the node after it. Due to the presence of the prev pointer, there is
//    no need to move a pred pointer as was the case in the SLL.
//
//
//                      +--------------------------+
//                      |                          |
//                      |             x            V
//          +--+-------+--+    +--+-------+--+    +--+-------+--+ 
//          |  |       |*-|-X->|  |       |*-|--->|  |       |*-|--> 
//  ....    |  |  val  |  |    |  |  val  |  |    |  |  val  |  |    ....
//       <--|-*|       |  |<---|-*|       |  |<-X-|-*|       |  |
//          +--+-------+--+    +--+-------+--+    +--+-------+--+
//                ^     ^             ^             |     ^
//                |     |             |             |     |
//              pred    |            node           |    succ
//                      +---------------------------+
//
// --- Asymptotic complexity: 
//       * Best Case:   O(1) If the value is at the head or the tail.
//       * Worst Case:  O(n) If the value is at the node before the tail or if
//                      the value is not in the list.
template <class T>
bool DLList<T>::remove(const T& val)
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

    // traverse list to find the node to be deleted
    for (DLLNode<T>* curr = head->next; curr != nullptr; curr = curr->next) {
        if (curr->val == val) {
            DLLNode<T>* pred = curr->prev;
            DLLNode<T>* succ = curr->next;
            pred->next = succ; 
            succ->prev = pred;
            delete curr;
            return true;
        }
    }

    // not found
    return false;
}



// Searches for a value in the list.
// --- Asymptotic complexity: O(n).
template <class T>
bool DLList<T>::contains(const T& val) const
{
    DLLNode<T>* curr;

    for (curr = head; curr != nullptr; curr = curr->next) {
        if (curr->val == val)
            return true;
    }

    return false;
}




// Adds all of the values in the nodes of "other" to 
// the tail of the current list. The other list should stay intact and the two
// lists should remain separate lists.
// --- Asymptotic complexity: O(n), where n is the number 
// --- of elements in the other list.
template <class T>
void DLList<T>::append(const DLList& other)
{
    if (this == &other)
        throw string("ERROR: Can't append the list to itself"); 
        // THINK: Why not?
        // How can we handle this case?
    
    DLLNode<T>* curr;

    for (curr = other.head; curr != nullptr; curr = curr->next)
        add_to_tail(curr->val);
}


// copy assignment
// This function is important to avoid shallow copying when using the
// assignment operator
template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    // Guard against self assignment
    if (this == &other)
        return *this;
 
    clear();
    append(other);

    return *this;
}


template<class T>
ostream& operator<<(ostream& out, const DLList<T>& list) {
    out << "[";

    DLLNode<T>* curr = list.head_node();
    while (curr != nullptr) {
        out << curr->get_val();
        if (curr->get_next() != nullptr)
            out << ", ";
        curr = curr->get_next();
    }
    out << "]";

    return out;
}
