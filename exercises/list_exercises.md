Linked List Exercises
=====================

*These exercises are based on* [`dll.h`](../code/dll.h), [`int_sll.h`](../code/int_sll.h) *and* [`ordered_dll.h`](../code/ordered_dll.h).

## Contents
**Singly-Linked Lists:**
1. [Exercise 1](#exercise-1): `bool is_sorted() const`
2. [Exercise 2](#exercise-2): `int get_max() const`
3. [Exercise 3](#exercise-3): `void selection_sort()`
4. [Exercise 4](#exercise-4): `bool check_seq3(int val) const`
5. [Exercise 5](#exercise-5): `bool check_seq(int k, int val) const`
6. [Exercise 6](#exercise-6): `void print_reverse(Node* node)`
7. [Exercise 7](#exercise-7): `void reverse()`

**Doubly-Linked Lists:**

8. [Exercise 8](#exercise-8): `void reverse()` 
9. [Exercise 9](#exercise-9): `T get_at_index(int index) const` 
10. [Exercise 10](#exercise-10): `DLList<T> sublist(int index1, int index2) const `
11. [Exercise 11](#exercise-11): `void remove(int index1, int index2)`  
12. [Exercise 12](#exercise-12): `void remove_all(const T& val)` 
13. [Exercise 13](#exercise-13): `DLList find_common(const DLList& other) const`
14. [Exercise 14](#exercise-14): `void remove_duplicates()`



Exercise 1
----------

Implement the following member function of class `List`, which checks if a singly-linked list is sorted.

```cpp
bool is_sorted() const;
```

#### *Solution*

```cpp
bool List::is_sorted() const 
{
    if (is_empty())
        return true;

    for (Node* curr = head; curr->next != nullptr; curr = curr->next)
        if (curr->val > curr->next->val)
            return false;

    return true;
}
```



Exercise 2
----------

Implement the following member function of class `List`, which returns the maximum element in a singly-linked list. If the list is empty, the function should throw an exception.

```cpp
int get_max() const;
```

#### *Solution*

```cpp
int List::get_max() const 
{
    if (is_empty())
        throw string("ERROR: Attempting to get the max in an empty list");
  
    Node* max_node = head;
    for (Node* curr = head->next; curr != nullptr; curr = curr->next)
        if (curr->val > max_node->val)
            max_node = curr;
  
    return max_node->val;
}
```


Exercise 3
----------

Implement the following member function of class `List`, which sorts the singly-linked list using *selection sort*.

```cpp
void selection_sort();
```

#### *Solution*

```cpp
void List::selection_sort() 
{
    for (Node* ptr1 = head; ptr1 != tail; ptr1 = ptr1->next) {
        // find the minimum from ptr1 to the tail
        Node* min_ptr = ptr1;
        for (Node* ptr2 = ptr1->next; ptr2 != nullptr; ptr2 = ptr2->next) {
            if (ptr2->val < min_ptr->val)
                min_ptr = ptr2;
        }

        swap(ptr1->val, min_ptr->val);  
    }
}
```


Exercise 4
----------

Implement the following member function of class `List`, which returns `true` if the list contains a sequence of 3 consequetive values equal to val.

```cpp
bool check_seq3(int val) const;
```
**Example:** `check_seq3(9)` is true for the list `1, 2, 5, 2, 9, 9, 9, 5` and the list `9, 9, 9, 9, 9, 9` but not for the list `1, 9, 1, 9, 1, 9` or the list `9, 9`.

#### *Solution*

```cpp
bool List::check_seq3(int val) const
{
    // if the list has <= 2 elements
    if (head == tail || head->next == tail)
        return false;
        
    Node* curr = head;
    while (curr->next->next != nullptr) {
        if (curr->val == curr->next->val && curr->val == curr->next->next->val)
            return true;
        curr = curr->next;
    }
    
    return false;
}
```


Exercise 5
----------

Implement the following member function of class `List`, which returns `true` if `val` appears `k` times in the list in consecutive nodes and `false` otherwise. 

```cpp
bool check_seq(int k, int val) const;
```
**Example:** `check_seq(3, 9)` is true for the list `1, 2, 5, 2, 9, 9, 9, 5` and the list `9, 9, 9, 9, 9, 9` but not for the list `1, 9, 1, 9, 1, 9` or the list `9, 9`.

#### *Solution*

```cpp
bool List::check_seq(int k, int val) const
{
    if (k < 0)  return false;
    if (k == 0) return true;

    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->val != val)
            count = 0;
        else 
            count++;
        
        if (count == k) 
            return true;
        else            
            curr = curr->next;
    }

    return false;
}
```


Exercise 6
----------

Implement the following member function of class `List`, which prints the contents of the singly-list in reverse.

```cpp
void print_reverse(Node* node);
```

Assume that this function is called as follows:

```cpp
print_reverse(head);
```

#### *Solution*

```cpp
void List::print_reverse(Node* node) 
{
    if (node == nullptr)
        return;
    print_reverse(node->next);
    cout << node->val << " ";
}
```

Exercise 7
----------

Implement the following member function of class `List`, which reverses the singly-linked list.

```cpp
void reverse();
```

#### *Solution* # 1

```cpp
void List::reverse() {
    List temp_list;

    while (!is_empty()) {
        temp_list.add_to_head(head->val);
        remove_head();
    }

    while (!temp_list.is_empty()) {
        add_to_tail(temp_list.head->val);
        temp_list.remove_head();
    }
}
```

#### *Solution* # 2

```cpp
void List::reverse() {
    Node* prev = nullptr;
    Node* curr = head;

    while (curr != nullptr) {
        Node* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    swap(head, tail);}
```

#### *Solution* # 3 

```cpp
void List::reverse(Node* first) 
{
    if (first == nullptr || first == tail)
        return;

    head = head->next;
    reverse(head);
    add_to_tail(first->val);
    delete first;
}

void List::reverse() {
    reverse(head);
}
```

#### *Solution* # 4

explanation: https://static.us.edusercontent.com/files/lsgyClOC9HqQgPYpusojm1ls

```cpp
void List::reverse(Node *prev, Node *curr)
{
    if (curr->next == nullptr) {
        swap(head, tail);
        tail->next = nullptr;
        head->next = prev;
        return;
    }
    else
        reverse(prev->next, curr->next);    

    curr->next = prev;
}

void List::reverse() 
{
    if (head == tail)
        return;
    reverse(head, head->next)
}
```



Exercise 8
----------

Implement the following member function of class `DLList`, which reverses the *doubly-linked* list.

```cpp
void reverse();
```

#### *Solution*

```cpp
template <class T>
void DLList<T>::reverse() 
{
    if (head == tail) // 0 or 1 nodes
        return;

    DLLNode<T>* ptr1 = head;
    DLLNode<T>* ptr2 = tail;  

    //     (odd size)        (even size)  
    while (ptr1 != ptr2 && ptr1->prev != ptr2) {
        T temp = ptr1->val;    
        ptr1->val = ptr2->val;
        ptr2->val = temp;
        ptr1 = ptr1->next;
        ptr2 = ptr2->prev;
    }
}
```

#### 

Exercise 9
----------

Implement the following member function of class `DLList`, which returns the value at the given *index* in the *doubly-linked* list, where the `head` is assumed to be at index 0. 

```cpp
T get_at_index(int index) const;
```

If the index is invalid, the function should throw an exception.

#### *Solution*

```cpp
template <class T>
T DLList<T>::get_at_index(int index) const 
{  
    if (index < 0)
        throw string("ERROR: Invalid index passed to get_at_index()");
    
    int count = 0;
    DLLNode<T>* curr = head;
    while (curr != nullptr) {
        if (count == index)
            return curr->val;
        curr = curr->next;
        count++;
    }

    // if execution reaches here, then index is larger than
    // the last index in the list    
    throw string("ERROR: Invalid index passed to get_at_index()");
}
```

#### 

Exercise 10
----------

Implement the following member function of class `DLList`, which returns the values in the nodes between the given indices (inclusive). 

```cpp
DLList sublist(int index1, int index2) const;
```

The function should throw an exception if any of the indices is invalid. If `index2` is larger than or equal to the number of nodes in the list, return all the values from `index1` to the `tail`.

#### *Solution*

```cpp
template <class T>
DLList<T> DLList<T>::sublist(int index1, int index2) const 
{  
    if (index1 < 0 || index2 < 0 || index1 > index2)
        throw string("ERROR: Invalid index passed to sublist()");

    // get to index1  
    int count = 0;  
    DLLNode<T>* curr = head;
    while (curr != nullptr) {
        if (count == index1)
            break;
        curr = curr->next;
        count++;
    }

    // if null is reached before reaching index1
    if (curr == nullptr)
        throw string("ERROR: Invalid index passed to sublist()");

    // collect all the values in the nodes between index1  
    // and index2 (stop if the end of the list is reached  
    // before reaching index2)  
    DLList<T> result;  
    while (curr != nullptr && count <= index2) {
        result.add_to_tail(curr->val);
        curr = curr->next;
        count++;  
    }

    return result;
}
```

#### 

Exercise 11
----------

Implement the following member function of class `DLList`, which removes the nodes between the given indices (inclusive). 

```cpp
void remove(int index1, int index2);
```

The function should throw an exception if any of the indices is invalid. If `index2` is larger than or equal to the number of nodes in the list, remove all the nodes from `index1` to the `tail`.

#### *Solution*

```cpp
template <class T>
void DLList<T>::remove(int index1, int index2) 
{  
    if (index1 < 0 || index2 < 0 || index1 > index2)        
        throw string("ERROR: Invalid index passed to sublist()");     

    DLList<T> new_list;      

    // get all the nodes that are not between index1 and index2 inclusive.  
    int count = 0;   
    DLLNode<T>* curr = head;    
    while (curr != nullptr) {        
        if (count < index1 || count > index2)
            new_list.add_to_tail(curr->val);
        curr = curr->next;
        count++;
    }      

    // if curr == nullptr and count <= index1, then index1  
    // is outside the range of valid indices.  
    if (count <= index1)      
        throw string("ERROR: Invalid index passed to sublist()");      

    clear();  
    append(new_list);
}
```

#### 

Exercise 12
----------

Implement the following member function of class `DLList`, which removes all the occurrences of the given value from the doubly-linked list.

```cpp
void remove_all(const T& val);
```

#### *Solution*

```cpp
template <class T>
void DLList<T>::remove_all(const T& val) 
{
    if (is_empty())
        return;

    while (head->val == val) {
        remove_head();
        if (head == nullptr)
            return;
    }

    while (tail->val == val)
        remove_tail();

    DLLNode<T>* curr = head->next;

    while (curr != nullptr) {
        if (curr->val == val) {
            DLLNode<T>* succ = curr->next;
            DLLNode<T>* pred = curr->prev;
            succ->prev = pred;
            pred->next = succ;
            delete curr;
            curr = succ;
        } else
            curr = curr->next;    
    }
}
```

#### 

Exercise 13
----------

Implement the following member function of class `DLList`, which returns all the common values between the current doubly-linked list and the recived doubly-linked list.

```cpp
DLList find_common(const DLList& other) const;
```

**Note 1.** No value appears in the same list more than once.

**Note 2.** An `O(n^2)` solution is fine.

#### *Solution*

```cpp
template <class T>
DLList<T> DLList<T>::find_common(const DLList<T>& other) const 
{
    DLList<T> result;

    if (is_empty() || other.is_empty())    
        return result;

    for (DLLNode<T>* ptr1 = head; ptr1 != nullptr; ptr1 = ptr1->next) {    
        // search for ptr1->val in the other list
        for (DLLNode<T>* ptr2 = other.head; ptr2 != nullptr; ptr2 = ptr2->next) {
            if (ptr1->val == ptr2->val) {
                result.add_to_tail(ptr1->val);
                break;
            }
        }
    }

    return result;
}
```

Exercise 14
----------

Implement the following member function of class `OrderedDLList`, which removes all duplicate elements in the list. After calling this function, the list must contain only distinct elements.

```cpp
void remove_duplicates();
```
**Example:** If the list is `1, 1, 1, 2, 3, 4, 4, 5, 5, 5` it should become `1, 2, 3, 4, 5`.


#### *Solution*

```cpp
template <class T>
void OrderedDLList<T>::remove_duplicates() 
{
    // 0 or 1 elements
    if (head == tail) 
        return;
        
    DLLNode<T>* curr = head->next;
    DLLNode<T>* pred = head;
    
    while (curr != nullptr) {
        if (pred->val == curr->val) {
            if (curr == tail) {
                remove_tail();
                return;
            } else {
                curr = curr->next;
                delete curr->prev;
                curr->prev = pred;
                pred->next = curr;
            }
        } else {
            curr = curr->next;
            pred = pred->next;
        }
    }
}
```
