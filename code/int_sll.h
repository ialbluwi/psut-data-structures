#pragma once

#include<iostream>
using std::ostream;

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

    bool contains(int val) const;
    int  get_at(int index) const;
    
    void add_to_head(int val);
    void add_to_tail(int val);
    
    void remove_head();
    void remove_tail();
    bool remove(int val);

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
    Node* del_node = head;

    if (is_empty())
        return;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else
        head = del_node->next;

    delete del_node;
}


void List::remove_tail()
{
    if (is_empty())
        return;

    Node* del_node = tail;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node* curr = head;
        while (curr->next != tail)
            curr = curr->next;

        tail = curr;
        tail->next = nullptr;   
    }

    delete del_node;
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


int List::get_at(int index) const {
    if (is_empty() || index < 0)    
        throw "Invalid argument in function get_at(int)";
    
    int count = 0;
    Node* curr = head;
    
    while (count != index && curr != nullptr) {
        curr = curr->next;
        count++;
    }
            
    if (curr != nullptr)
        return curr->val;
    else
        throw "Invalid argument in function get_at(int)";
}


ostream& operator<<(ostream& out, const List& list) {
    out << "[";

    Node* curr = list.head_node();
    while (curr != nullptr) {
        out << curr->val;
        if (curr->next != nullptr)
            out << ", ";
        curr = curr->next;
    }
    out << "]";

    return out;
}
