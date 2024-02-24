#include "checkpoints.h"

set<int> checkpoints;

unsigned int binary_to_int(string binary){
    unsigned int result = 0;
    int piv = (int)binary.length();
    for(int i = 0; i < piv; ++i){
        if(binary[i] == '0') continue;
        if(i == 0) result += (unsigned int)(1 << (piv - i - 1));
        else result += (unsigned int)(1 << (piv - i - 1));
    }
    return result;
}

bool is_all_numberr(string str){
    for(auto c: str)
        if(c < '0' || c > '9') return false;
    return true;
}

string string_to_binary(string str){
    string ret = "";
    vector<string> bytes(4, "");

    if(str.length() < 4){
        for(int k = (int)str.length(); k < 4; ++k)
            bytes[k] = "00000000";
    }
    if(str.length() > 4){
        str = str.substr(0, 4);
    }

    for(int k = 3; k >= 0; --k){
        if(bytes[k] == ""){
            bytes[k] = bitset<8>((int)str[k]).to_string();
        }

        ret += bytes[k];
    }

    return ret;
}

string word_to_binary(string word){
    if(word == ""){
        string tmp = "";
        for(int i = 0; i < 32; ++i) tmp.push_back('0');
        return tmp;
    }
    if(word.length() == 32){
        string bytes[4];
        for(int k = 0; k < 4; ++k)
            bytes[k] = word.substr(k * 8, 8);
        return bytes[3] + bytes[2] + bytes[1] + bytes[0];
    }
    return bitset<32>(stoi(word)).to_string();
}

string half_to_binary(string half){
    string ret = "";
    vector<string> vec = split_string("|", half);
    for(int k = 1; k >= 0; --k){
        if(vec[k] == ""){
            ret += "0000000000000000";
            continue;
        }
        if(vec[k].length() == 16){
            string bytes[2];
            for(int k = 0; k < 2; ++k)
                bytes[k] = vec[k].substr(k * 8, 8);
            ret += bytes[1] + bytes[0];
            continue;
        }
        ret += bitset<16>(stoi(vec[k])).to_string();
    }
    return ret;
}
string byte_to_binary(string byte){
    string ret = "";
    vector<string> vec = split_string("|", byte);
    for(int k = 3; k >= 0; --k){
        if(vec[k] == ""){
            ret += "00000000";
            continue;
        }
        if(vec[k].length() == 8){
            ret += vec[k];
            continue;
        }
        ret += bitset<8>(stoi(vec[k])).to_string();
    }
    return ret;
}

string int_to_binary(int number){
    string str = bitset<32>(number).to_string();
    string bytes[4];
    for(int k = 0; k < 4; ++k){
        bytes[k] = str.substr(k * 8, 8);
    }
    return bytes[0] + bytes[1] + bytes[2] + bytes[3];
    return bytes[3] + bytes[2] + bytes[1] + bytes[0];
}

void init_checkpoint(string checkpoint_file){
    ifstream ifs(checkpoint_file);
    int point;
    while(ifs >> point){
        checkpoints.insert(point);
    }
    ifs.close();
}

void checkpoint_memory(int ins_count, memory computer){
    FILE *fp = fopen(("memory_" + to_string(ins_count) + ".bin").c_str(), "wb");
    for(int32_t address = 0x400000 / 4; address < 0xA00000 / 4; ++address){
        string str;

        if(computer.type[address] == "word"){
            str = word_to_binary(computer.blocks[address]);
        } else if(computer.type[address] == "half"){
            str = half_to_binary(computer.blocks[address]);
        } else if(computer.type[address] == "byte"){
            str = byte_to_binary(computer.blocks[address]);
        } else if(computer.type[address] == "instruction"){
            str = computer.blocks[address];
        } else {
            str = string_to_binary(computer.blocks[address]);
        }
        //if(ins_count == 23 && str.find('1') != -1) cout << computer.type[address] << endl;
        unsigned int a = binary_to_int(str);
        void *p = &a;
        //if(ins_count == 23 && str.find('1') != -1) cout << a << endl;
        fwrite(p, 4, 1, fp);
        //if(ins_count == 23 && str.find('1') != -1) cout << "success\n";
    }
    fclose(fp);
}

void checkpoint_register(int ins_count, memory computer){
    FILE *fp = fopen(("register_" + to_string(ins_count) + ".bin").c_str(), "wb");

    for(int i = 0; i < 28; ++i){
        int a = computer.registers[i];
        void *p = &a;
        fwrite(p, 4, 1, fp);
    }

    for(int i = 28; i < 32; ++i){
        int a = computer.registers[i] * 4;
        void *p = &a;
        fwrite(p, 4, 1, fp);
    }

    int a = computer.PC;
    void *p = &a;
    fwrite(p, 4, 1, fp);

    for(int i = 32; i <= 33; ++i){
        int a = computer.registers[i];
        void *p = &a;
        fwrite(p, 4, 1, fp);
    }

    fclose(fp);
}

bool is_checkpoint(int ins_count){
    return checkpoints.count(ins_count);
}

void checkpoint(int ins_count, memory computer){
    if(!checkpoints.count(ins_count))
        return;
    checkpoint_memory(ins_count, computer);
}

void checkpoint2(int ins_count, memory computer){
    if(!checkpoints.count(ins_count))
        return;
    checkpoint_register(ins_count, computer);
}
