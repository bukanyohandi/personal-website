/*
 * File: phase2.cpp
 * ----------------
 * This file implements the phase2.h interface.
 */

#include "phase2.h"

map<string, string> register_number
    = {{"$zero","00000"},   {"$at", "00001"},   {"$v0", "00010"},   {"$v1", "00011"},
       {"$a0",  "00100"},   {"$a1", "00101"},   {"$a2", "00110"},   {"$a3", "00111"},
       {"$t0",  "01000"},   {"$t1", "01001"},   {"$t2", "01010"},   {"$t3", "01011"},
       {"$t4",  "01100"},   {"$t5", "01101"},   {"$t6", "01110"},   {"$t7", "01111"},
       {"$s0",  "10000"},   {"$s1", "10001"},   {"$s2", "10010"},   {"$s3", "10011"},
       {"$s4",  "10100"},   {"$s5", "10101"},   {"$s6", "10110"},   {"$s7", "10111"},
       {"$t8",  "11000"},   {"$t9", "11001"},   {"$k0", "11010"},   {"$k1", "11011"},
       {"$gp",  "11100"},   {"$sp", "11101"},   {"$fp", "11110"},   {"$ra", "11111"}};

map<string, string> r_type_function
    = {{"add",  "100000"},  {"addu","100001"},  {"and", "100100"},  {"div", "011010"},
       {"divu", "011011"},  {"jalr","001001"},  {"jr",  "001000"},  {"mfhi","010000"},
       {"mflo", "010010"},  {"mthi","010001"},  {"mtlo","010011"},  {"mult","011000"},
       {"multu","011001"},  {"nor", "100111"},  {"or",  "100101"},  {"sll", "000000"},
       {"sllv", "000100"},  {"slt", "101010"},  {"sltu","101011"},  {"sra", "000011"},
       {"srav", "000111"},  {"srl", "000010"},  {"srlv","000110"},  {"sub", "100010"},
       {"subu", "100011"},  {"syscall","001100"},{"xor","100110"}};

map<string, string> i_type_opcode
    = {{"addi", "001000"},  {"addiu","001001"}, {"andi","001100"},  {"beq", "000100"},
       {"bgez", "000001"},  {"bgtz","000111"},  {"blez","000110"},  {"bltz","000001"},
       {"bne",  "000101"},  {"lb",  "100000"},  {"lbu", "100100"},  {"lh",  "100001"},
       {"lhu",  "100101"},  {"lui", "001111"},  {"lw",  "100011"},  {"ori", "001101"},
       {"sb",   "101000"},  {"slti","001010"},  {"sltiu","001011"}, {"sh",  "101001"},
       {"sw",   "101011"},  {"xori","001110"},  {"lwl", "100010"},  {"lwr", "100110"},
       {"swl",  "101010"},  {"swr", "101110"}};

map<string, string> j_type_opcode
    = {{"j",    "000010"},  {"jal", "000011"}};

string r_instruction(string op, string rs, string rt, string rd, string shamt, string funct){
    if(rs != UNDEFINED_5_BIT) rs = register_number[rs];
    if(rt != UNDEFINED_5_BIT) rt = register_number[rt];
    if(rd != UNDEFINED_5_BIT) rd = register_number[rd];
    if(shamt != UNDEFINED_5_BIT){
        shamt = bitset<5>(stoi(shamt)).to_string();
    }
    return op + rs + rt + rd + shamt + funct;
}

string i_instruction(string op, string rs, string rt, string immediate){
    if(rs != UNDEFINED_5_BIT) rs = register_number[rs];
    if(rt != UNDEFINED_5_BIT) rt = register_number[rt];
    if(immediate != UNDEFINED_16_BIT){
        immediate = bitset<16>(stoi(immediate)).to_string();
    }
    return op + rs + rt + immediate;
}

string j_instruction(string op, string address){
    return op + bitset<26>(stoi(address)).to_string();
}

bool character_in_string(char c, string s){
    for(auto ch: s){
        if(ch == c){
            return true;
        }
    }
    return false;
}

string frag(string argument, string divider, int index){
    vector<string> ret;
    string tmp = "";

    for(auto ch: argument){
        if(character_in_string(ch, divider)){
            ret.push_back(tmp);
            tmp = "";
        } else {
            tmp.push_back(ch);
        }
    }

    if(index >= (int)ret.size()){
        return "";
    }
    return ret[index];
}

void machine_code(vector<string> &ret, vector<string> argument, int line_number){
    if(argument[0] == "add"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "addu"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "and"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "div"){
        ret.push_back(r_instruction("000000", argument[1], argument[2], UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "divu"){
        ret.push_back(r_instruction("000000", argument[1], argument[2], UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "jalr"){
        ret.push_back(r_instruction("000000", argument[2], UNDEFINED_5_BIT, argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "jr"){
        ret.push_back(r_instruction("000000", argument[1], UNDEFINED_5_BIT, UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "mfhi"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, UNDEFINED_5_BIT, argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "mflo"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, UNDEFINED_5_BIT, argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "mthi"){
        ret.push_back(r_instruction("000000", argument[1], UNDEFINED_5_BIT, UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "mtlo"){
        ret.push_back(r_instruction("000000", argument[1], UNDEFINED_5_BIT, UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "mult"){
        ret.push_back(r_instruction("000000", argument[1], argument[2], UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "multu"){
        ret.push_back(r_instruction("000000", argument[1], argument[2], UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "nor"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "or"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "sll"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, argument[2], argument[1], argument[3], r_type_function[argument[0]]));
    } else if(argument[0] == "sllv"){
        ret.push_back(r_instruction("000000", argument[3], argument[2], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "slt"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "sltu"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "sra"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, argument[2], argument[1], argument[3], r_type_function[argument[0]]));
    } else if(argument[0] == "srav"){
        ret.push_back(r_instruction("000000", argument[3], argument[2], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "srl"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, argument[2], argument[1], argument[3], r_type_function[argument[0]]));
    } else if(argument[0] == "srlv"){
        ret.push_back(r_instruction("000000", argument[3], argument[2], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "sub"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "subu"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "syscall"){
        ret.push_back(r_instruction("000000", UNDEFINED_5_BIT, UNDEFINED_5_BIT, UNDEFINED_5_BIT, UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "xor"){
        ret.push_back(r_instruction("000000", argument[2], argument[3], argument[1], UNDEFINED_5_BIT, r_type_function[argument[0]]));
    } else if(argument[0] == "addi"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "addiu"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "andi"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "beq"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], argument[2], to_string(get_relative_address(argument[3], line_number))));
    } else if(argument[0] == "bgez"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], "00001", to_string(get_relative_address(argument[2], line_number))));
    } else if(argument[0] == "bgtz"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], "00000", to_string(get_relative_address(argument[2], line_number))));
    } else if(argument[0] == "blez"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], "00000", to_string(get_relative_address(argument[2], line_number))));
    } else if(argument[0] == "bltz"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], "00000", to_string(get_relative_address(argument[2], line_number))));
    } else if(argument[0] == "bne"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[1], argument[2], to_string(get_relative_address(argument[3], line_number))));
    } else if(argument[0] == "lb"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "lbu"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "lh"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "lhu"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "lui"){
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], UNDEFINED_5_BIT, argument[1], immediate));
    } else if(argument[0] == "lw"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "ori"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "sb"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "slti"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "sltiu"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "sh"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "sw"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "xori"){
        ret.push_back(i_instruction(i_type_opcode[argument[0]], argument[2], argument[1], argument[3]));
    } else if(argument[0] == "lwl"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "lwr"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "swl"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "swr"){
        string rs = frag(argument[2], "()", 1);
        string immediate = frag(argument[2], "()", 0);
        ret.push_back(i_instruction(i_type_opcode[argument[0]], rs, argument[1], immediate));
    } else if(argument[0] == "j"){
        ret.push_back(j_instruction(j_type_opcode[argument[0]], to_string(get_address(argument[1]))));
    } else if(argument[0] == "jal"){
        ret.push_back(j_instruction(j_type_opcode[argument[0]], to_string(get_address(argument[1]))));
    } else {
        cerr << "[Error] unknown operation type occurs, found: " << argument[0] << endl;
        exit(1);
    }
}
