/*
 * File: TraverseTest.cpp
 * ------------------
 * This program reimplements the depth-first search algorithm using an
 * explicit stack
 * or
 * reimplements the breadth-first search algorithm using an
 * explicit queue.
 */

#include "P2Traverse.h"

using namespace std;

void dfs(Node *start){
    Stack<Node*> stack;
    Set<Node*> visited;

    cout << "*** DFS search ***" << endl;

    stack.push(start);
    visited.add(start);
    while(!stack.isEmpty()){
        Node *current = stack.pop();
        cout << current -> name << endl;
        for(Arc *neighbor: current -> arcs){
//        foreach(Arc *neighbor in current -> arcs){
            if(!visited.contains(neighbor -> finish)){
                stack.push(neighbor -> finish);
                visited.add(neighbor -> finish);
            }
        }
    }
}

void bfs(Node *start){
    Queue<Node*> queue;
    Set<Node*> visited;

    cout << "*** BFS search ***" << endl;

    queue.enqueue(start);
    visited.add(start);
    while(!queue.isEmpty()){
        Node *current = queue.dequeue();
        cout << current -> name << endl;
        for(Arc *neighbor: current -> arcs){
//        foreach(Arc *neighbor in current -> arcs){
            if(!visited.contains(neighbor -> finish)){
                queue.enqueue(neighbor -> finish);
                visited.add(neighbor -> finish);
            }
        }
    }
}
