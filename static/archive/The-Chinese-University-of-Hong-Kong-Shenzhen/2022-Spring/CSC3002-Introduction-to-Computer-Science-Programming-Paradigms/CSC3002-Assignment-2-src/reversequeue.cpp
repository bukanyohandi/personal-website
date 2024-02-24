/*
 * File: reversequeue.cpp
 * ----------------------
 * This file implements the reversequeue.h interface
 */


#include "reversequeue.h"
#include <iostream>
#include "stack.h"
using namespace std;

void reverseQueue(Queue<std::string> & queue){
    /*
     * Idea: The property of a stack comes in handy
     *       when choosing the right data structure
     *       to reverse a queue. Dequeue every element
     *       inside the queue into the stack and enqueue
     *       every element back to the queue from
     *       the top of the stack.
     */

    Stack<string> stack;
    while(!queue.isEmpty()){
        stack.push(queue.dequeue());
    }
    while(!stack.isEmpty()){
        queue.enqueue(stack.pop());
    }
    return;
}


void listQueue(Queue<std::string> & queue){
    /*
     * Idea: The property of a queue comes in handy
     *       when choosing the right data structure
     *       to list a queue. Dequeue every element
     *       inside the queue into another queue and
     *       enqueue the element back to the queue
     *       from the front of the another queue.
     *       The use of another queue is to maintain
     *       the elements such that they don't get
     *       removed permanently.
     */

    Queue<string> tempQueue;
    while(!queue.isEmpty()){
        tempQueue.enqueue(queue.dequeue());
    }
    cout << "The queue contains:";
    while(!tempQueue.isEmpty()){
        cout << " " << tempQueue.peek();
        queue.enqueue(tempQueue.dequeue());
    }
    cout << endl;
}
