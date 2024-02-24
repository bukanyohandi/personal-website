#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H

#include <bitset>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "phase1.h"
using namespace std;

string string_to_binary(string str);
string word_to_binary(string word);
string half_to_binary(string half);
string byte_to_binary(string byte);
void init_checkpoint(string checkpoint_file);
bool is_checkpoint(int ins_count);
void checkpoint(int ins_count, memory computer);
void checkpoint2(int ins_count, memory computer);

#endif // CHECKPOINTS_H
