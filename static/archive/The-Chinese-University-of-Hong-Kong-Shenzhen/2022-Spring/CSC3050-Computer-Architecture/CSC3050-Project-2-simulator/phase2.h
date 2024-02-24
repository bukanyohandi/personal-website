#ifndef PHASE2_H
#define PHASE2_H

#include <bitset>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "labeltable.h"
#include "phase1.h"
using namespace std;

const int lo = 33, hi = 32;

map<string, string> inverted_map(map<string, string> current_map);
void init_inverted_map();
int binary_to_int(string binary_code, bool is_signed = false);
int sign(int number, int bit = 16);
int unsign(int number, int bit = 16);
string cleaned(string str);
string execute(ifstream &ifs, ofstream &ofs, int32_t &PC, string machine_code);

#endif // PHASE2_H
