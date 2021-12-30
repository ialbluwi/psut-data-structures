#pragma once

#include "queue_dll.h"
#include "stack_dll.h"


template <class T>
class BST;

template <class T>
class BSTNode
{
public:
    BSTNode(const T& val, BSTNode* left, BSTNode* right);
    T get_val() const { return val; }
    BSTNode* get_left() const { return left; }
    BSTNode* get_right() const { return right; }

private:
    T val;
    BSTNode* left;
    BSTNode* right;

    friend class BST<T>;
};

template <class T>
BSTNode<T>::BSTNode(const T& val,
                    BSTNode* left,
                    BSTNode* right)
{
    this->val = val;
    this->left = left;
    this->right = right;
}


// A binary search tree (BST) class to store elements of a generic type T
template <class T>
class BST
{
public:
    BST();
    BST(const BST& other);
    ~BST();
    
    bool is_empty() const;
    bool contains(const T& val) const;

    T max() const;
    T min() const;
    T remove_max();
    T remove_min();

    void insert(const T& val);        
    bool remove(const T& val);
    void clear();
        
    DLList<T> elements() const;
    DLList<T> elements_level_ordered() const;
    BSTNode<T>* get_root() const { return root; }

    BST& operator=(const BST& other);

private:
    BSTNode<T> *root;

    void copy_from(BSTNode<T>* node);
    void elements(DLList<T>& result, BSTNode<T>* node) const;
    bool contains(const T& val, BSTNode<T>* node) const;

    void del_single(BSTNode<T>* ptr, BSTNode<T>* prev);
    void del_double(BSTNode<T>* node);
    
    void clear(BSTNode<T>* node);
};



template <class T>
BST<T>::BST()
{
    root = nullptr;
}

// uses pre-order traversal
template <class T>
void BST<T>::copy_from(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    
    insert(node->val);
    copy_from(node->left);
    copy_from(node->right);
}

template <class T>
BST<T>::BST(const BST<T>& other) {
    root = nullptr;
    copy_from(other.root);
}


template <class T>
BST<T>::~BST()
{
    clear();
}

template <class T>
bool BST<T>::is_empty() const
{
    return root == nullptr;
}


// Iterative implementation of searching in the tree.
// ---- Asymptotic Complexity:
//         * Best case: O(1) If the value is at the root.
//         * Worst case: O(height), where the height is O(logn) in balanced 
//                       trees and can be as bad as O(n) in non-balanced trees.
template <class T>
bool BST<T>::contains(const T& val) const
{
    BSTNode<T>* node = root; // always start the search from the root
    
    while(node != nullptr) {
        // If the current node has the value we are looking for
        if (val == node->val) 
            return true;

        // If the value that we are looking for is smaller than the 
        // value of the current tree node, go left; else, go right
        if(val < node->val)
            node = node->left;
        else
            node = node->right;
    }

    // If the loop completes, node is necessarily a null pointer,
    // which means that val was not found in the tree
    return false; 
}

// Recursive implementation of search.
// In a recursive implementation of the contains() function, 
// the public contains() function will call the private recursive 
// contains() function as follows:

// bool BST<T>::contains(const T& x)
// {
//      return contains(x, root);
// }

// x is the value that we are looking for
// node is the root of the sub-tree that we are searching in.
// Initially node is the root of the entire tree.
// Then the recursion will be limiting the search to
// smaller and smaller sub-trees 

// The asymptotic complexity of the recursive and the iterative search functions
// are the same. In some cases, a recursive function is more readable and easier 
// to implement than its iterative equivalent. However, recursion requires more
// time to execute than loops due to the high cost of function calls.
template <class T>
bool BST<T>::contains(const T& val, BSTNode<T>* node) const
{
    // if a nullptr is reached, val does not exist in the tree
    if (node == nullptr)
        return false;

    // search value is found in the current node
    if (val == node->val)
        return true;

    // search in either the left sub-tree or the right sub-tree, 
    // depending on the value of val  
    if (val < node->val)
        return contains(val, node->left);
    else
        return contains(val, node->right);
}


// inserts the given val into the tree if it is not already in the tree.
// ---- Asymptotic Complexity:
//         * Best case: O(1) if the value is already in the root or if 
//                      insertion happens to the left or right of the root. 
//         * Worst case: O(height), where the height is O(logn) in balanced 
//                       trees and can be as bad as O(n) in non-balanced trees.
template <class T>
void BST<T>::insert(const T& val)
{
    // if the tree is empty, the root needs to point at the new node.
    if (is_empty()) {
        root = new BSTNode<T>(val, nullptr, nullptr);
        return;
    }

    BSTNode<T>* curr = root;
    BSTNode<T>* prev = nullptr;

    // Loop to search for the right position for val
    while(curr != nullptr) {
        prev = curr;
        if (val < curr->val)
            curr = curr->left;
        else if (val > curr->val)
            curr = curr->right;
        else
            return;
    }

    // When the loop terminates, curr will always be null.
    // prev will be at the node where insertion should happen.     

    // Create a new node with null children, because we always 
    // insert a LEAF node. There is no insertion in the middle
    // of the tree
    BSTNode<T>* new_node = new BSTNode<T>(val, nullptr, nullptr); 

    // If the inserted new node is smaller than its parent (prev), set the
    // the left pointer in the parent to the new node. Otherwise,
    // set the right pointer in the parent to the new node.
    if (val < prev->val)
        prev->left = new_node;
    else
        prev->right = new_node;
}

// Breadth-first traversal
template <class T>
DLList<T> BST<T>::elements_level_ordered() const
{
    DLList<T> result;

    if (root == nullptr) 
        return result;

    // a queue of pointers to BSTNode objects.
    QueueDLL<BSTNode<T>*> queue;
    BSTNode<T>* node = root;
    queue.enqueue(node);

    while (!queue.is_empty()) {
        // Take a node out of the queue, process it and then insert 
        // its children into the queue.
        node = queue.dequeue();
        result.add_to_tail(node->val);

        if (node->left != nullptr)
            queue.enqueue(node->left);
        if (node->right != nullptr)
            queue.enqueue(node->right);
    }

    return result;
}

// returns the tree elements in-order
template <class T>
DLList<T> BST<T>::elements() const
{
    DLList<T> result;
    elements(result, root);
    return result;
}

// recursive helper version: returns the elements in-order
template <class T>
void BST<T>::elements(DLList<T>& result, BSTNode<T>* node) const
{
    if (node == nullptr) 
        return;

    elements(result, node->left);

    // Process the node after processing its left subtree 
    // and before processing its right subtree 
    result.add_to_tail(node->val);
    
    elements(result, node->right);
}



// Deletes from the tree the node with the given value.
// ---- Asymptotic complexity:
//      The remove() function includes two steps: a search step + a delete step.
//      
//      - The search step is O(height) in the worst case and O(1) in the best 
//      case as explained in the search function.
//
//      - The delete step may be O(1) or O(height) depending on whether there
//      is a search for a replacement or not and where the replacement is found.
//      Search for a replacement is done only if the deleted node has two children.
//      
//      Examples: 
//          - If the node to be deleted is at the root and has two children, the
//          search for the deleted node itself will be O(1) but the delete 
//          operation (search for a replacement then copy) will be O(height).
//
//          - If the node to be deleted is a leaf node, then the search for the
//          deleted node will be O(height) and deletion will be O(1) 
//          (no replacement is needed).
//
//          - If the node to be deleted is the root node and has a single
//          child, the search for the deleted node will be O(1) and 
//          deletion will be O(1) as well, because there will be no search for
//          a replacement.
//
//      Therefore, the delete function is O(height) in the worst case and O(1) 
//      in the best case.
template <class T>
bool BST<T>::remove(const T& val)
{
    BSTNode<T>* node = root;
    BSTNode<T>* prev = nullptr;

    // This loop searches for the node to be deleted 
    while (node != nullptr) {
        if (node->val == val)
            break;
        
        prev = node;
        if (val < node->val)
            node = node->left;
        else
            node = node->right;
    }
    
    // if val is not found, return false without deleting anything
    // (this covers the case of an empty tree)
    if (node == nullptr)
        return false;
    
    // if the node to be deleted has 0 or 1 children, 
    // call del_single() else call del_double()
    if (node->left == nullptr || node->right == nullptr)
        del_single(node, prev);
    else
        del_double(node);
    
    return true;
}


// Deletes a node with at most one child.
// This function is O(1) in the best and worst case.
template <class T>
void BST<T>::del_single(BSTNode<T>* ptr, BSTNode<T>* prev)
{
    // if the node to be deleted is the root
    if (ptr == root) {
        // the new root becomes the child that is not null.
        // if both children are null, the root becomes null.
        if (root->left != nullptr)
            root = root->left;
        else
            root = root->right;
    
    } 
    // if the node to be deleted is the left child of its parent,
    // set the parent's left child to the only child of the deleted node
    // or to null if it has no children
    else if (ptr == prev->left) {
        if (ptr->right != nullptr)
            prev->left = ptr->right;
        else
            prev->left = ptr->left;
    
    }  
    // if the node to be deleted is the right child of its parent,
    // set the parent's right child to the only child of the deleted node
    // or to null if it has no children
    else {
        if (ptr->right != nullptr)
            prev->right = ptr->right;
        else
            prev->right = ptr->left;
    }
    
    delete ptr;
}


// Deletes a node with exactly two children.
// This function is O(height) in the worst case and O(1) in the best case.
template <class T>
void BST<T>::del_double(BSTNode<T>* node)
{
    // the replacement will be the largest node in the left subtree.
    // So, start searching for a replacement by going left
    BSTNode<T>* rep = node->left; 
    BSTNode<T>* prev = node;
    
    // keep going right until a node with no right is reached.
    // The largest node in the left subtree is the rightmost 
    // node in the left subtree.
    while (rep->right != nullptr) {
        prev = rep;
        rep = rep->right;
    }
    
    // copy the value of the replacement into the node to be deleted 
    node->val = rep->val;

    // delete the replacement node using del_single, because that
    // node does not have a right child.
    del_single(rep, prev);
}


template <class T>
void BST<T>::clear()
{
    clear(root);
    root = nullptr;
}

// Deleting nodes is best done in post-order, because we should not
// delete a node until we have deleted its left and its right.  
template <class T>
void BST<T>::clear(BSTNode<T>* node)
{
    if (node == nullptr) 
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}


// returns the maximum element in the tree.
// ---- Asymptotic Complexity:
//          * Best Case: O(1) if the root is the maximum.
//          * Worst Case: O(n) if the tree is a right-leaning chain. 
template <class T>
T BST<T>::max() const {
    if (is_empty())
        throw "Attempting to retrieve the max value in an empty tree";

    BSTNode<T>* curr = root;
    while (curr->right != nullptr)
        curr = curr->right;

    return curr->val;
}

// returns the minimum element in the tree.
// ---- Asymptotic Complexity:
//          * Best Case: O(1) if the root is the minimum.
//          * Worst Case: O(n) if the tree is a left-leaning chain. 
template <class T>
T BST<T>::min() const {
    if (is_empty())
        throw "Attempting to retrieve the min value in an empty tree";

    BSTNode<T>* curr = root;
    while (curr->left != nullptr)
        curr = curr->left;

    return curr->val;
}

// removes and returns the maximum value in the tree.
template <class T>
T BST<T>::remove_max() {
    if (is_empty())
        throw "Attempting to remove the max value from an empty tree";

    BSTNode<T>* curr = root;
    BSTNode<T>* prev = nullptr;
    while (curr->right != nullptr) {
        prev = curr;
        curr = curr->right;
    }

    T val = curr->val;
    del_single(curr, prev);
    return val;
}

// removes and returns the minimum value in the tree.
template <class T>
T BST<T>::remove_min() {
    if (is_empty())
        throw "Attempting to remove the min value from an empty tree";

    BSTNode<T>* curr = root;
    BSTNode<T>* prev = nullptr;
    while (curr->left != nullptr) {
        prev = curr;
        curr = curr->left;
    }

    T val = curr->val;
    del_single(curr, prev);
    return val;
}


// copy assignment
template <class T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{
    // Guard against self assignment
    if (this == &other)
        return *this;
 
    clear();
    copy_from(other.root);

    return *this;
}