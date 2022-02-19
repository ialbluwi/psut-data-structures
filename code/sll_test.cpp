#include "int_sll.h"

#include<iostream>
using std::cout;
using std::endl;

int main() {
    List list1;

    for (int i = 0; i < 5; i++) {
        list1.add_to_head(i);
        list1.add_to_tail(i);
    }
    list1.print();
    cout << endl;
    // should print: [4, 3, 2, 1, 0, 0, 1, 2, 3, 4]


    for (int i = 0; i < 2; i++) {
        list1.remove_head();
        list1.remove_tail();
    }
    list1.print();
    cout << endl;
    // should print: [2, 1, 0, 0, 1, 2]

    return 0;
}
