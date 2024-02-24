/*
 * File: buffer.cpp (list version without dummy cell)
 * --------------------------------------------------
 * This file implements the EditorBuffer class using a linked
 * list to represent the buffer.
 */

#include <iostream>
#include "buffer.h"
using namespace std;

/*
 * Implementation notes: EditorBuffer constructor
 * ----------------------------------------------
 * This function initializes an empty editor buffer, represented
 * as a doubly linked list.  In this implementation, the ends of
 * the linked list are joined to form a ring, with the dummy cell
 * at both the beginning and the end.  This representation makes
 * it possible to implement the moveCursorToEnd method in constant
 * time, and reduces the number of special cases in the code.
 */

EditorBuffer::EditorBuffer() {
    start = cursor = new Cell;
    start->next = start;
    start->prev = start;
}

EditorBuffer::~EditorBuffer() {
    Cell *current = start;
    do{
        Cell *tmp = start -> next;
        delete current;
        current = tmp;
    } while(current != NULL);
}

/*
 * Implementation notes: cursor movement
 * -------------------------------------
 * In a doubly linked list, each of these operations runs in
 * constant time.
 */

void EditorBuffer::moveCursorForward() {
    if (cursor != start) {
        cursor = cursor -> next;
    }

    return;
}

void EditorBuffer::moveCursorBackward() {
    if (cursor -> prev != start) {
        cursor = cursor -> prev;
    }

    return;
}

void EditorBuffer::moveCursorToStart() {
    cursor = start->next;

    return;
}

void EditorBuffer::moveCursorToEnd() {
    cursor = start;

    return;
}

void EditorBuffer::insertCharacter(char ch) {
    Cell *current = new Cell;

    current -> ch = ch;
    current -> prev = cursor -> prev;
    current -> next = cursor;

    cursor -> prev -> next = current;
    cursor -> prev = current;

    return;
}

void EditorBuffer::deleteCharacter() {
    if(cursor != start){
        Cell *current = cursor;

        current -> prev -> next = current -> next;
        current -> next -> prev = current -> prev;
        cursor = current -> next;

        delete current;
    }

    return;
}

string EditorBuffer::getText() const {
    Cell *current = start -> next;
    string ret = "";

    while(current -> next != start){
        ret += current -> ch;
        current = current -> next;
    }

    return ret + current -> ch;
}

int EditorBuffer::getCursor() const {
    Cell *current = start;
    int index = 0;

    for(; current -> next != cursor; current = current -> next){
        index++;
    }

    return index;
}
