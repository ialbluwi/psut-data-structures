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

// OTHER POSSIBLE IMPLEMENTATIONS:
//
// 1)
// void print(QueueArray<int>& queue) {
//     QueueArray<int> temp(queue);
// 
//     while (!temp.is_empty())
//         cout << temp.dequeue() << " ";
// }
//
// 2)
// void print(QueueArray<int>& queue) {
//     QueueArray<int> temp;
// 
//     while (!queue.is_empty()) {
//         cout << queue.get_first() << " ";
//         temp.enqueue(queue.dequeue());
//     }
//
//     queue = temp;
// }


void reverse(QueueArray<int>& queue) {
    StackDLL<int> stack;
    
    while (!queue.is_empty())
        stack.push(queue.dequeue());
    
    while (!stack.is_empty())
        queue.enqueue(stack.pop());
}
// Note. To reverse a Stack, we can use a Queue
//       following the same logic used for reverseing
//       the queue in the above function.
