#include <iostream>
#include "stack_dll.h"
#include "queue_array.h"

using namespace std;

void print(QueueArray<int>& queue);
void reverse(QueueArray<int>& queue);

int main() {
    QueueArray<int> queue(2);

    for (int i = 0; i < 20; i++)
        queue.enqueue(i);

    print(queue);
    cout << endl;

    reverse(queue);
    print(queue);
    cout << endl;

    return 0;
}

void print(QueueArray<int>& queue) {
    for (int i = 0; i < queue.get_size(); i++) {
        cout << queue.get_first() << " ";
        queue.enqueue(queue.dequeue());
    }
}

void reverse(QueueArray<int>& queue) {
    StackDLL<int> stack;
    
    while (!queue.is_empty())
        stack.push(queue.dequeue());
    
    while (!stack.is_empty())
        queue.enqueue(stack.pop());
}
