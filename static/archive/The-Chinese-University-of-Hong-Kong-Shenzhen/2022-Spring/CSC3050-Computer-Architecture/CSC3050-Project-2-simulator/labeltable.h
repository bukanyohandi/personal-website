/*
 * File: labelTable.h
 * ------------------
 * This header file is intentionally created as storage, where
 * it saves the address of all collected labels.
 */

#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <map>
#include <string>
using namespace std;

extern int32_t dynamic_address;

/* Function Prototypes */

/*
 * Function: save_address
 * Usage: save_address(label, current_line_number);
 * ------------------------------------------------
 * Saves an address of a label with current_line_number as a
 * variable in determining its address corresponds to the number
 * of lines.
 */

void save_address(string label, int current_line_number);

void direct_save_address(string label, int32_t address);

/*
 * Function: get_relative_address
 * Usage: int32_t rel_address = get_relative_address(label, current_line_number);
 * ------------------------------------------------------------------------------
 * Returns a relative address of a label with current_line_number
 * as a variable in determining its relative address based on the
 * number of lines.
 */

int32_t get_relative_address(string label, int current_line_number);

/*
 * Function: get_address
 * Usage: int32_t address = get_address(label);
 * --------------------------------------------
 * Returns an address of a specific label.
 */

int32_t get_address(string label);

#endif // LABELTABLE_H
