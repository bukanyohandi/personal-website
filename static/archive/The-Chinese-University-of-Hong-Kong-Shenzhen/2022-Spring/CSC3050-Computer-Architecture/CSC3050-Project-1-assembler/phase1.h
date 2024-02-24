/*
 * File: phase1.h
 * --------------
 * This header file is intentionally designed to deal
 * with the .text segment for assembling.
 */

#ifndef PHASE1_H
#define PHASE1_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "labelTable.h"
using namespace std;

/* Function Prototypes */

/*
 * Function: remove_specific_char
 * Usage: string modified_line = remove_specific_char(c, line);
 * ------------------------------------------------------------
 * Returns a new modified string, which does not contain
 * a specific character anymore.
 */

string remove_specific_char(char c, string line);

/*
 * Function: remove_comments
 * Usage: remove_comments(line);
 * -----------------------------
 * Removes a substring from a line that contains comments
 * —specifically, a substring where it starts from '#'.
 */

void remove_comments(string &line);

/*
 * Function: split_string
 * Usage: vector<string> v = split_string(divider, str);
 * -----------------------------------------------------
 * Returns a vector of strings where it is originally coming
 * from string str. The split strings are divided based on
 * the custom divider.
 */

vector<string> split_string(string divider, string str);

/*
 * Function: separated_text_type
 * Usage: vector<vector<string>> text = separated_text_type(input_file);
 * ---------------------------------------------------------------------
 * Returns a vector of vectors of strings. It is a cleaned
 * version of the inputted file where it does not contain comments,
 * labels (in which its address will be saved by this function), and
 * any additional spaces / tabs.
 */

vector<vector<string>> separated_text_type(string input_file);

#endif // PHASE1_H
