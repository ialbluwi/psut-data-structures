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
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::add_to_head(const T& val)
{
    // The next of the new node is the old head, and the previous is nullptr
    DLLNode<T>* new_node = new DLLNode<T>(val, head, nullptr);

    // If there is a head in the list, then its previous must
    // point at the newly crated node
    if (head != nullptr)
        head->prev = new_node;

    // The head must become the new node.
    // The tail changes only if it is the first node added to the list
    head = new_node;
    if (tail == nullptr)
        tail = new_node;
}



// Adds a node to the end of the list.
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::add_to_tail(const T& val)
{
    // The next of the new tail is nullptr, and the previous is the old tail
    DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, tail);

    // If there is a tail already in the list, then its next
    // must point at the newly created node
    if (tail != nullptr)
        tail->next = new_node;

    // The tail pointer must always move to point at the
    // newly created node. The head changes only if it is
    // the first node added to the list.
    tail = new_node;
    if (head == nullptr)
        head = new_node;
}




// Deletes the head node.
// --- Asymptotic complexity: O(1)
template <class T>
void DLList<T>::remove_head()
{
    if (is_empty())
        return;

    // save a pointer to the current head
    // and move the head forward.
    DLLNode<T>* del_node = head;
    head = del_node->next;

    // if the head is now nullptr, it means that
    // there is only one node in the list. Hence,
    // the tail must also become nullptr.
    if (head == nullptr)
        tail = nullptr;
    else
        head->prev = nullptr;
        // if the head is not nullptr, its prev
        // must be set to nullptr 

    delete del_node;
}


// Deletes the tail node.
// --- Asymptotic complexity: O(1)
// --- Note that this operation was O(n) in the singly-linked list.
// --- The prev pointer allows moving the tail easily one step backward, which
// --- was not possible in the SLL without traversing the list up to the node
// --- preceding the tail.
template <class T>
void DLList<T>::remove_tail()
{
    if (is_empty())
        return;

    // save a pointer to the current tail
    // and move the tail pointer backwards
    DLLNode<T>* del_node = tail;
    tail = tail->prev;

    // if the tail is now nullptr, this means that
    // there is only one node in the list. Hence,
    // the head must also point at nullptr
    if (tail == nullptr) 
        head = nullptr;
    else
        tail->next = nullptr;
        // if the tail is not nullptr, its next
        // must be set to nullptr

    delete del_node;
}



// Removes one occurrence of "val" from the list and returns true. 
// Returns false if val is not in the list.
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
    DLLNode<T>* temp1 = other.head;
    DLLNode<T>* temp2 = other.tail;
    
    while (temp1 != temp2) {
        add_to_tail(temp1->val);
        temp1 = temp1->next;
    }
    
    if (temp1 != nullptr)
        add_to_tail(temp1->val);
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
