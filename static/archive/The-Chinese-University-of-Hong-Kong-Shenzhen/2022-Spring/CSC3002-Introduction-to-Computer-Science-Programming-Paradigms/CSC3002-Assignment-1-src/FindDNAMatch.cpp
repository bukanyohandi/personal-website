/*
 * File: FindDNAMatch.cpp
 * ----------------------
 * This file solves the DNA matching exercise from the text.
 */

#include "FindDNAMatch.h"

int findDNAMatch(string s1, string s2, int start){
    /*
     * Idea: First, modify s1 into its matching strand.
     *       Then, the problem is changed to "Find the
     *       index of the first matched substring". To
     *       do this, use two for loops. The first for
     *       loop iterates each index in the longer DNA
     *       strand, and the second for loop iterates
     *       each index in the shorter DNA strand to
     *       compare each character.
     */

    string modified_s1 = matchingStrand(s1);

    for(int i = start; i < (int)s2.length(); ++i){
        bool check = true;

        for(int j = 0; j < (int)modified_s1.length()
                        && i + j < (int)s2.length(); ++j){
            if(modified_s1[j] != s2[i + j]){
                check = false;
            }
        }

        if(check == true){
            return i + 1;
        }
    }

    return -1;
}

string matchingStrand(string strand){
    /*
     * Idea: Loop every single character in the strand.
     *       Directly change A <-> T and C <-> G, other
     *       characters will be changed to X.
     */

    string modified_strand = strand;

    for(int i = 0; i < (int)strand.length(); ++i){
        if(strand[i] == 'A') modified_strand[i] = 'T';
        else if(strand[i] == 'C') modified_strand[i] = 'G';
        else if(strand[i] == 'G') modified_strand[i] = 'C';
        else if(strand[i] == 'T') modified_strand[i] = 'A';
        else modified_strand[i] = 'X';
    }

    return modified_strand;
}

void findAllMatches(string s1, string s2){
    /*
     * Idea: Initialize a variable for the index location.
     *       Use a do-while loop until the condition of
     *       "there is no match" is met. The condition is
     *       met when the value of the index is equal to -1.
     */

    int index = 0, sz = 0;
    int arr[(int)s1.length() + s2.length()];
    do{
        index = findDNAMatch(s1, s2, index);
        if(index != -1){
            arr[sz++] = index - 1;
        }
    } while(index != -1);

    if(sz != 0){
        cout << "Matched position found: ";
        for(int i = 0; i < sz; ++i){
            if(i != 0) cout << ", ";
            cout << arr[i];
        }
    } else {
        cout << "No matched position found";
    }
    cout << endl;

    return;
}
