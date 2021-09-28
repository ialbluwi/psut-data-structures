#pragma once

#include <iostream>
using std::string;
using std::ostream;

template <class T>
class OrderedDLList;


template <class T>
class DLLNode
{
public:
	DLLNode(const T& val, DLLNode* next, DLLNode* prev);

	T get_val() const { return val; }
	DLLNode* get_next() const { return next; }
	DLLNode* get_prev() const { return prev; }
	
private:
	T val;
	DLLNode* next;
	DLLNode* prev;

	friend class OrderedDLList<T>;
};

template <class T>
DLLNode<T>::DLLNode(const T& val, DLLNode* next, DLLNode* prev)
{
	this->val = val;
	this->next = next;
	this->prev = prev;
}

// An ordered doubly-linked list class
template <class T>
class OrderedDLList {
public:
	OrderedDLList();
	OrderedDLList(const OrderedDLList<T>& other);
	~OrderedDLList();

	bool is_empty() const;
	
	DLLNode<T>* get_head() const;
	DLLNode<T>* get_tail() const;

	void insert(const T& val);
	void merge(const OrderedDLList<T>& other);
	
	void remove_head();
	void remove_tail();
	bool remove(const T& val);
	void clear();	

	bool contains(const T& val) const;
	OrderedDLList& operator=(const OrderedDLList& other);

private:
	DLLNode<T>* head;
	DLLNode<T>* tail;

	void add_to_head(const T& val);
	void add_to_tail(const T& val);
	void append(const OrderedDLList<T>& other);
};


template <class T>
OrderedDLList<T>::OrderedDLList()
{
	head = nullptr;
	tail = nullptr;
}

template <class T>
OrderedDLList<T>::OrderedDLList(const OrderedDLList<T>& other) {
	head = nullptr;
    tail = nullptr;

    append(other);
}

template <class T>
OrderedDLList<T>::~OrderedDLList()
{
	clear();
}

template <class T>
void OrderedDLList<T>::clear()
{
	while (!is_empty())
		remove_head();
}

template <class T>
bool OrderedDLList<T>::is_empty() const
{
	return head == nullptr;
}

template <class T>
void OrderedDLList<T>::add_to_head(const T& val)
{
	DLLNode<T>* new_node = new DLLNode<T>(val, head, nullptr);

	if (head != nullptr)
		head->prev = new_node;

	head = new_node;
	if (tail == nullptr)
		tail = new_node;
}

template <class T>
void OrderedDLList<T>::add_to_tail(const T& val)
{
	DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, tail);

	if (tail != nullptr) //If list is non-empty
		tail->next = new_node;

	tail = new_node;
	if (head == nullptr)
		head = new_node;
}

template <class T>
void OrderedDLList<T>::remove_head()
{
	DLLNode<T>* del_node = head;

	if (is_empty())
		return;

	if (head == tail) // if only one node in the list
		head = tail = nullptr;
	else {
		head = del_node->next;
		head->prev = nullptr;
	}
	delete del_node;
}

template <class T>
void OrderedDLList<T>::remove_tail()
{
	if (is_empty())
		return;

	DLLNode<T>* del_node = tail;

	if (head == tail) // if only one node in the list
		head = tail = nullptr;
	else {
		tail = del_node->prev;
		tail->next = nullptr;	
	}

	delete del_node;
}

template <class T>
bool OrderedDLList<T>::remove(const T& val)
{
	if (is_empty() || val < head->val || val > tail->val)
		return false;

	if (val == head->val) {
		remove_head();
		return true;
	}

	if (val == tail->val) {
		remove_tail();
		return true;
	}

	DLLNode<T>* curr = nullptr;
	DLLNode<T>* pred = nullptr;
	DLLNode<T>* succ = nullptr;

	// traverse list to find the node to be deleted
	for (curr = head->next; curr != nullptr; curr = curr->next) {
		if (curr->val == val) {
			pred = curr->prev;
			succ = curr->next;
			pred->next = curr->next; 
			succ->prev = curr->prev;
			delete curr;
			return true;
		}

		if (val < curr->val)
			return false;
	}

	return false;
}

template <class T>
bool OrderedDLList<T>::contains(const T& val) const
{
	DLLNode<T>* curr;

	for (curr = head; curr != nullptr; curr = curr->next) {
		if (val == curr->val)
			return true;
		if (val < curr->val)
			return false;
	}

	return false;
}

template <class T>
DLLNode<T>* OrderedDLList<T>::get_head() const
{
	return head;
}

template <class T>
DLLNode<T>* OrderedDLList<T>::get_tail() const 
{
	return tail;
}

template <class T>
void OrderedDLList<T>::append(const OrderedDLList& other)
{
	DLLNode<T>* curr;

	for (curr = other.head; curr != nullptr; curr = curr->next)
		add_to_tail(curr->val);
}

// Inserts an element into an ordered doubly-linked list.
// Steps:
//		- If the list is empty, add_to_head() or add_to_tail() can be used.
//		- If the value >= the tail value, use add_to_tail().
//		- If the value <= the head value, use add_to_head().
//		- If none of these cases are true, search for the appropriate place
//		  to insert in the list and preserve the order.
//
//                 pred              succ
//					V				  V
//          +--+-------+--+    +--+-------+--+    +--+-------+--+ 
//          |  |       | *|-X->|  |		  |*-|--->|  |       |*-|--> 
//  ....    |  |  val  |  |    |  |  val  |  |    |  |  val  |  |    ....
//	     <--|-*|       |  |<-X-|* |       |  |<---|-*|       |  |
//          +--+-------+--+	   +--+-------+--+    +--+-------+--+
//                     ^ |       | ^	
//                     | V       V |	
//                    +--+-------+--+     
//                    |  |       |  |
//                    |  |  val  |  |    
//                    |  |       |  |
//                    +--+-------+--+
//                            ^
//                            |
//                         new_node
//
// --- Asymptotic complexity: 
//		* Best Case:	O(1) If the value is <= head or >= tail.
//		* Worst Case:	O(n) If the node is to be added at the node before 
//						the tail.
template <class T>
void OrderedDLList<T>::insert(const T& val)
{
	if (is_empty() || val <= head->val) {
		add_to_head(val);
		return;
	}

	if (val >= tail->val) { 
		add_to_tail(val);
		return;
	}

	// at this point, we know that the list has at least two nodes; otherwise
	// one of the three cases above would have been taken.

	DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, nullptr);
	DLLNode<T>* succ = nullptr;
	DLLNode<T>* pred = nullptr;

	// traverse the list to find the right position for the new node
	for (DLLNode<T>* curr = head; curr != nullptr; curr = curr->next)
		if (val <= curr->val) { // insertion should be before "curr"
			succ = curr;
			pred = curr->prev;
			break;
		}

	// link the new node to its successor and predecessor
	new_node->next = succ;
	new_node->prev = pred;
	succ->prev = new_node;
	pred->next = new_node;
}

// Merges the ordered list "other" into the current list, which is also
// an ordered list. The other list should stay intact and the two
// lists should remain separate lists.
//
// For example:
// If the current list is 1 3 4 5 10. and the other list is: 1 2 3 6.
// After calling this function, the current list becomes: 1 1 2 3 4 5 6 10.
// The other list remains as is.
//
// A simple algorithm to perform this operation is to use the insert() function to insert
// every element in "other" into the current list. This algorithm results in
// an ordered merged list, which is what we want.
// The problem is that if the size of the current list is N and the size of the
// other list is M, this algorithm requires O(N*M) operations.
//
// The following algorithm is O(M+N):
//		- Create a temporary empty list.
//		- Create pointer ptr1 to point to the head of the current list.
//		- Create pointer ptr2 to point to the head of the other list.
//		- Insert the value of the smaller pointer into the temporary list 
//        and move the pointer forward.
//		- keep repeating this until both pointers reach null.
//		- If one of the pointers reaches null first, work will be done on only
//		  the non-null pointer.
//		- Once all of the elements have been added to the temporary list:
//			* clear the current list.
//			* append the temporary list into the current empty list.
template <class T>
void OrderedDLList<T>::merge(const OrderedDLList<T>& other)
{
	if (other.is_empty())
		return;

	if (is_empty()) {
		append(other);
		return;
	}

	OrderedDLList<T> new_list;
	DLLNode<T> *ptr1 = this->head;
	DLLNode<T> *ptr2 = other.head;

	while (ptr1 != nullptr || ptr2 != nullptr) {
		if (ptr2 == nullptr) {
			new_list.add_to_tail(ptr1->val);
			ptr1 = ptr1->next;
		}
		else if (ptr1 == nullptr) {
			new_list.add_to_tail(ptr2->val);
			ptr2 = ptr2->next;
		}
		else if (ptr1->val <= ptr2->val) {
			new_list.add_to_tail(ptr1->val);
			ptr1 = ptr1->next;
		}
		else {
			new_list.add_to_tail(ptr2->val);
			ptr2 = ptr2->next;
		}
	}
	
	clear();
	append(new_list);
}


// copy assignment
template <class T>
OrderedDLList<T>& OrderedDLList<T>::operator=(const OrderedDLList<T>& other)
{
    if (this == &other)
        return *this;
 
    clear();
    append(other);

    return *this;
}


template<class T>
ostream& operator<<(ostream& out, const OrderedDLList<T>& list) {
	out << "[";

	DLLNode<T>* curr = list.get_head_node();
	while (curr != nullptr) {
		out << curr->get_val();
		if (curr->get_next() != nullptr)
			out << ", ";
		curr = curr->get_next();
	}
	out << "]";

	return out;
}

