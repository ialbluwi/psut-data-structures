#pragma once

#include <iostream>
using namespace std;

const int DEFAULT_CAPACITY = 8;

// A Queue class based on a circular array implementation
template <class T>
class QueueArray
{
public:
    QueueArray();
    QueueArray(const QueueArray& other);
    ~QueueArray();

    void enqueue(const T& val);
    T dequeue();
    void clear();

    int get_size() const;
    T get_first() const;
    T get_last() const;
    bool is_empty() const;

    QueueArray& operator=(const QueueArray& other);

private:
    T* data;
    int capacity;  // maximum number of elements allowed in the queue.
    int size;      // current number of elements in the queue.
    int first;     // index of the first element in the queue.
    int last;      // index of the last element in the queue.

    bool is_full() const;
    void resize(int new_cap);
};


// Constructor.
// Initially no values are in the queue, 
// so first and last are -1.
template <class T>
QueueArray<T>::QueueArray()
{
    capacity = DEFAULT_CAPACITY;
    data = new T[capacity];
    last = -1;
    first = -1;
    size = 0;
}

// Destructor.
template <class T>
QueueArray<T>::~QueueArray()
{
    delete [] data;
}

template <class T>
T QueueArray<T>::get_first() const
{
    if (is_empty())
        throw string("ERROR: An empty queue has no first element");

    return data[first];
}

template <class T>
T QueueArray<T>::get_last() const
{
    if (is_empty())
        throw string("ERROR: An empty queue has no last element");

    return data[last];
}

template <class T>
bool QueueArray<T>::is_empty() const
{
    return size == 0;
}

template <class T>
bool QueueArray<T>::is_full() const
{
    return size == capacity;
}

template <class T>
int QueueArray<T>::get_size() const 
{
    return size;
}

template <class T>
void QueueArray<T>::clear()
{
    first = -1;
    last = -1;
    size = 0;

    delete [] data;
    data = new T[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
}


// adds an element to the end of the queue (data[++last] = val). 
// 
// If the queue is empty, both first and last should be set to 0.
//
// If the queue is not full and the last element in the queue is at the last 
// index in the array, then we wrap around and insert the new element at 
// index 0.
//
//  -----------------------------
//  [   |   | A | B | C | D |   ]
//  -----------------------------
//    0   1   2   3   4   6   7
//            ^           ^
//          first       last
//
// After enqueue(E)
//  -----------------------------
//  [   |   | A | B | C | D | E ]
//  -----------------------------
//    0   1   2   3   4   6   7
//            ^               ^
//          first           last
//
// After enqueue(F)
//  -----------------------------
//  [ F |   | A | B | C | D | E ]
//  -----------------------------
//    0   1   2   3   4   6   7
//    ^       ^               
//  last    first           
//
template <class T>
void QueueArray<T>::enqueue(const T& val)
{
    if (is_full())
        resize(capacity * 2);
    
    last = (last + 1) % capacity;
    data[last] = val;
    size++;

    if (first == -1)
        first = 0;
}



// Returns and deletes an element from the queue (val = data[first++]). 
// 
// If there is only one element, both first and last should be set to -1.
//
// If the queue is not empty and the first element in the queue is at the last 
// index in the array, then we wrap around and first becomes 0.
//
//  -----------------------------
//  [ A | B | C | D |   | E | F ]
//  -----------------------------
//    0   1   2   3   4   6   7
//                ^       ^
//               last   first
//
// After dequeue()
//  -----------------------------
//  [ A | B | C | D |   |   | F ]
//  -----------------------------
//    0   1   2   3   4   6   7
//                ^           ^
//               last       first
//
// After dequeue()
//  -----------------------------
//  [ A | B | C | D |   |   |   ]
//  -----------------------------
//    0   1   2   3   4   6   7
//    ^           ^       
//  first        last             

template <class T>
T QueueArray<T>::dequeue()
{
    if (is_empty())
        throw string("ERROR: Can't remove from an empty queue.");

    T val = data[first];
    size--;

    if (size == 0) {
        last = -1;
        first = -1;        
    }   
    else 
        first = (first + 1) % capacity;

    if (size < capacity / 4 && capacity > DEFAULT_CAPACITY)
        resize(capacity / 2);

    return val;
}


// Copy constructor
template <class T>
QueueArray<T>::QueueArray(const QueueArray& other)
{
    capacity = other.capacity;
    size     = other.size;
    first    = other.first;
    last     = other.last;
    data     = new T[capacity];

    int j = other.first;
    for (int i = 0; i < size; i++) {
        data[j] = other.data[j];
        j = (j + 1) % other.capacity;
    }
}


template <class T>
QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& other) 
{
    if (this == &other)
        return *this;

    delete [] data;
    
    capacity = other.capacity;
    size     = other.size;
    first    = other.first;
    last     = other.last;
    data     = new T[capacity];

    int j = other.first;
    for (int i = 0; i < size; i++) {
        data[j] = other.data[j];
        j = (j + 1) % other.capacity;
    }

    return *this;
}


template <class T>
void QueueArray<T>::resize(int new_cap) 
{
    if (new_cap < size)
        throw string("ERROR: Invalid new capacity");

    T* new_data = new T[new_cap];
    int j = first;
    for (int i = 0; i < size; i++) {
        new_data[i] = data[j];
        j = (j + 1) % capacity;
    }

    delete [] data;
    data = new_data;
    capacity = new_cap;

    if (size == 0) {
        first = -1;
        last  = -1;
    } else {
        first = 0;
        last  = size - 1;
    }
}
