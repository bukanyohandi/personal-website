/*
 * File: tester.h
 * --------------
 * This header file is intentionally designed
 * to compare two files. Mainly both files are
 * the output and its expected output.
 */

#ifndef TESTER_H
#define TESTER_H

#include <string>
using namespace std;

/* Function Prototypes */

/*
 * Function: compare_files
 * Usage: string result = compare_files(output_file, expected_output_file);
 * ---------------------------------------------------------------------
 * Returns a string expression of the equality of two files
 * by comparing each of the characters contained between two files.
 */

string compare_files(string output_file, string expected_output_file);

#endif // TESTER_H
