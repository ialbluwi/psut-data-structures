#pragma once

// A Stack class based on an array implementation
// This is a bounded stack (has a fixed size).
template <class T>
class StackArray
{
public:
    StackArray(int cap);
    StackArray(const StackArray& other);
    ~StackArray();

    void push(const T& val);
    T pop();
    T top() const;

    bool is_empty() const;
    bool is_full() const;

    void clear();
    StackArray& operator=(const StackArray& other);

private:
    T* data;
    int capacity;
    int last;
};


template <class T>
StackArray<T>::StackArray(int cap)
{
    if (cap <= 0)
        throw "Invalid capacity!";

    capacity = cap;
    data = new T[capacity];
    last = -1;
}

template <class T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& other) {
    if (this == &other)
        return *this;

    clear();
    delete [] data;

    capacity = other.capacity;
    data = new T[capacity];

    last = other.last;
    for (int i = 0; i <= last; i++)
        data[i] = other.data[i];

    return *this;
}

template <class T>
StackArray<T>::StackArray(const StackArray<T>& other) {
    capacity = other.capacity;
    data = new T[capacity];

    last = other.last;
    for (int i = 0; i <= last; i++)
        data[i] = other.data[i];
}

template <class T>
StackArray<T>::~StackArray()
{
    delete [] data;
}

template <class T>
void StackArray<T>::push(const T& val)
{
    if (is_full())
        throw "Stack overflow!";

    last++;
    data[last] = val;
}

template <class T>
T StackArray<T>::pop()
{
    if (is_empty())
        throw "Stack underflow!";
        
    T val = data[last];
    last--;
    return val;
}

template <class T>
T StackArray<T>::top() const
{
    if (is_empty()) 
        throw "Attempting to retrieve an element from an empty stack!";

    return data[last];
}

template <class T>
bool StackArray<T>::is_empty() const
{
    return last == -1;
}

template <class T>
bool StackArray<T>::is_full() const
{
    return last == capacity - 1;
}

template <class T>
void StackArray<T>::clear()
{
    last = -1;
}
