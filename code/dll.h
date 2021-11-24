#pragma once

#include <iostream>
using std::string;
using std::ostream;


template <class T>
class DLList;

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

// A doubly-linked list class to store elements of a generic type T
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

template <class T>
DLList<T>::DLList(const DLList<T>& other) {
    head = nullptr;
    tail = nullptr;
    append(other);
}

template <class T>
DLList<T>::~DLList()
{
    clear();
}

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

template <class T>
bool DLList<T>::is_empty() const
{
    return head == nullptr;
}

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

template <class T>
void DLList<T>::add_to_tail(const T& val)
{
    DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, tail);

    if (tail != nullptr) //If list is non-empty
        tail->next = new_node;

    tail = new_node;
    if (head == nullptr)
        head = new_node;
}

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
            pred->next = curr->next; 
            succ->prev = curr->prev;
            delete curr;
            return true;
        }
    }

    return false;
}

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
        throw "Attempting to retrieve a value of the head from an empty list. ";
    return head->val;
}

template <class T>
T DLList<T>::tail_val() const 
{
    if (is_empty())
        throw "Attempting to retrieve a value of the tail from an empty list. ";

    return tail->val;
}

template <class T>
void DLList<T>::append(const DLList& other)
{
    if (this == &other)
        throw "Can't append list to itself";

    for (DLLNode<T>* curr = other.head; curr != nullptr; curr = curr->next)
        add_to_tail(curr->val);
}

// copy assignment
template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
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

