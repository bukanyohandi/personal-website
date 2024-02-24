/*
 * File: labelTable.cpp
 * --------------------
 * This file implements the labelTable.h interface.
 */

#include "labelTable.h"

const int32_t address_start = 0x400000;
map<string, int32_t> label_address;

void save_address(string label, int current_line_number){
    if(label_address.count(label) == 1) return;
    label_address[label] = (int32_t)address_start + (4 * current_line_number);
    return;
}

int32_t get_relative_address(string label, int current_line_number){
    if(label_address.count(label) == 0) return -1;
    return (int32_t) (label_address[label] - (address_start + (4 * current_line_number))) / 4;
}

int32_t get_address(string label){
    if(label_address.count(label) == 0) return -1;
    return (int32_t) label_address[label] / 4;
}
