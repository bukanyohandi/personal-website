/*
 * File: RemoveComments.cpp
 * ------------------------
 * Prints out a file after removing comments.
 */

#include "RemoveComments.h"

void removeComments(istream & is, ostream & os){
    /*
     * Idea: Initialize a boolean variable as the comment status,
     *       whereas it intends to tell whether the state of the
     *       current character is commented or not commented. To
     *       solve the comment status problem, use two variables
     *       to save the previous read character and the current
     *       read character.
     */

    char previous_char = '.', current_char = '.';
    bool comment_status = false;
    string s;

    while(!is.eof()){
        is.get(current_char);

        if(previous_char == '/' && current_char == '/'){
            getline(is, s);
            previous_char = '.';
            os << '\n';
            continue;
        } else if(previous_char == '/' && current_char == '*'){
            comment_status = true;
        } else if(previous_char == '*' && current_char == '/'){
            comment_status = false;
        }

        if(comment_status != true && current_char != '/'){
            os << current_char;
        }

        previous_char = current_char;
    }

    return;
}
