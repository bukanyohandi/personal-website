#ifndef PHASE1_H
#define PHASE1_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include "labeltable.h"
using namespace std;

const int32_t text_segment = 0x400000;
const int32_t data_segment = 0x500000;
const int32_t allocated_memory = 0x600000;

extern struct memory{
    vector<int> registers;
    vector<string> blocks, type;
    int32_t text_start, data_start, text_end, data_end, PC;
} computer;

void init_memory();
void remove_comments(string &line);
bool is_all_number(string str);
string remove_specific_char(char c, string line);
vector<string> split_string(string divider, string str);
void static_data_store(string current_line);
void text_store(string assembled_binary_file);
void separate_data_type(string assembly_file);
void separated_text_type(string assembly_file);

#endif // PHASE1_H
