/*
 * File: phase1.cpp
 * ----------------
 * This file implements the phase1.h interface.
 */

#include "phase1.h"

string remove_specific_char(char c, string line){
    string tmp = "";
    for(auto ch: line){
        if(ch != c){
            tmp.push_back(ch);
        }
    }
    return tmp;
}

void remove_comments(string &line){
    line = line.substr(0, line.find('#'));
    return;
}

vector<string> split_string(string divider, string str){
    string tmp = "";
    vector<string> ret;
    for(auto ch: str){
        if(divider.find(ch) != string::npos){
            if(tmp != ""){
                ret.push_back(tmp);
            }
            tmp = "";
        } else {
            tmp.push_back(ch);
        }
    }
    if(tmp != ""){
        ret.push_back(tmp);
    }
    return ret;
}

vector<vector<string>> separated_text_type(string input_file){
    int current_line_number = 0;
    bool check = false, usage = false;
    string current_line;
    vector<string> split_current_line, tmp;
    vector<vector<string>> ret;
    ifstream ifs(input_file);

    while(getline(ifs, current_line)){
        if(current_line.find(".text") != string::npos){
            usage = true;
            continue;
        } else if(current_line.find(".data") != string::npos){
            usage = false;
            continue;
        }
        if(usage == true){
            check = false;
            tmp.clear();
            remove_comments(current_line);
            split_current_line = split_string(" 	", current_line);
            for(string s: split_current_line){
                if(s.find(':') != string::npos){
                    if(check == true){
                        cerr << "[Error] invalid operation occurs" << endl;
                        exit(1);
                    }
                    save_address(remove_specific_char(':', s), current_line_number);
                } else {
                    tmp.push_back(remove_specific_char(',', s));
                    check = true;
                }
            }
            if(!tmp.empty()){
                ret.push_back(tmp);
                current_line_number++;
            }
        }
    }

    ifs.close();

    return ret;
}
