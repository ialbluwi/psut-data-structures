#include <iostream>
#include "bst.h"
using namespace std;

template <class T> int tree_height(BSTNode<T>* node);
template <class T> int size(BSTNode<T>* node);
template <class T> int count_leafs(BSTNode<T>* node);


int main() {
    BST<int> bst;
    for (int i = 0; i < 10; i++)
        bst.insert(rand() % 10);

    cout << "BST elements in-order:       " << bst.elements() << endl;
    cout << "BST elements in level order: " << bst.elements_level_ordered() 
         << endl << endl;

    cout << "Max: " << bst.max() << endl;
    cout << "Min: " << bst.min() << endl << endl;

    cout << "Height:          " << tree_height(bst.get_root()) << endl;
    cout << "Number of nodes: " << size(bst.get_root()) << endl;
    cout << "Number of leafs: " << count_leafs(bst.get_root()) << endl;
    
    return 0;
}

template <class T>
int tree_height(BSTNode<T>* node) {
    if (node == nullptr)
        return -1;

    return 1 + max(tree_height(node->get_left()), 
                   tree_height(node->get_right()));
}

template <class T>
int size(BSTNode<T>* node) {
    if (node == nullptr)
        return 0;

    return 1 + size(node->get_left()) + size(node->get_right());
}

template <class T>
int count_leafs(BSTNode<T>* node) {
    if (node == nullptr)
        return 0;
    
    if (node->get_left() == nullptr && node->get_right() == nullptr)
        return 1;

    return count_leafs(node->get_left()) + 
           count_leafs(node->get_right());
}