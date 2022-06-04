
/*
 * Required Operations:
 * --------------------
 *
 * A) Stacks:
 * 		1.	push
 * 		2.	pop
 * 		3.	top
 * 		4. 	empty
 * 		5.	size
 *
 *	B) Queues:
 *		1.	push
 *		2.	pop
 *		3.	back
 *		4.	front
 *		5.	empty
 *		6.	size
 *
 *	C) Lists:
 *		1.	push_back
 *		2.	pop_back
 *		3.	push_front
 *		4.	pop_front
 *		5.	back
 *		6.	front
 *		7. 	empty
 *		8.	size
 *		9.	clear
 *
 *	D)	Vectors:
 *		1.	push_back
 *		2.	pop_back
 *		3.	empty
 *		4.	size
 *		5.	back
 *		6.	front
 *		7.	clear
 *		8.	access elements using []
 *
 *	E)	Iterators:
 *		1. 	Define a list iterator.
 *		2.	Move the list iterator forward and backward using ++ and --.
 *		3.	Access the value pointed to by the iterator using *
 *
 *		4.	Define a vector iterator.
 *		5.	Move the vector iterator forward and backward using ++, --, +=, -=.
 *		6.	Access the values using * or *(iterator +/- step).
 *
 *		7.	Know how to use the two iterators: begin() and end().
 *		
 *		8.  Know how to use Range-based for loops
 *
 *	F)	Priority Queues:
 *		1.	push
 *		2.	pop
 *		3.	top
 *		4.	empty
 *		5.	size
 *
 *	G)	Algorithms:
 *		1.	Sort
 *		2.	Find
 */


#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


int main() {
	
	// Example 1: 	Insert elements into a stack and then use a queue to reverse
	// 				the stack.
	cout << "Printing a reversed stack:" << endl;
	
	stack<int> myStack;
	
	for (int i=0; i<10; i++)
		myStack.push(i);
	
	queue<int> myQueue;
	
	while (!myStack.empty()) {
		int x = myStack.top();
		myStack.pop();
		
		myQueue.push(x);
	}
	
	while (!myQueue.empty()) {
		int x = myQueue.front();
		myQueue.pop();
		
		myStack.push(x);
	}
	
	while (!myStack.empty()) {
		int x = myStack.top();
		myStack.pop();
		
		cout << x << ", ";
	}
	//--------------------------------------------------------------------------
	
	
	
	// Example 2:	Insert random numbers into a priority queue and then output
	//				them in descending order.
	cout << endl << endl << "Printing the contents of a priority queue: \n";
	
	priority_queue<int> pq; // define a max-priority queue
	// to define a min-priority queue use:
	// priority_queue<int, vector<int>, std::greater<int>> pq;
	
	for (int i=0; i<10; i++) {
		int x = rand() % 10;
		pq.push(x);
	}
	
	while (!pq.empty()) {
		int x = pq.top();
		pq.pop();
		
		cout << x << ", ";
	}
	//--------------------------------------------------------------------------
	
	
	
	
	// Example 3:	Using lists and list iterators.
	cout << endl << endl << "Printing the contents of a list "
	<< "forwards and backwards: " << endl;
	
	list<int> myList;
	
	// Create the following list:
	// 0 1 2 3 4 5 6 7 8 9
	for (int i = 0; i <= 10; i++)
		myList.push_back(i);
	for (int i = 10; i >= 0; i--)
		myList.push_front(i);
	
	// printing forward
	list<int>::iterator temp;
	for (temp = myList.begin(); temp != myList.end(); temp++)
		cout << *temp << ", ";
	cout << endl;
	
	// printing backward
	temp--;
	for (; temp != myList.begin(); temp--)
		cout << *temp << ", ";
	cout << *temp << endl;

	// printing using the range-based for loop:
	// for (int val : myList)
	// 		cout << val << ", ";
	// cout << endl;
	//--------------------------------------------------------------------------
	
	
	
	
	// Example 4: Using vectors and vector iterators.
	cout << endl << endl << "Printing the contents of a vector using four "
	<< "different ways." << endl;
	
	vector<int> myVector;
	
	for (int i=0; i<10; i++)
		myVector.push_back(i);
	
	
	vector<int>::iterator temp2;
	for (temp2 = myVector.begin(); temp2 != myVector.end(); temp2++)
		cout << *temp2 << ", ";
	cout << endl;
	
	
	for (int i=0; i<myVector.size(); i++)
		cout << *(myVector.begin() + i) << ", ";
	cout << endl;
	
	
	for (int i = 0; i < myVector.size(); i++)
		cout << myVector[i] << ", ";
	cout << endl;


	for (int val : myVector)
			cout << val << ", ";
	cout << endl;
	//--------------------------------------------------------------------------
	
	
	
	
	
	// Example 5: Sorting a vector
	sort(myVector.begin(), myVector.end());
	//--------------------------------------------------------------------------
	
	
	
	
	// Example 6: Removing the duplicates from a stack.
	while (!myStack.empty())
		myStack.pop();
	
	
	cout << "\n\nContents of the stack reversed are: " << endl;
	for (int i = 0; i < 10; i++) {
		int x = rand() % 10;
		cout << x << ", ";
		
		myStack.push(x);
	}
	
	
	myVector.clear();
	while (!myStack.empty()) {
		int x = myStack.top();
		myStack.pop();
		
		if (find(myVector.begin(), myVector.end(), x) == myVector.end())
			myVector.push_back(x);
	}
	
	while (!myVector.empty()) {
		myStack.push(myVector.back());
		myVector.pop_back();
	}
	
	cout << endl << endl << "After removing duplicates: " << endl;
	while (!myStack.empty()) {
		int x = myStack.top();
		myStack.pop();
		
		cout << x << ", ";
	}
	//--------------------------------------------------------------------------
	
	
	
	
	return 0;
}