#include <iostream>
#include "hash_table.h"

using namespace std;

int main() {
    HashTable<int> table1;
    HashTable<int> table2;

    for (int i = 0; i < 20; i++) {
        int val1 = rand() % 20;
        if (!table1.contains(val1))
            table1.insert(val1);

        int val2 = rand() % 20;
        if (!table2.contains(val2))
            table2.insert(val2);
    }

    DLList<int> elements1 = table1.elements();
    cout << "Table 1: " << elements1 << endl;
    cout << "Table 2: " << table2.elements() << endl << endl;

    cout << "Common elements: ";
    DLLNode<int>* curr = elements1.head_node();
    while (curr != nullptr) {
        if (table2.contains(curr->get_val()))
            cout << curr->get_val() << " ";
        curr = curr->get_next();
    }

    return 0;
}