#include "phase1.h"

void init_memory(){
    computer.registers = vector<int>(34, 0);
    computer.registers[28] = 0x508000 / 4;
    computer.registers[29] = 0xA00000 / 4;
    computer.registers[30] = 0xA00000 / 4;
    computer.blocks = vector<string>(0xA00000 / 4, "");
    computer.type = vector<string>(0xA00000 / 4, "string");
    computer.text_start = computer.text_end = text_segment / 4;
    computer.data_start = computer.data_end = data_segment / 4;

    return;
}

void remove_comments(string &line){
    line = line.substr(0, line.find('#'));

    return;
}

bool is_all_number(string str){
    for(auto ch: str){
        if(ch < '0' || ch > '9'){
            return false;
        }
    }
    return true;
}

string remove_specific_char(char c, string line){
    string tmp = "";
    for(auto ch: line){
        if(ch != c){
            tmp.push_back(ch);
        }
    }
    return tmp;
}

vector<string> split_string(string divider, string str){
    string tmp = "";
    vector<string> ret;

    for(auto ch: str){
        if(divider.find(ch) != string::npos){
            if(tmp != "") ret.push_back(tmp);
            tmp = "";
        } else {
            tmp.push_back(ch);
        }
    }
    if(tmp != "") ret.push_back(tmp);

    return ret;
}

void static_data_store(string current_line){
    vector<string> split_current_line;
    deque<char> dequeue;

    while(current_line.back() == ' ' || current_line.back() == '\t')
        current_line.pop_back();

    for(int idx = 0; idx < (int)current_line.size(); ++idx){
        if(dequeue.empty()){
            dequeue.push_back(current_line[idx]);
            continue;
        }
        if(dequeue.back() == '\\' && (current_line[idx] == 'n' ||  current_line[idx] == 't')){
            dequeue.pop_back();
            if(current_line[idx] == 'n')
                dequeue.push_back('\n');
            if(current_line[idx] == 't')
                dequeue.push_back('\t');
            continue;
        }
        dequeue.push_back(current_line[idx]);
    }
    current_line = "";

    while(!dequeue.empty()){
        current_line.push_back(dequeue.front());
        dequeue.pop_front();
    }

    current_line = remove_specific_char('"', current_line);
    split_current_line.push_back(current_line.substr(0, current_line.find(":")));
    current_line = current_line.substr(current_line.find("."));
    split_current_line.push_back(split_string(" \t", current_line)[0]);
    for(int idx = (int)split_current_line[1].size(); idx < (int)current_line.size(); ++idx){
        if(current_line[idx] != ' ' && current_line[idx] != '\t'){
            current_line = current_line.substr(idx);
            break;
        }
    }

    split_current_line.push_back(current_line);

    int len, temporary;

    if(split_current_line.size() < 3) return;

    // direct_save_address(split_current_line[0], computer.data_end);

    if(split_current_line[1] == ".ascii"){
        string value = split_current_line[2];
        temporary = (int)value.size();
        for(len = 0; len + 4 < (int)value.length(); len += 4){
            computer.type[computer.data_end] = "string";
            computer.blocks[computer.data_end++] = value.substr(len, 4);
        }
        if(len != (int)value.length()){
            value = value.substr(len, (int)value.length() - len);
            computer.type[computer.data_end] = "string";
            computer.blocks[computer.data_end++] = value;
        }
        while(temporary % 4 != 0) temporary++;
    } else if(split_current_line[1] == ".asciiz"){
        string value = split_current_line[2] + '\0';
        temporary = (int)value.size();
        for(len = 0; len + 4 < (int)value.length(); len += 4){
            computer.type[computer.data_end] = "string";
            computer.blocks[computer.data_end++] = value.substr(len, 4);
        }
        if(len != (int)value.length()){
            value = value.substr(len, (int)value.length() - len);
            computer.type[computer.data_end] = "string";
            computer.blocks[computer.data_end++] = value;
        }
        while(temporary % 4 != 0) temporary++;
    } else if(split_current_line[1] == ".word"){
        vector<string> resplit = split_string(",", current_line);
        for(int idx = 0; idx < (int)resplit.size(); ++idx){
            resplit[idx] = remove_specific_char(' ', resplit[idx]);
            resplit[idx] = remove_specific_char('\t', resplit[idx]);
        }
        for(auto str: resplit){
            if(is_all_number(str)){
                computer.type[computer.data_end] = "word";
                computer.blocks[computer.data_end++] = str;
            }
        }
    } else if(split_current_line[1] == ".byte"){
        vector<string> resplit = split_string(",", current_line);
        for(int idx = 0; idx < (int)resplit.size(); ++idx){
            resplit[idx] = remove_specific_char(' ', resplit[idx]);
            resplit[idx] = remove_specific_char('\t', resplit[idx]);
        }
        vector<string> dump;
        for(auto str: resplit){
            if(!is_all_number(str)){
                dump.push_back(str);
            }
        }
        for(auto str: dump){
            remove(resplit.begin(), resplit.end(), str);
        }
        string tmp;
        for(len = 0; len + 4 < (int)resplit.size(); len += 4){
            tmp = "";
            for(int k = 0; k < 4; ++k){
                if(k != 0) tmp.push_back('|');
                tmp += resplit[len + k];
            }
            computer.type[computer.data_end] = "byte";
            computer.blocks[computer.data_end++] = tmp;
        }
        if(len != (int)resplit.size()){
            tmp = "";
            int k;
            for(k = 0; len + k < (int)resplit.size() && k < 4; ++k){
                if(k != 0) tmp.push_back('|');
                tmp += resplit[len + k];
            }
            while(k < 4) tmp.push_back('|');
            computer.type[computer.data_end] = "byte";
            computer.blocks[computer.data_end++] = tmp;
        }
    } else if(split_current_line[1] == ".half"){
        vector<string> resplit = split_string(",", current_line);
        for(int idx = 0; idx < (int)resplit.size(); ++idx){
            resplit[idx] = remove_specific_char(' ', resplit[idx]);
            resplit[idx] = remove_specific_char('\t', resplit[idx]);
        }
        vector<string> dump;
        for(auto str: resplit){
            if(!is_all_number(str)){
                dump.push_back(str);
            }
        }
        for(auto str: dump){
            remove(resplit.begin(), resplit.end(), str);
        }
        string tmp;
        for(len = 0; len + 2 < (int)resplit.size(); len += 2){
            tmp = "";
            for(int k = 0; k < 2; ++k){
                if(k != 0) tmp.push_back('|');
                tmp += resplit[len + k];
            }
            computer.type[computer.data_end] = "half";
            computer.blocks[computer.data_end++] = tmp;
        }
        if(len != (int)resplit.size()){
            tmp = "";
            int k;
            for(k = 0; len + k < (int)resplit.size() && k < 2; ++k){
                if(k != 0) tmp.push_back('|');
                tmp += resplit[len + k];
            }
            while(k < 2) tmp.push_back('|');
            computer.type[computer.data_end] = "half";
            computer.blocks[computer.data_end++] = tmp;
        }
    } else {
        cerr << "[Error] unknown data type occurs, found: " << split_current_line[1] << endl;
        exit(1);
    }

    return;
}

void text_store(string assembled_binary_file){
    string current_line;
    ifstream ifs(assembled_binary_file);

    while(getline(ifs, current_line)){
        if(computer.text_end <= computer.data_start){
            computer.type[computer.text_end] = "instruction";
            computer.blocks[computer.text_end++] = current_line;
//            computer.registers[29] = computer.text_end;
        } else {
            cerr << "[Error] memory limit exceeded" << endl;
            exit(1);
        }
    }

    return;
}

void separate_data_type(string assembly_file){
    bool usage = false;
    string current_line;
    ifstream ifs(assembly_file);

    while(getline(ifs, current_line)){
        remove_comments(current_line);

        if(current_line.find(".text") != string::npos){
            usage = false;
            continue;
        } else if(current_line.find(".data") != string::npos){
            usage = true;
            continue;
        }

        if(usage == true && current_line != ""){
            static_data_store(current_line);
        }
    }

    ifs.close();

    return;
}

void separated_text_type(string assembly_file){
    int current_line_number = 0;
    bool check = false, usage = false;
    string current_line;
    vector<string> split_current_line, tmp;
    ifstream ifs(assembly_file);

    while(getline(ifs, current_line)){
        remove_comments(current_line);

        if(current_line.find(".text") != string::npos){
            usage = true;
            continue;
        } else if(current_line.find(".data") != string::npos){
            usage = false;
            continue;
        }

        if(usage == true && current_line != ""){
            check = false;
            tmp.clear();
            split_current_line = split_string(" \t", current_line);
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
                current_line_number++;
            }
        }
    }

    ifs.close();

    return;
}
