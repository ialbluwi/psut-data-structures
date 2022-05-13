#include <iostream>
using namespace std;

class ArrayList
{
public:
	ArrayList(int capacity);
	ArrayList(const ArrayList& other);
	~ArrayList();

	bool is_empty() const;
	bool is_full() const;
	int size() const;

	void add_front(int val);
	void add_back(int val);
	
	void remove_front();
	void remove_back();
	bool remove(int val);
	void clear();

	int search(int val) const;
	int at(int i) const;

	ArrayList& operator=(const ArrayList& other);
	friend ostream& operator<<(ostream& out, const ArrayList& list);

private:
	int* data;
	int capacity;
	int last    // The index of the last element in the ArrayList. We are
	            // interested only in the values that are stored between 0
                // and last (inclusive).

	void shif_left(int i);
	void shift_right(int i);
	void resize(int new_size);
};


// Constructor. Creates a new array of size "capacity".
ArrayList::ArrayList(int cap)
{
	capacity = cap;
	data = new int[capacity];
	last = -1;
}

ArrayList::ArrayList(const ArrayList& other) {
	data = nullptr;
	*this = other;
}

ArrayList& ArrayList::operator=(const ArrayList& other) {
	if (this == &other) // avoid self-assignment
		return *this;

	delete [] data;
	data = new int[other.capacity];

	capacity = other.capacity;
	last = other.last;

	for (int i = 0; i <= last; i++)
		data[i] = other.data[i];

	return *this;
}


// Destructor.
ArrayList::~ArrayList()
{
	delete [] data;
}


// Checks if the list is empty by looking at the index of the last element in
// the array. An index of -1 means that the list is empty.
bool ArrayList::is_empty() const
{
	return last == -1;
}


// Checks if the number of elements stored in the ArrayList is equal to the 
// allocated capacity or not.
bool ArrayList::is_full() const
{
	return last+1 == capacity;
}

// Returns the number of elements currently in the list
int ArrayList::size() const
{
	return last+1;
}


// Elements in an array cannot be physically deleted; the array will remain in
// memory unless it is de-allocated using the "delete" operator, which will make
// the array inaccessible.
// Instead, we only set the last index to -1, which means that we are no more
// interested in any element currently stored in the array.
void ArrayList::clear()
{
	last = -1;
}


// Shifts all of the elements between "startIndex" and "last" (inclusive)
// towards the end of the list. 
// 
// For example: shif_left(2)
//
// Before:  *   *   *   *   *
// [A | B | C | D | E | F | G |   |   |   ]
//  0   1   2   3   4   5   6   7   8   9
//          ^               ^
//      startIndex        last
//
// After:       *   *   *   *   *
// [A | B | C | C | D | E | F | G |   |   ]
//  0   1   2   3   4   5   6   7   8   9
//          ^                   ^
//      startIndex             last
// 
// This function is used in order to create a vacant place at "startIndex", 
// which can be used to insert a new value.
// 
// No validity checks are made on the passed parameter since this is a private
// function, which is called from public functions with proper validity checks.
//
void ArrayList::shif_left(int start_index)
{
	int i;

	for(i= last; i>= start_index; i--)
		data[i+1] = data[i];
	last++;
}


// Shifts all of the elements between "startIndex" and "last" (inclusive)
// towards the beginning of the list. 
// 
// For example: shif_left(2)
//
// Before:
//          *   *   *   *   * 
// [A | B | C | D | E | F | G |   |   |   ]
//  0   1   2   3   4   5   6   7   8   9
//          ^               ^
//       startIndex	       last
//
// After:
//      *   *   *   *   *
// [A | C | D | E | F | G | G |   |   |   ]
//  0   1   2   3   4   5   6   7   8   9
//                      ^
//                    last
// 
// This function is used in order to delete the element at "startIndex - 1", 
// which can be used to insert a new value.
// 
// No validity checks are made on the passed parameter since this is a private
// function, which is called from public functions with proper validity checks.
//
void ArrayList::shift_right(int start_index)
{
	int i;

	for(i=start_index; i<=last; i++)
		data[i-1] = data[i];
	last--;
}


// Adds an element at index 0.
void ArrayList::add_front(int val)
{
	if (is_full())
		resize(capacity * 2);
	
	shif_left(0);
	data[0] = val;
}


// Adds an element at the end of the list.
void ArrayList::add_back(int val)
{
	if (is_full())
		resize(capacity * 2);
		
	last++;
	data[last] = val;
}


// Deletes the element at index 0.
void ArrayList::remove_front()
{
	if (is_empty() == true) {
		cout << "Can't delete from an empty list" << endl;
		return;
	}
	shift_right(1);
}


// Deletes an element from the end of the list.
void ArrayList::remove_back()
{
	if (is_empty()) {
		cout << "Can't delete from an empty list" << endl;
		return;
	}
	last--;
}


// Searches for the given value and deletes it if it is found.
bool ArrayList::remove(int val)
{
	int index = search(val);

	if (index == -1) 
		return false;

	shift_right(index+1);
	return true;
}


// Performs Linear search and returns the index of the value or -1 if the value
// is not found.
int ArrayList::search(int val) const
{
	int i;

	if (is_empty() == true)
		return -1;
	for (i=0; i <= last; i++)
	{
		if (data[i] == val)
			return i;
	}
	return -1;
}



// Returns the value at the given index. If the given index is less than 0, the
// element at 0 is returned. If the index is more than "last", the last element
// is returned.
int ArrayList::at(int index) const
{
	if (index < 0)
		return data[0];
	else if (index > last)
		return data[last];
	else
		return data[index];

}



// resizes the current array according to "new_size".
// A new array is created with capacity = old-capacity * new_size.
// Elements in the old array are copied into the new array.
void ArrayList::resize(int new_size)
{
	int i;
	int newCap = new_size;
	int* newData = new int[newCap];

	for(i=0; i<= last; i++) // copy old into new
		newData[i] = data[i];

	delete [] data; 
	data = newData;
	capacity = newCap;
}



ostream& operator<<(ostream& out, const ArrayList& list) {
	out << "[";
	for (int i = 0; i <= list.last; i++) {
		out << list.data[i];
		if (i != list.last)
			out << ", ";
	}
	out << "]";

	return out;
}


int main() {
	ArrayList list(4);

	for (int i = 0; i < 15; i++) {
		list.add_back(i);
		list.add_front(i);
	}

	cout << "Before deletion: " << endl;
	cout << "Size: " << list.size() << endl;
	cout << "Data: " << list << endl << endl;

	for (int i = 0; i < 5; i++) {
		list.remove_back();
		list.remove_front();
	}

	cout << "After deletion: " << endl;
	cout << "Size: " << list.size() << endl;
	cout << "Data: " << list << endl << endl;

	ArrayList list2(list);
	cout << endl << "List2: " << list2 << endl;

	for (int i = 0; i < 5; i++)
		list2.add_back(1);

	cout << "list1: " << list << endl;
	cout << "list2: " << list2 << endl;

	return 0;
}