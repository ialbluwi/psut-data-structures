Hash Table Exercises
=====================

*These exercises are based on* [`hash_table.h`](../code/hash_table.h).

## Contents

1. `T max() const`  
2. `bool has_duplicates() const`
3. `void remove_duplicates()`
4. ` bool equals(const HashTable& other) const` 
5. `bool has_long_chains() const`
6. `void print() const`



Exercise 1
----------

Implement the following member function of class `HashTable`, which returns the maximum element in the hash table. The function should throw an exception if the table is empty.

```cpp
T max() const;
```

#### *Solution*

```cpp
template <class T>
T HashTable<T>::max() const 
{
    if (is_empty())
        throw "Error: Attempting to retrieve the max from an empty hash table."
  
    DLLNode<T>* max_node = nullptr;
    for (int i = 0; i < m; i++) {
        DLLNode<T>* curr = table[i].head_node();
        while (curr != nullptr) {
            if (max_node == nullptr || curr->get_val() > max_node->get_val())
                max_node = curr;
            curr = curr->get_next();
        }
    }
  
    return max_node->get_val();
}

// NOTE. This could be made simpler by calling the elements() 
// function and then iterating over the returned linked list.
```



Exercise 2
----------

Implement the following member function of class `HashTable`, which checks if any element appears in the hash table more than once.

```cpp
bool has_duplicates() const;
```

#### *Solution*

```cpp
template <class T>
bool HashTable<T>::has_duplicates() const
{
    HashTable<T> temp_table;
    DLList<T> temp_list = elements();
  
    DLLNode<T>* curr = temp_list.head_node();
    while (curr != nullptr) {
        if (temp_table.contains(curr->get_val()))
            return true;
        temp_table.insert(curr->get_val());
        curr = curr->get_next();
    }
  
    return false;
}
```



Exercise 3
----------

Implement the following member function of class `HashTable`, which removes all the duplicates from the hash table.

```cpp
void remove_duplicates();
```

#### *Solution*

```cpp
template <class T>
void HashTable<T>::remove_duplicates()
{
    HashTable<T> temp_table;
    DLList<T> temp_list = elements();
  
    // insert into temp_table only distinct elements
    DLLNode<T>* curr = temp_list.head_node();
    while (curr != nullptr) {
        if (!temp_table.contains(curr->get_val()))
            temp_table.insert(curr->get_val());
        curr = curr->get_next();
    }
  
    clear();
  
    // insert back the elements from temp_table
    temp_list = temp_table.elements();
    curr = temp_list.head_node(); 
    while (curr != nullptr) {
        insert(curr->get_val());
        curr = curr->get_next();
    }
}
```



Exercise 4
----------

Implement the following member function of class `HashTable`, which checks if the hash table is equal to the `other` hash table. Two hash tables are equal if they both contain exactly the same elements regardless of how they are distributed in the tables.

```cpp
bool equals(const HashTable& other) const;
```

For simplicity, assume that the elements in both tables are distinct (i.e. a situation where one table has the elements `{1, 1, 1, 1, 1, 2}` and the other has `{2, 2, 2, 2, 2, 1}` will not occur).

#### *Solution*

```cpp
template <class T>
bool HashTable<T>::equals(const HashTable<T>& other) const
{
    if (n != other.n)
        return false;
  
    for (int i = 0; i < m; i++) {
        DLLNode<T>* curr = table[i].head_node();
        while (curr != nullptr) {
            if (!other.contains(curr->get_val()))
                return false;
            curr = curr->get_next();
        }
    }
  
    return true;
}
```



Exercise 5
----------

Implement the following member function of class `HashTable`, which checks if any chain in the table is longer than twice the average chain length in the table.

```cpp
bool has_long_chains() const;
```

#### *Solution*

```cpp
template <class T>bool 
HashTable<T>::has_long_chains() const
{  
    double avg_length = (double) n / m;

    for (int i = 0; i < m; i++) {
        int count = 0;
        DLLNode<T>* curr = table[i].head_node();

        while (curr != nullptr) {
            count++;
            curr = curr->get_next();
        }
        
        if (count > 2 * avg_length)
            return true;
    }
    
    return false;
}
```



Exercise 6
----------

Implement the following member function of class `HashTable`, which prints the hash table to the standard output according to the format shown below.

```cpp
void print() const;// EXAMPLE FOR PRINTING A TABLE WITH 5 CHAINS// [0] {20, 10, 40}// [1] {11}// [2] {2, 12, 7, 2, 2, 27}// [3] {}// [4] {9, 19}
```

#### *Solution*

```cpp
template <class T>
void HashTable<T>::print() const
{ 
    for (int i = 0; i < m; i++) {
        cout << "[" << i << "] ";
        cout << "{";

        DLLNode<T>* curr = table[i].head_node();
        while (curr != nullptr) {
            cout << curr->get_val();
            if (curr != table[i].tail_node())
                cout << ", ";      

            curr = curr->get_next();
        }

        cout << "}" << endl;
    }
}
```
