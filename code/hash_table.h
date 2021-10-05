#pragma once

#include "dll.h"
#include <string>

const int DEFAULT_TABLE_SIZE = 15;

template <class T>
class HashTable {
public:
    HashTable();
    HashTable(const HashTable& other);

    ~HashTable();
    bool is_empty() const;

    bool contains(const T&  val) const;
    void insert(const T&  val);
    bool remove(const T&  val);
    void clear();
    DLList<T> elements() const; // returns all the elements of the hash table

    HashTable& operator=(const HashTable& other);

private:
    DLList<T>* table;
    int n;   // number of elements in the table
    int m;   // number of buckets in the table

    int hash_value(const T &val) const;
    void resize(int new_size);
};



template <class T>
HashTable<T>::HashTable()
{
    n = 0;
    m = DEFAULT_TABLE_SIZE;
    table = new DLList<T>[m];
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& other)
{
    this->n = other.n;
    this->m = other.m;
    table = new DLList<T>[m];

    for (int i = 0; i < m; i++)
        table[i] = other.table[i];
        // the assignment operator has been overloaded 
        // for the DLL to perform a deep copy
}


template <class T>
HashTable<T>::~HashTable()
{
   delete [] table;
   // Note: deleting an array automatically calls the destructor for
   //       the array elements (the DLLists in this case).
}


template <class T>
bool HashTable<T>::is_empty() const
{
   return n == 0;
}


// Asymptotic Complexity:
//     - O(1) if hashing is perfect
//     - O(n) if hashing is the worst possible (all the elements are in the 
//            same chain and the element is found at the end of the chain). 
//     - O(n/m) if the elements are uniformly distributed across the chains.
//              This is O(1) if n and m are within a constant factor of each
//              other.
template <class T>
bool HashTable<T>::contains(const T&  val) const
{
    int index = hash_value(val);
    return table[index].contains(val);
}

// Always O(1) regardless of how the elements are distributed in the table.
// O(n + m) if the table resizes, but this does not occur frequently.
template <class T>
void HashTable<T>::insert(const T&  val)
{
    int index = hash_value(val);
    table[index].add_to_tail(val); // or add_to_head()

    n++;
    if (n / m >= 8)
        resize(m * 2);
}

// Asymptotic Complexity:
//     - O(n) if hashing is the worst possible (all the elements are in the 
//            same chain and the element is found at the end of the chain).
//            The running time is O(n + m) if the table resizes, but this won't
//            occur frequently. 
//     - O(n/m) if the elements are uniformly distributed across the chains.
//              This is O(1) if n and m are within a constant factor of each
//              other (assuming the table does not resize)
template <class T>
bool HashTable<T>::remove(const T&  val)
{
    int index = hash_value(val);
    return table[index].remove(val);

    n--;
    if (n / m < 2 && m > DEFAULT_TABLE_SIZE)
        resize(m / 2);
}

// A hash function for integers
template <> 
int HashTable<int>::hash_value(const int& val) const  
{
    return abs(val) % m;
}

// A simplified version of the string hash function
// int HashTable<string>::hash_value(const string& val) const 
// {
//     int sum = 0; 
//     int R = 1;
// 
//     for (int i = val.length()-1; i >= 0; i--) {
//         sum += R * val[i];
//         R *= 26;
//    }
// 
//     return sum % m;
// }


// A hash function for strings
template <>
int HashTable<string>::hash_value(const string& val) const
{
    int sum = 0;
    const int R = 33;

    for (int i = 0; i < val.length(); i++)
        sum = (sum*R + val[i]) % m;
    
    return abs(sum);
}


// Returns all the elements in the table.
// There is no guarantee on the order of the elements returned.
template <class T>
DLList<T> HashTable<T>::elements() const 
{
    DLList<T> result;

    for (int i = 0; i < m; i++)
        result.append(table[i]);

    return result;
}


// Resizes the array to the given size.
// All the elements need to be rehashed.
template <class T>
void HashTable<T>::resize(int new_size)
{
    int old_m = m;
    DLList<T>* old_table = table;

    m = new_size;
    table = new DLList<T>[m]; // O(m)

    // Rehash all the values to the new table. Runs in O(old_m + n)
    for (int i = 0; i < old_m; i++) {
        DLLNode<T>* node = old_table[i].head_node();
        while (node != nullptr) {
            int index = hash_value(node->get_val());
            table[index].add_to_tail(node->get_val());
            node = node->get_next();
        }
    }

    delete [] old_table; // O(old_m)
}

// removes all the elements in the hash table and resizes it to be of the
// DEFAULT_TABLE_SIZE
template <class T>
void HashTable<T>::clear() 
{
    delete [] table;
    n = 0;
    m = DEFAULT_TABLE_SIZE;
    table = new DLList<T>[m];
}

// performs a deep copy of the other table.
template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other)
{
    n = other.n;
    m = other.m;

    delete [] table;
    table = new DLList<T>[m];

    for (int i = 0; i < m; i++)
        table[i] = other.table[i];

    return *this;
}
