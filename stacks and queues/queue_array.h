#pragma once

// A Queue class based on a circular array implementation
template <class T>
class QueueArray
{
public:
    QueueArray(int cap);
    QueueArray(const QueueArray& other);
    ~QueueArray();

    void enqueue(const T& val);
    T dequeue();

    T get_first() const;
    T get_last() const;
    
    bool is_empty() const;
    bool is_full() const;
    
    void clear();
    QueueArray& operator=(const QueueArray& other);

private:
    T* data;
    int capacity;  // maximum number of elements allowed in the queue.
    int size;      // current number of elements in the queue.
    int first;     // index of the first element in the queue.
    int last;      // index of the last element in the queue.
};


// Constructor.
// Initially no values are in the queue, so first and last are -1.
template <class T>
QueueArray<T>::QueueArray(int cap)
{
    capacity = cap;
    data = new T[capacity];
    size = 0;

    first = -1;
    last = -1;
}

// Copy constructor
template <class T>
QueueArray<T>::QueueArray(const QueueArray& other)
{
    capacity = other.capacity;
    data = new T[capacity];
    first = -1;
    last = -1;
    size = 0;

    for (int i = other.first; size < other.size; i = (i+1) % capacity)
        enqueue(other.data[i]);
}


// Destrucotr.
template <class T>
QueueArray<T>::~QueueArray()
{
    delete [] data;
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

template <class T>
void QueueArray<T>::enqueue(const T& val)
{
    if (is_full())
        throw "Can't enqueue to a full queue";

    if (is_empty()) {
        first = 0;
        last = 0;
    }
    else 
        last = (last + 1) % capacity;

    data[last] = val;
    size++;
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
        throw "Can't remove from an empty queue.";

    T val = data[first];
    size--;

    if (size == 0) {
        last = -1;
        first = -1;        
    }   
    else 
        first = (first + 1) % capacity;

    return val;
}

template <class T>
T QueueArray<T>::get_first() const
{
    return data[first];
}

template <class T>
T QueueArray<T>::get_last() const
{
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
void QueueArray<T>::clear()
{
    first = -1;
    last = -1;
    size = 0;
}

template <class T>
QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& other) {
    if (this == &other)
        return *this;

    clear();
    delete [] data;

    capacity = other.capacity;
    data = new T[capacity];

    for (int i = other.first; size < other.size; i = (i+1) % capacity)
        enqueue(other.data[i]);

    return *this;
}