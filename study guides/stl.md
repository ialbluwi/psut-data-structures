# STL Overview
The STL is a library in C++ (short for Standard Template Library) that offers a wide range of container classes implemented using data structures we have seen in the course. The following are examples:
* `stack`
* `queue`
* `vector` (array-based list)
* `list` (doubly-linked list)
* `set` (balanced binary search tree)
* `map` (balanced binary search tree)
* `unordered_set` (hash table)
* `unordered_map` (hash table)
* `priority_queue` (heap)

# What You Need To Know

There is a lot to learn about the STL. You are required, in this course, to know the following about the containers `vector`, `list`, `stack`, `queue`, `set`, and `map`:

* The basic operations.
* The running time of these operations.
* How to iterate using **range-based** loops.
* When to use which container.

Beyond this course, you also should know the following:
* Other containers. For example, the algorithms course assumes that you know how to use the `priority_queue`.
* Iterators. While we don't use them in the course, they are important to learn about if you'd like to use the STL in your life. 
* Algorithms. The library has many algorithms for searching, sorting, shuffling, generating permutations, etc.

# Learning Resources

1. **STL Overview Video** (prepared by our UTA Aya Tell):   
https://drive.google.com/file/d/1UzGUJo0SoTqdrPRJxI5pek5DaFIErchI/view  
This video covers what you need for this course's exams and assignments.

2. **STL Simplified Reference**:  
This is provided below and is similar in scope to what is in the video.

There are tons of online resources on the STL. Feel free to learn from wherever you like.  
[This is a video](https://drive.google.com/file/d/1dywBBjQJd7yDoEGd8fcMfNgf6Pg5nLvX/view?usp=drive_link) recorded for this course, which covers iterators, priority queues, and some STL algorithms (these are not required for the exams, but are important to know).

# STL Simplified Reference

## Stacks & Queues

The following example shows how to use the STL `stack` and `queue` classes.
```cpp
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

/* Stack Functions:
 *   push(val): adds val to the stack
 *   top()    : returns the top of the stack
 *   pop()    : removes the top of the stack
 *              (does not return it back)
 *   empty()  : checks if the stack is empty
 *   size()   : returns the number of elements in the stack  
 *
 * Queue Functions:
 *   push(val): enqueues val to the queue
 *   pop()    : dequeues from the queue 
 *   front()  : returns the first element in the queue
 *   back()   : returns the last element in the queue
 *   empty()  : checks the queue is empty
 *   size()   : returns the number of elements in the queue
 */
int main() {
    stack<int> s;
    queue<int> q;

    // add 0-9 to the stack and queue
    for (int i = 0; i < 10; i++) {
        s.push(i);
        q.push(i);
    }

    // remove the stack elements and print them
    while (!s.empty()) {
        int val = s.top();
        cout << val << " ";
        s.pop();
    }
    cout << endl;

    // remove the queue elements and print them
    while (!q.empty()) {
        int val = q.front();
        cout << val << " ";
        q.pop();
    }

    return 0;
} 
```


## Vectors

The `vector` class is an array-list. It is probably the class in the STL that you will use most as a C++ programmer. The following code shows how the class can be used and highlights some of the main differences and similarities between the `vector` class and our List ADT.
```cpp
#include <vector>
#include <iostream>
using namespace std;

/* Basic vector functions:
 *   push_back(val): add_to_tail(val)
 *   pop_back()    : remove_tail()
 *   clear()       : removes all the elements
 *   empty()       : checks if the vector is empty
 *   size()        : returns the number of elements in the vector
 *   operator[i]   : direct access to element i (just like in arrays)
 *      
 * Note that the class does not offer dedicated public functions for 
 * adding or removing from the beginning of the vector.
 */
int main() {
    // v will contain [0, 1, 2, ..., 9]
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    // prints 10 elements randomly from v
    for (int i = 0; i < 10; i++) {
        int rand_index = rand() % v.size();
        cout << v[rand_index] << " ";
    }
    cout << endl;

    return 0;
} 
```
The full documentation for the class can be found [here](https://en.cppreference.com/w/cpp/container/vector).

## Linked Lists

The `list` class in the STL is implemented as a doubly-linked list. 
```cpp
#include <list>
#include <iostream>
using namespace std;

/* Basic vector functions:
 *      push_back(val)  : add_to_tail(val)
 *      pop_back()      : remove_tail()
 *      push_front(val) : add_to_head(val)
 *      pop_front()     : remove_head()
 *      front() : head_val()
 *      back()  : tail_val()
 *      clear() : removes all the elements
 *      empty() : checks if the vector is empty
 *      size()  : returns the number of elements in the vector
 */
int main() {
    // mylist will be: 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    list<int> mylist;
    for (int i = 0; i < 10; i++) {
        mylist.push_back(i);
        mylist.push_front(i);
    }

    // removes from the head and prints
    while (!mylist.empty()) {
        cout << mylist.front() << " ";
        mylist.pop_front();
    }
    cout << endl;

    return 0;
} 
```
The full documentation of the class can be found [here](https://en.cppreference.com/w/cpp/container/list).

## The `set` Container

This container does not allow duplicates. Since it is implemented as a balanced binary search tree, insertion, deletion and search all run in logarithmic time. The following are examples for its use  
```cpp
#include <set>
#include <iostream>
using namespace std;

/* Basic set functions:
 *   insert(val) : insert val if it is not in the set  - O(logn)
 *   erase(val)  : removes val                         - O(logn)
 *   count(val)  : 1 if val is in the set, 0 otherwise - O(logn)
 *   clear()     : removes all the elements in the set - O(n)
 *   empty()     : checks if the set is empty          - O(1)
 *   size()      : number of elements in the set       - O(1)
 */
int main() {
    set<string> names;
    names.insert("Khalid");     // an attempt to insert the
    names.insert("Khalid");     // same name three times
    names.insert("Khalid");     

    names.insert("Ahmad");
    names.insert("Hamada");

    names.insert("Salma");
    names.erase("Salma");       // remove Salma

    cout << "Name          # of occurrences" << endl;
    cout << "------------------------------" << endl;
    cout << "Khalid        " << names.count("Khalid") << endl;
    cout << "Ahmad         " << names.count("Ahmad") << endl;
    cout << "Salma         " << names.count("Salma") << endl;
    cout << "WAQWAQ        " << names.count("WAQWAQ") << endl;

    return 0;
} 
```
To check if the `set` contains an element, the easiest way is to check if the `count` equals 1.

There are also other functions that you can use. Check the [documentation](https://en.cppreference.com/w/cpp/container/set/erase) if you are interested.

## The `map` Container

This container allows mapping keys to values. For example, you can map:
```
Key              Value
---------------------------
Usernames     to Passwords
Student IDs   to GPAs
Country Names to Capital Cities
Words         to Meanings
etc.
```
This container does not allow duplicates (just like the `set` container). This makes sense because you can't have two identical usernames or two identical student IDs. However, values can repeat (e.g. two students can have the same GPA).

The `map` container is typically implemented as a balanced binary search tree, where each node has a key and a value (+ pointers to the left and right children). The following is an example of a tree mapping cities to their population counts:

<p align="center">
<img src="https://github.com/user-attachments/assets/6ce9d8da-b808-43a3-9062-04294e042b8f" alt="drawing" width="400"/>
</p>

Note that `Amman > Ajloun` (because `m > j`) and `Amman < Aqaba` (because `m < q`).

Searching is done by comparing the keys and returning the value when the node is found (e.g. searching for `Aqaba` compares `Aqaba` to `Huwwara` and goes left and then to `Amman` and goes right and then returns `188160`.

The following is an example that shows how to build the above `map` in C++
```cpp
#include <map>
#include <iostream>
using namespace std;

/* Basic map functions:
 *   mymap[key] = val : inserts the (key, val) pair if key is not in mymap
 *                      replaces the old val if key is already in mymap
 *                      O(log n)
 *
 *   mymap[key]       : returns the value corresponding to the given key
 *                      if key is not in mymap, key is inserted into the map
 *                      with a corresponding garbage value
 *                      O(log n)
 *   
 *   mymap.erase(key)  : removes key from mymap                  O(log n)
 *   mymap.count(key)  : 1 if key is in mymap, 0 otherwise       O(log n)
 *   mymap.clear()     : removes all key-value pairs from mymap  O(n)
 *   mymap.empty()     : checks if mymap is empty                O(1)
 *   mymap.size()      : returns the number of elements in mymap O(1)
 */
int main() {
    map<string, int> cities;
    
    cities["Huwwara"] = 25000;   // the [] operator can be used to insert
    cities["Irbid"]   = 177000;  
    cities["Amman"]   = 4008000;
    cities["Ajloun"]  = 148870;
    cities["Aqaba"]   = 188160;
    cities["Maan"]    = 41000;
    cities["Karak"]   = 32216;
    cities["Zarqa"]   = 1365000;

    cities["Zarqa"]   = 9999999;  // if the key already exists
                                  // the value is updated

    cities.erase("Maan");         // removes Maan:41000 from the map


    cout << "City          Population" << endl;
    cout << "------------------------------" << endl;
    cout << "Huwwara        " << cities["Huwwara"] << endl;
    cout << "Amman          " << cities["Amman"] << endl;
    cout << "Zarqa          " << cities["Zarqa"] << endl << endl;

    cout << "calling cities.count(\"Maan\") returns " << cities.count("Maan") << endl;
    cout << "calling cities.count(\"Zarqa\") returns " << cities.count("Zarqa") << endl;

    return 0;
} 
```
You can read the [documentation](https://en.cppreference.com/w/cpp/container/map) of the map container if you are interested in learning more about it.

## Range-Based Loops

To simplify iteration over containers in the STL, the C++ language provides **range-based loops**, which allow using the same syntax to iterate over all the containers. Here is an example for iterating over the elements in a `set`:
```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    set<string> names;
    names.insert("Khalid");
    names.insert("Ahmad");
    names.insert("Hamada");
    names.insert("Salma");

    // For every string name in the container "names"
    for (string name : names)
        cout << name << endl;

    return 0;
} 
```
Here is also another example for iterating over the elements of a `set` of integers:
```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    set<int> numbers;
    for (int i = 0; i < 10; i++)
        numbers.insert(rand() % 10);    

    // For every integer num in the container "numbers"
    for (int num : numbers)
        cout << num << endl;

    return 0;
} 
```
As you might have noticed, iterating over a `set` always gives the elements in ascending order.

Here are also examples for iterating over a `list` and a `vector`:
```cpp
#include <vector>
#include <list>
#include <iostream>
using namespace std;

int main() {
    vector<int> myvector;
    list<int> mylist;

    for (int i = 0; i < 10; i++) {
        myvector.push_back(i);
        mylist.push_back(i);
    }

    // For every integer num in the container myvector
    cout << "vector: ";
    for (int num : myvector)
        cout << num << " ";
    cout << endl;

    // For every integer num in the container mylist
    cout << "list:   ";
    for (int num : mylist)
        cout << num << " ";
    cout << endl;

    return 0;
} 
```

Similarly, we can iterate over the key-value pairs in a `map`. Here is an example:
```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    map<string, int> cities;
    
    cities["Huwwara"] = 25000;   
    cities["Irbid"]   = 177000;
    cities["Amman"]   = 4008000;
    cities["Ajloun"]  = 148870;
    cities["Aqaba"]   = 188160;
    cities["Maan"]    = 41000;
    cities["Karak"]   = 32216;
    cities["Zarqa"]   = 1365000;
    
    // for every (string, int) pair in the cities map
    // print the city and the population of the city
    for (pair<string, int> city_pop : cities)
        cout << city_pop.first << " : " << city_pop.second << endl;

    return 0;
} 
```
As you can see, every element in the `map` is a `pair`, where the key is the `first` and the value is the `second` in this pair.

You might have also noticed that iterating through the `map` gives the keys in ascending order.
