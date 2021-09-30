Binary Search Trees Exercises
=====================

*These exercises are based on* [`bst.h`]().

## Contents

1. `int count() const`
2. `int count_leafs() const`
3. `void compute_heights()`
4. `void compute_depths()`
5. `bool is_full() const`
6. `bool is_balanced() const`
7. `int count_last_level() const`
8. `void prune()`
9. `void update_counts()`
10. `int rank(const T& val) const`



Exercise 1
----------

Implement the following member function of class `BST`, which returns the number of nodes in the tree.

```cpp
int count() const;
```

#### *Solution* # 1

```cpp
template <class T>
int BST<T>::count(BSTNode<T>* node) const 
{
    if (node == nullptr)
        return 0;
    return 1 + count(node->left) + count(node->right);
}

template <class T>
int BST<T>::count() const 
{
    return count(root);
}
```

#### *Solution* # 2

```cpp
template <class T>
int BST<T>::count() const 
{
    if (is_empty())
        return 0;
  
    int counter = 0;
    QueueDLL<BSTNode<T>*> queue;
    queue.enqueue(root);
  
    while (!queue.is_empty()) {
        counter++;
        BSTNode<T>* node = queue.dequeue();
        if (node->left != nullptr)
            queue.enqueue(node->left);
        if (node->right != nullptr)
            queue.enqueue(node->right);
    }
  
    return counter;
}
```



## Exercise 2

Implement the following member function of class `BST`, which returns the number of leafs in the BST.

```cpp
int count_leafs() const;
```

#### *Solution* # 1

```cpp
template <class T>
int BST<T>::count_leafs(BSTNode<T>* node) const 
{
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    return count_leafs(node->left) + count_leafs(node->right);
}

template <class T>
int BST<T>::count_leafs() const 
{
    return count_leafs(root);
}
```

#### *Solution* # 2

Use breadth-first traversal as in ***solution* # 2** for **Exercise 1**.



## Exercise 3

Assume that the `BSTNode` class has two data members for storing the `depth` of the node and the `height` of the node. 

```cpp
template <class T>
class BSTNode {
  // ... public members ...
private:
    T val;
    BSTNode* left;
    BSTNode* right;
    int depth;
    int height;
};
```

Implement the following member function in class `BST`, which computes the height of each node in the tree and stores it in the data member `height`.

```cpp
void compute_heights();
```

#### *Solution*

```cpp
template <class T>
void BST<T>::compute_heights(BSTNode<T>* node) 
{
    if (node == nullptr)
        return;
  
    compute_heights(node->left);
    compute_heights(node->right);
  
    int left_height = -1;
    if (node->left != nullptr)
        left_height = node->left->height;
  
    int right_height = -1;
    if (node->right != nullptr)
        right_height = node->right->height;
  
    node->height = 1 + max(left_height, right_height);
}

template <class T>
void BST<T>::compute_heights() 
{
    compute_heights(root);
}
```

#### 

## Exercise 4

Using the `BSTNode` class defined in **Exercise 3**, implement the following member function in class `BST`, which computes the depth of each node in the tree and stores it in the data member `depth`.

```cpp
void compute_depths();
```

#### *Solution* # 1

```cpp
template <class T>
void BST<T>::compute_depths(BSTNode<T>* node, BSTNode<T>* parent) 
{
    if (node == nullptr)
        return;
  
    if (parent == nullptr)
        node->depth = 0;
    else
        node->depth = parent->depth + 1;
    
    compute_depths(node->left, node);
    compute_depths(node->right, node);
}

template <class T>
void BST<T>::compute_depths() 
{
    compute_depths(root, nullptr);
}
```

#### *Solution* # 2

```cpp
template <class T>
void BST<T>::compute_depths() 
{
    if (is_empty())
        return;
  
    QueueDLL<BSTNode<T>*> queue;
    queue.enqueue(root);
    root->depth = 0;
  
    while (!queue.is_empty()) {
        BSTNode<T>* node = queue.dequeue();
    
        if (node->left != nullptr) {
            node->left->depth = node->depth + 1;
            queue.enqueue(node->left);
        }
        if (node->right != nullptr) {
            node->right->depth = node->depth + 1;
            queue.enqueue(node->right);
        }
    }
}
```



## Exercise 5

Using the `BSTNode` class defined in **Exercise 3**, implement the following member function of class `BST`, which checks if the tree is a full tree. You can assume that `compute_heights()` was already called.

```cpp
bool is_full() const;
```

#### *Solution* # 1

```cpp
template <class T>
bool BST<T>::is_full() const 
{
    return is_full(root);
}

template <class T>
bool BST<T>::is_full(BSTNode<T>* node) const
{
    if (node == nullptr)
        return true;
    
    // Check if the heights of the children are the same.
    int left_height = -1;
    int right_height = -1;
    
    if (node->left != nullptr)
        left_height = node->left->height;
    if (node->right != nullptr)
        right_height = node->right->height;
    
    if (left_height != right_height)
        return false;
    
    // Check for the left child and for the right child.
    return is_full(node->left) && is_full(node->right);
}
```

#### *Solution* # 2

```cpp
template <class T>
bool BST<T>::is_full() const 
{
    if (root == nullptr)
        return true;
    
    if (count() == (pow(2.0, root->height+1) - 1))
        return true;
    else
        return false;
}
```



## Exercise 6

Using the `BSTNode` class defined in **Exercise 3**, implement the following member function of class `BST`, which checks if the tree is a balanced tree. You can assume that `compute_heights()` was already called. 

```cpp
bool is_balanced() const;
```

#### *Solution* # 1

```cpp
template <class T>
bool BST<T>::is_balanced() const 
{
    compute_heights();
    return is_balanced(root);
}

template <class T>
bool BST<T>::is_balanced(BSTNode<T>* node) const
{
    if (node == nullptr)
        return true;
    
    // Check if the heights of the children are the same.
    int left_height = -1;
    int right_height = -1;
    
    if (node->left != nullptr)
        left_height = node->left->height;
    if (node->right != nullptr)
        right_height = node->right->height;
    
    if (abs(left_height - right_height) > 1)
        return false;
    
    // Check for the left child and for the right child.
    return is_balanced(node->left) && is_balanced(node->right);
}
```

#### *Solution* # 2

Use breadth-first traversal.



## Exercise 7

Using the `BSTNode` class defined in **Exercise 3**, implement the following member function of class `BST`, which counts the number of nodes in the last level in the tree.

```cpp
int count_last_level() const;
```

#### *Solution*

1. Call `compute_heights()` and `compute_depths()`.
2. The `depth` of the last level is the `height` of the tree (the `height` of the `root`).
3. Perform any traversal (BFT, in-order, post-order, pre-order) and count nodes whose `depth` data member equals to the `height` of the `root`.



## Exercise 8

Implement the following member function of class `BST`, which deletes all the leaf nodes from the tree.

```cpp
void prune();
```

#### *Solution*

```cpp
template <class T>
void BST<T>::prune() {
    root = prune(root);
}

template <class T>
BSTNode<T>* BST<T>::prune(BSTNode<T>* node) {
    if (node == nullptr)
        return nullptr;
  
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
    }
  
    node->left = prune(node->left);
    node->right = prune(node->right);
    return node;
}
```



## Exercise 9

Assume that the `BSTNode` class has a data member `count` for storing the number of nodes in the subtree rooted at that node. The following figure illustrates the idea.

<img src="counts.png" alt="Screen Shot 2021-09-30 at 8.09.40 AM" style="width:40%; display: block; margin-left: auto; margin-right: auto;" />

```cpp
template <class T>
class BSTNode {
  // ... public members ...
private:
    T val;
    BSTNode* left;
    BSTNode* right;
    int count;
};
```

Implement the following member function in class `BST`, which updates the `count` data member in every node in the tree.

```cpp
void store_counts();
```

#### *Solution*

```cpp
template <class T>
void BST<T>::update_counts(BSTNode<T>* node) 
{
    if (node == nullptr)
        return;
  
    update_counts(node->left);
    update_counts(node->right);
  
    int left_count = 0;
    if (node->left != nullptr)
    left_count = node->left->count;
  
    int right_count = 0;
    if (node->right != nullptr)
    right_count = node->right->count;    
  
    node->count = 1 + left_count + right_count;
}

template <class T>
void BST<T>::update_counts() 
{
    update_counts(root);
}
```

 

## Exercise 10

Using the `BSTNode` class defined in **Exercise 9** and assuming that `update_counts()` was called, implement the following member function of class `BST`, which returns the ***rank*** of the given value in the tree. The ***rank*** of a value ***x*** is the number of values in the tree that are ***less than x***.

```cpp
int rank(const T& val) const;
```

Note that this can be easily solved in `O(n)` if we call the `elements()` function on the tree and then iterate over the returned ordered list of elements.

The goal of this exercise is to make use of the node counts to achieve a running time of `O(log n)` if the tree is balanced.

#### *Solution*

```cpp
// a helper function
template <class T>
int BST<T>::get_count(BSTNode<T>* node) const {
    if (node == nullptr) return 0;
    else return node->count;
}

template <class T>
int BST<T>::rank(const T& val) const 
{
    return rank(val, root);
}

template <class T>
int BST<T>::rank(const T& val, BSTNode<T>* node) const
{
    if (node == nullptr)
        return 0;
    
    if (val == node->val)
        return get_count(node->left);
    else if (val < node->val)
        return rank(val, node->left);
    else
        return 1 + get_count(node->left) + rank(val, node->right);
}
```
