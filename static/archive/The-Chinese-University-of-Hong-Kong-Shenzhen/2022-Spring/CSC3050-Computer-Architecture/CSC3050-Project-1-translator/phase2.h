/*
 * File: phase2.h
 * --------------
 * This header file implements each of the MIPS
 * instructions and translates it to a machine
 * code line by line. The address of a label can
 * be referred to the stored information in
 * labelTable class file.
 */

#ifndef PHASE2_H
#define PHASE2_H

#include <bitset>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "labelTable.h"
using namespace std;

const string UNDEFINED_5_BIT = "00000";
const string UNDEFINED_6_BIT = "000000";
const string UNDEFINED_16_BIT = "0000000000000000";

/* Function Prototypes */

/*
 * Function: r_instruction
 * Usage: string r = r_instruction(op, rs, rt, rd, shamt, funct);
 * --------------------------------------------------------------
 * Returns a concatenated string of machine code based on
 * the R-type instruction parameters.
 */

string r_instruction(string op, string rs, string rt, string rd, string shamt, string funct);

/*
 * Function: i_instruction
 * Usage: string i = i_instruction(op, rs, rt, immediate);
 * -------------------------------------------------------
 * Returns a concatenated string of machine code based on
 * the I-type instruction parameters.
 */

string i_instruction(string op, string rs, string rt, string immediate);

/*
 * Function: j_instruction
 * Usage: string j = j_instruction(op, address);
 * ---------------------------------------------
 * Returns a concatenated string of machine code based on
 * the J-type instruction parameters.
 */

string j_instruction(string op, string address);

/*
 * Function: machine_code
 * Usage: machine_code(vectors, argument, line_number);
 * ----------------------------------------------------
 * Fills the vector of strings with a machine code result
 * based on the instruction argument.
 */


void machine_code(vector<string> &ret, vector<string> argument, int line_number);

/*
 * Function: character_in_string
 * Usage: bool contained = character_in_string(c, s);
 * --------------------------------------------------
 * Returns a boolean expression whether a character is
 * contained inside of a string.
 */

bool character_in_string(char c, string s);

/*
 * Function: frag
 * Usage: string fragged = frag(argument, divider, index);
 * -------------------------------------------------------
 * Returns the index-th fragged string from the original
 * argument. The frags are divided based on the custom divider.
 */

string frag(string argument, string divider, int index);

#endif // PHASE2_H
