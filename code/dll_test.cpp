#include "dll.h"
#include <iostream>
using std::string;
using std::to_string;
using std::cout;
using std::endl;



int main() {
    DLList<int> int_list;
    for (int i = 0; i < 10; i++)
        int_list.add_to_head(i);
    cout << int_list << endl;
    // should print [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]


    DLList<string> str_list;
    string str = "Hello ";
    for (int i = 0; i < 4; i++)
        str_list.add_to_tail(str + to_string(i));
    cout << str_list << endl;
    // should print [Hello 0, Hello 1, Hello 2, Hello 3]


    DLList<string> str_list2 = str_list;
    str_list.append(str_list2);
    cout << str_list << endl;
    // should print [Hello 0, Hello 1, Hello 2, Hello 3, Hello 0, Hello 1, Hello 2, Hello 3]


    string key = "Hello 0";
    while (str_list.contains(key))
        str_list.remove(key);
    cout << str_list << endl;
    // should print [Hello 1, Hello 2, Hello 3, Hello 1, Hello 2, Hello 3]

    return 0;
}