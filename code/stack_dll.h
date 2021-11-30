#pragma once

// A Stack class based on a DLL implementation
// Delegates the work to a DLL object.
//
// A stack can be implemented as a linked list or as an array by adding
// and deleting from the same end. For example: 
//      add_to_tail() + remove_tail() or
//      add_to_head() + remove_head()
//
// If a singly-linked list is used, addition and deletion should 
// be done at the head because remove_tail() performs O(n) operations.
#include "dll.h"

template <class T>
class StackDLL
{
public:
    void push(const T& val);  // adds an element to the stack
    T pop();                  // returns and Removes the last added element.
    T top() const;            // returns the last added element.

    bool is_empty() const;    
    void clear();

private:
    DLList<T> list;
};

// NOTE. The default constructor and destructor of StackDLL
// automatically call the default constructor and destructor
// of DLList.


template <class T>
void StackDLL<T>::push(const T& val)
{
    list.add_to_tail(val);
}

template <class T>
T StackDLL<T>::pop()
{
    if (is_empty())
        throw "Stack underflow";
        
    T val = list.tail_val();
    list.remove_tail();
    return val;
}

template <class T>
T StackDLL<T>::top() const
{
    if (is_empty())
        throw "Stack underflow";

    return list.tail_val();
}

template <class T>
bool StackDLL<T>::is_empty() const
{
    return list.is_empty();
}

template <class T>
void StackDLL<T>::clear()
{
    list.clear();
}

