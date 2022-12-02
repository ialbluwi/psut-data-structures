Queues Exercises
=====================

*These exercises are based on* [`queue_array.h`](../code/queue_array.h).

## Contents

1. [Exercise 1](#exercise-1): `void print() const`  
2. [Exercise 2](#exercise-2): `void postpone()`
3. [Exercise 3](#exercise-3): `void normalize()`
4. [Exercise 4](#exercise-4): `void remove_all(QueueArray<T>& queue, const T& val) ` 
5. [Exercise 5](#exercise-5): `void move_first_to(QueueArray<T>& queue, int position) `



Exercise 1
----------

Implement the following member function of class `QueueArray`, which prints the elements in the queue. Note that the function is const, which means that functions `enqueue()` and `dequeue()`can't be called.

```cpp
void print() const
```

#### *Solution*

```cpp
template <class T>
void QueueArray<T>::print() const 
{
    cout << "[";
    
    int i = first;
    int count = 0;
    while (count < size) {
        cout << data[i];
        if (count < size-1)
            cout << ", ";
        count++;
        i = (i+1) % capacity;
    }
    
    cout << "]";
}
```



Exercise 2
----------

Implement the following member function of class `QueueArray`, which postpones the first element one position. In other words, the first and second elements in the queue are swapped after calling this function.

The function should not do anything if there are only  `0` or `1` elements in the queue.

```cpp
void postpone()
```

#### *Solution*

```cpp
template <class T>
void QueueArray<T>::postpone() 
{
    if (size == 0 || size == 1)
        return;
    swap(data[first], data[(first + 1) % capacity]);
}
```



Exercise 3
----------

Implement the following member function of class `QueueArray`, which rearranges the elements in the queue array if the first element is not at index `0`. This function should not change the order of the elemnts in the queue. 

```cpp
void normalize()
```

#### *Solution*

```cpp
template <class T>
void QueueArray<T>::normalize() 
{
    if (first == 0 || first == -1)
        return;
    
    QueueArray<T> temp_q;
    while (!is_empty())
        temp_q.enqueue(dequeue());
    
    *this = temp_q;
        
    // A better idea is to just call resize(capacity), which
    // has a similar effect. 
    
    // Another more tedious idea is to create a new array, copy
    // the elements from the old array into the new one starting
    // at index 0, delete the old array and assign the data pointer
    // to the new array.
}
```



Exercise 4
----------

Implement the following non-member function of class `QueueArray`, which removes all the occurrences of `val` from the queue.  

```cpp
template <class T>
void remove_all(QueueArray<T>& queue, const T& val);
```

#### *Solution*

```cpp
template <class T>
void remove_all(QueueArray<T>& queue, const T& val)
{
    QueueArray<T> temp_q;
    while (!queue.is_empty()) {
        T curr_val = queue.dequeue();
        if (curr_val != val)
            temp_q.enqueue(curr_val);
    }
    
    while (!temp_q.is_empty())
        queue.enqueue(temp_q.dequeue());
}
```



Exercise 5
----------

Implement the following non-member function of class `QueueArray`, which moves the first element in the Queue to be at the given position, where positions start at `0` for the first and `size-1` for the last.

**Example.** If the queue contains `[0, 1, 2, 3, 4, 5, 6, 7]` and `move_first_to()` is called with `pos=3`, the queue becomes 
`[1, 2, 3, 0, 4, 5, 6, 7]`

```cpp
template <class T>
void move_first_to(QueueArray<T>& queue, int pos);
```

#### *Solution*

```cpp
template <class T>
void move_first_to(QueueArray<T>& queue, int pos)
{
    if (pos < 0 || pos >= queue.get_size())
        throw string("ERROR: Invalid argument(s)");
              
    QueueArray<T> temp_q;
    T first_val = queue.dequeue();
                     
    for (int i = 0; i < pos; i++)
    	temp_q.enqueue(queue.dequeue());
                     
    temp_q.enqueue(first_val);
                     
    while (!queue.is_empty())
	temp_q.enqueue(queue.dequeue());
    
    while (!temp_q.is_empty())
        queue.enqueue(temp_q.dequeue());
}
```
