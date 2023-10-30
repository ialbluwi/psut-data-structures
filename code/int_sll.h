#pragma once

#include<iostream>
using std::cout;
using std::string;

class Node {
public:
    int val;
    Node* next;

    Node(int val, Node* next) {
        this->val = val;
        this->next = next;
    }
};


class List {
public:
    List();
    ~List();

    Node* head_node() const;
    Node* tail_node() const;
    bool is_empty() const;
    
    void add_to_head(int val);
    void add_to_tail(int val);
    
    void remove_head();
    void remove_tail();
    bool remove(int val);

    bool contains(int val) const;
    void print() const;

private:
    Node* head;
    Node* tail;
};


List::List()
{
    head = nullptr;
    tail = nullptr;
}


List::~List()
{   
    Node* curr = head;
    Node* del_node;
    
    while (curr != nullptr) {
        del_node = curr;
        curr = curr->next;
        delete del_node;
    }
}


bool List::is_empty() const 
{
    return head == nullptr; 
}

Node* List::head_node() const 
{ 
    return head; 
}

Node* List::tail_node() const 
{ 
    return tail; 
}


void List::add_to_head(int val)
{
    Node* new_node = new Node(val, head);

    head = new_node;
    if (tail == nullptr) 
        tail = new_node;
}


void List::add_to_tail(int val)
{
    Node* new_node = new Node(val, nullptr);

    if (tail == nullptr) 
        head = new_node;
    else 
        tail->next = new_node;
        
    tail = new_node;
}


void List::remove_head()
{
    if (is_empty())
        return;

    Node* temp = head;
    head = head->next;
    delete temp;

    if (head == nullptr)
        tail = nullptr;
}


void List::remove_tail()
{
    if (head == tail) {
        remove_head();
        return;
    }

    Node* prev = head;
    while (prev->next != tail)
        prev = prev->next;

    delete tail;
    tail = prev;
    tail->next = nullptr;
}


bool List::remove(int val)
{
    if (is_empty())
        return false;

    if (val == head->val) {
        remove_head();
        return true;
    }

    if (val == tail->val) {
        remove_tail();
        return true;
    }

    Node* node = head->next;
    Node* pred = head;

    while (node != nullptr) {
        if (node->val == val) {
            pred->next = node->next; 
            delete node;
            return true;
        }

        node = node->next;
        pred = pred->next;
    }
    
    return false;
}


bool List::contains(int val) const
{
    for (Node* curr = head; curr != nullptr; curr = curr->next)
        if (curr->val == val)
            return true;

    return false;
}

void List::print() const 
{
    cout << "[";

    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->val;

        if (curr->next != nullptr)
            cout << ", ";

        curr = curr->next;
    }
    
    cout << "]";
}
