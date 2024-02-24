#include "phase2.h"

map<string, string> r_type_function
    = {{"add",  "100000"},  {"addu","100001"},  {"and", "100100"},  {"div", "011010"},
       {"divu", "011011"},  {"jalr","001001"},  {"jr",  "001000"},  {"mfhi","010000"},
       {"mflo", "010010"},  {"mthi","010001"},  {"mtlo","010011"},  {"mult","011000"},
       {"multu","011001"},  {"nor", "100111"},  {"or",  "100101"},  {"sll", "000000"},
       {"sllv", "000100"},  {"slt", "101010"},  {"sltu","101011"},  {"sra", "000011"},
       {"srav", "000111"},  {"srl", "000010"},  {"srlv","000110"},  {"sub", "100010"},
       {"subu", "100011"},  {"syscall","001100"},{"xor","100110"}};
map<string ,string> inverted_r_type_function;

map<string, string> i_type_opcode
    = {{"addi", "001000"},  {"addiu","001001"}, {"andi","001100"},  {"beq", "000100"},
       {"bgez", "000001"},  {"bgtz","000111"},  {"blez","000110"},  {"bltz","000001"},
       {"bne",  "000101"},  {"lb",  "100000"},  {"lbu", "100100"},  {"lh",  "100001"},
       {"lhu",  "100101"},  {"lui", "001111"},  {"lw",  "100011"},  {"ori", "001101"},
       {"sb",   "101000"},  {"slti","001010"},  {"sltiu","001011"}, {"sh",  "101001"},
       {"sw",   "101011"},  {"xori","001110"},  {"lwl", "100010"},  {"lwr", "100110"},
       {"swl",  "101010"},  {"swr", "101110"}};
map<string, string> inverted_i_type_opcode;

map<string, string> j_type_opcode
    = {{"j",    "000010"},  {"jal", "000011"}};
map<string, string> inverted_j_type_opcode;

map<string, string> inverted_map(map<string, string> current_map){
    map<string, string> result;
    for(auto values: current_map){
        result[values.second] = values.first;
    }

    return result;
}

void init_inverted_map(){
    inverted_r_type_function = inverted_map(r_type_function);
    inverted_i_type_opcode = inverted_map(i_type_opcode);
    inverted_j_type_opcode = inverted_map(j_type_opcode);

    return;
}

int binary_to_int(string binary_code, bool is_signed){
    int ret = 0;

    if(binary_code[0] == '1'){
        if(is_signed == false){
            ret += (1 << ((int)binary_code.length() - 1));
        } else {
            ret -= (1 << ((int)binary_code.length() - 1));
        }
    }

    for(int bit = 1; bit < (int)binary_code.length(); ++bit){
        if(binary_code[bit] == '1'){
            ret += (1 << ((int)binary_code.length() - bit - 1));
        }
    }

    return ret;
}

string int_to_hex(int number){
    stringstream stream;
    stream << "0x" << hex << number;
    return stream.str();
}

int sign16(int number){
    return binary_to_int(bitset<16>(number).to_string(), true);
}

int unsign16(int number){
    return binary_to_int(bitset<16>(number).to_string(), false);
}

int sign32(int number){
    return binary_to_int(bitset<32>(number).to_string(), true);
}

uint32_t unsign32(int number){
    return binary_to_int(bitset<32>(number).to_string(), false);
}

string cleaned(string str){
    if(str.back() == '\0')
        str.pop_back();
    return str;
}

string execute(ifstream &ifs, ofstream &ofs, int32_t &PC, string machine_code){
    if(machine_code == "00000000000000000000000000001100"){
        if(computer.registers[2] == 1){
            ofs << computer.registers[4];
        } else if(computer.registers[2] == 2){
            // no need to be considered
        } else if(computer.registers[2] == 3){
            // no need to be considered
        } else if(computer.registers[2] == 4){
            for(int32_t address = computer.registers[4] / 4; address < computer.data_end; ++address){
                ofs << cleaned(computer.blocks[address]) << flush;
                if(computer.blocks[address].find('\0') != string::npos) break;
            }
        } else if(computer.registers[2] == 5){
            string str;
            getline(ifs, str);
            computer.registers[2] = stoi(str);
        } else if(computer.registers[2] == 6){
            // no need to be considered
        } else if(computer.registers[2] == 7){
            // no need to be considered
        } else if(computer.registers[2] == 8){
            int len;
            int32_t address = computer.registers[4] / 4;
            string str;
            getline(ifs, str);
            for(len = 0; len + 4 < (int)str.length(); len += 4){
                computer.type[address] = "string";
                computer.blocks[address++] = str.substr(len, 4);
            }
            if(len != (int)str.length()){
                str = str.substr(len, (int)str.length() - len);
                computer.type[address] = "string";
                computer.blocks[address++] = str;
            }
            computer.data_end = max(computer.data_end, address);
        } else if(computer.registers[2] == 9){
            for(int32_t address = dynamic_address;; address++){
                bool check = true;
                for(int32_t pointer = address;
                    pointer < address + ((computer.registers[4] + 3) / 4);
                    pointer++){
                    if(computer.blocks[pointer] != "") check = false;
                }
                if(check == true){
                    dynamic_address = address;
                    break;
                }
            }
            computer.registers[2] = dynamic_address * 4;
        } else if(computer.registers[2] == 10){
            return "Exit 0";
        } else if(computer.registers[2] == 11){
            ofs << (char)computer.registers[4];
        } else if(computer.registers[2] == 12){
            char ch;
            string str;
            getline(ifs, str);
            ch = str[0];
            computer.registers[2] = ch;
        } else if(computer.registers[2] == 13){
            int32_t address = computer.registers[4] / 4;
            string str = "";

            for(; address < computer.data_end; ++address){
                str += cleaned(computer.blocks[address]);
                if(computer.blocks[address].find('\0') != string::npos) break;
            }
            str = str.substr(1);
            computer.registers[4] = open(str.c_str(), computer.registers[5], (mode_t)computer.registers[6]);
//            computer.registers[4] = open(str.c_str(), O_RDWR | O_CREAT);
            if(computer.registers[4] == -1) return "[Error] cannot open file";
        } else if(computer.registers[2] == 14){
            int len, tmp = 0, sz = 0;
            char buffer[computer.registers[6]];
            int32_t address = computer.registers[5] / 4;
            string str = "";
            for(int k = 0; k < computer.registers[6]; ++k){
                char c;
                tmp += read(computer.registers[4], &c, 1);
                buffer[sz++] = c;
            }
            computer.registers[4] = tmp;
            for(int idx = 0; idx < (int)strlen(buffer); ++idx){
                str.push_back(buffer[idx]);
            }
            for(len = 0; len + 4 < (int)str.length(); len += 4){
                computer.type[address] = "string";
                computer.blocks[address++] = str.substr(len, 4);
            }
            if(len != (int)str.length()){
                str = str.substr(len);
                computer.type[address] = "string";
                computer.blocks[address++] = str;
            }
            computer.data_end = max(computer.data_end, address);
        } else if(computer.registers[2] == 15){
            int sz = 0;
            char msg[computer.registers[6]];
            int32_t address = computer.registers[5] / 4;
            for(; sz < computer.registers[6]; ){
                for(int k = 0; k < 4 && sz < computer.registers[6]; ++k){
                    msg[sz++] = computer.blocks[address][k];
                }
                address++;
            }
            computer.registers[4] = write(computer.registers[4], msg, sizeof(msg));
            computer.data_end = max(computer.data_end, address);
        } else if(computer.registers[2] == 16){
            close(computer.registers[4]);
        } else if(computer.registers[2] == 17){
            return "Exit " + to_string(computer.registers[4]);
        }

        return "Success";
    }

    if(machine_code.substr(0, 6) == "000000"){
        int rs, rt, rd, sa;
        string function;
        rs = binary_to_int(machine_code.substr(6, 5));
        rt = binary_to_int(machine_code.substr(11, 5));
        rd = binary_to_int(machine_code.substr(16, 5));
        sa = binary_to_int(machine_code.substr(21, 5));
        function = inverted_r_type_function[machine_code.substr(26, 6)];
        if(function == "add"){
            computer.registers[rd] = sign32(computer.registers[rs]) + sign32(computer.registers[rt]);
        } else if(function == "addu"){
            computer.registers[rd] = computer.registers[rs] + computer.registers[rt];
        } else if(function == "and"){
            computer.registers[rd] = computer.registers[rs] & computer.registers[rt];
        } else if(function == "div"){
            computer.registers[lo] = computer.registers[rs] / computer.registers[rt];
            computer.registers[hi] = computer.registers[rs] % computer.registers[rt];
        } else if(function == "divu"){
            computer.registers[lo] = computer.registers[rs] / computer.registers[rt];
            computer.registers[hi] = computer.registers[rs] % computer.registers[rt];
        } else if(function == "jalr"){
            computer.registers[rd] = PC + 1;
            PC = computer.registers[rs] - 1;
        } else if(function == "jr"){
            PC = computer.registers[rs] - 1;
        } else if(function == "mfhi"){
            computer.registers[rd] = computer.registers[hi];
        } else if(function == "mflo"){
            computer.registers[rd] = computer.registers[lo];
        } else if(function == "mthi"){
            computer.registers[hi] = computer.registers[rs];
        } else if(function == "mtlo"){
            computer.registers[lo] = computer.registers[rs];
        } else if(function == "mult"){
            int64_t temp = (int64_t)((int64_t)computer.registers[rs] * (int64_t)computer.registers[rt]);
            computer.registers[hi] = stoi(bitset<64>(temp).to_string().substr(0, 32), 0, 2);
            computer.registers[lo] = stoi(bitset<64>(temp).to_string().substr(32, 32), 0, 2);
        } else if(function == "multu"){
            int64_t temp = (int64_t)((int64_t)computer.registers[rs] * (int64_t)computer.registers[rt]);
            computer.registers[hi] = stoi(bitset<64>(temp).to_string().substr(0, 32), 0, 2);
            computer.registers[lo] = stoi(bitset<64>(temp).to_string().substr(32, 32), 0, 2);
        } else if(function == "nor"){
            computer.registers[rd] = ~(computer.registers[rs] | computer.registers[rt]);
        } else if(function == "or"){
            computer.registers[rd] = computer.registers[rs] | computer.registers[rt];
        } else if(function == "sll"){
            computer.registers[rd] = computer.registers[rt] << sa;
        } else if(function == "sllv"){
            computer.registers[rd] = computer.registers[rt] << computer.registers[rs];
        } else if(function == "slt"){
            computer.registers[rd] = (sign32(computer.registers[rs]) < sign32(computer.registers[rt]) ? 1 : 0);
        } else if(function == "sltu"){
            computer.registers[rd] = (computer.registers[rs] < computer.registers[rt] ? 1 : 0);
        } else if(function == "sra"){
            computer.registers[rd] = computer.registers[rt] >> sa;
        } else if(function == "srav"){
            computer.registers[rd] = computer.registers[rt] >> computer.registers[rs];
        } else if(function == "srl"){
            computer.registers[rd] = computer.registers[rt] >> sa;
        } else if(function == "srlv"){
            computer.registers[rd] = computer.registers[rt] >> computer.registers[rs];
        } else if(function == "sub"){
            computer.registers[rd] = sign32(computer.registers[rs]) - sign32(computer.registers[rt]);
        } else if(function == "subu"){
            computer.registers[rd] = computer.registers[rs] - computer.registers[rt];
        } else if(function == "xor"){
            computer.registers[rd] = computer.registers[rs] ^ computer.registers[rt];
        } else {
            return "[Error] unknown instruction occurs, found: " + function;
        }
    } else if(machine_code.substr(0, 5) != "00001"){
        string opcode;
        int rs, rt, immediate;
        opcode = inverted_i_type_opcode[machine_code.substr(0, 6)];
        rs = binary_to_int(machine_code.substr(6, 5));
        rt = binary_to_int(machine_code.substr(11, 5));
        immediate = binary_to_int(machine_code.substr(16, 16));
        if(opcode == "addi"){
            computer.registers[rt] = sign32(computer.registers[rs]) + sign16(immediate);
        } else if(opcode == "addiu"){
            computer.registers[rt] = computer.registers[rs] + immediate;
        } else if(opcode == "andi"){
            computer.registers[rt] = computer.registers[rs] & immediate;
        } else if(opcode == "beq"){
            if(computer.registers[rs] == computer.registers[rt])
                PC += sign16(immediate);
        } else if((opcode == "bgez" || opcode == "bltz") && rt == 1){
            if(computer.registers[rs] >= 0)
                PC += sign16(immediate);
        } else if(opcode == "bgtz"){
            if(computer.registers[rs] > 0)
                PC += sign16(immediate);
        } else if(opcode == "blez"){
            if(computer.registers[rs] <= 0)
                PC += sign16(immediate);
        } else if((opcode == "bltz" || opcode == "bgez") && rt == 0){
            if(computer.registers[rs] < 0)
                PC += sign16(immediate);
        } else if(opcode == "bne"){
            if(computer.registers[rs] != computer.registers[rt])
                PC += sign16(immediate);
        } else if(opcode == "lb"){
            if(!is_all_number(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate])){
                computer.blocks[computer.registers[rt] / 4] = split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate];
                computer.registers[rt] = computer.registers[rs];
            } else {
                computer.registers[rt] = sign32(stoi(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate]));
            }
        } else if(opcode == "lbu"){
            if(!is_all_number(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate])){
                computer.blocks[computer.registers[rt] / 4] = split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate];
                computer.registers[rt] = computer.registers[rs];
            } else {
                computer.registers[rt] = stoi(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate]);
            }
        } else if(opcode == "lh"){
            if(!is_all_number(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate / 2])){
                computer.blocks[computer.registers[rt] / 4] = split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate / 2];
                computer.registers[rt] = computer.registers[rs];
            } else {
                computer.registers[rt] = sign32(stoi(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate / 2]));
            }
        } else if(opcode == "lhu"){
            computer.registers[rt] = stoi(split_string("|", computer.blocks[computer.registers[rs] / 4])[immediate / 2]);
        } else if(opcode == "lui"){
            computer.registers[rt] = (immediate << 16);
        } else if(opcode == "lw"){
            if(!is_all_number(computer.blocks[(computer.registers[rs] + sign16(immediate)) / 4])){
                computer.blocks[computer.registers[rt] / 4] = computer.blocks[(computer.registers[rs] + sign16(immediate)) / 4];
                computer.registers[rt] = computer.registers[rs];
            } else {
                computer.registers[rt] = stoi(computer.blocks[(computer.registers[rs] + sign16(immediate)) / 4]);
            }
        } else if(opcode == "ori"){
            computer.registers[rt] = computer.registers[rs] | immediate;
        } else if(opcode == "sb"){
            vector<string> split = split_string("|", computer.blocks[computer.registers[rs] / 4]);
            while(split.size() < 4) split.push_back("");
            if(computer.registers[rt] / 4 >= computer.data_start)
                split[immediate] = computer.blocks[computer.registers[rt] / 4];
            else
                split[immediate] = to_string(computer.registers[rt]);

            string str = "";
            for(int idx = 0; idx < (int)split.size(); ++idx){
                if(split[idx] == "") continue;
                if(idx != 0) str.push_back('|');
                str += split[idx];
            }
            computer.type[computer.registers[rs] / 4] = "byte";
            computer.blocks[computer.registers[rs] / 4] = str;
            computer.data_end = max(computer.data_end, (computer.registers[rs] + 4) / 4);
        } else if(opcode == "slti"){
            computer.registers[rt] = (sign32(computer.registers[rs]) < sign16(immediate) ? 1 : 0);
        } else if(opcode == "sltiu"){
            computer.registers[rt] = (computer.registers[rs] < immediate ? 1 : 0);
        } else if(opcode == "sh"){
            vector<string> split = split_string("|", computer.blocks[computer.registers[rs] / 4]);
            while(split.size() < 2) split.push_back("");
            if(computer.registers[rt] / 4 >= computer.data_start)
                split[immediate / 2] = computer.blocks[computer.registers[rt] / 4];
            else
                split[immediate / 2] = to_string(computer.registers[rt]);
            string str = "";
            for(int idx = 0; idx < (int)split.size(); ++idx){
                if(split[idx] == "") continue;
                if(idx != 0) str.push_back('|');
                str += split[idx];
            }
            computer.type[computer.registers[rs] / 4] = "half";
            computer.blocks[computer.registers[rs] / 4] = str;
            computer.data_end = max(computer.data_end, (computer.registers[rs] + 4) / 4);
        } else if(opcode == "sw"){
            if(computer.registers[rt] / 4 >= computer.data_start){
                computer.type[(computer.registers[rs] + immediate) / 4] = "string";
                computer.blocks[(computer.registers[rs] + immediate) / 4] = computer.blocks[computer.registers[rt] / 4];
            } else {
                computer.type[(computer.registers[rs] + immediate) / 4] = "word";
                computer.blocks[(computer.registers[rs] + immediate) / 4] = to_string(computer.registers[rt]);
            }
            computer.data_end = max(computer.data_end, (computer.registers[rs] + immediate + 4) / 4);
        } else if(opcode == "xori"){
            computer.registers[rt] = computer.registers[rs] ^ immediate;
        } else if(opcode == "lwl"){
            immediate = sign16(immediate);
            int32_t address = (computer.registers[rs] + immediate) / 4;
            string str = bitset<32>(computer.registers[rt]).to_string();
            string bytes[4], converted_str[4];
            bytes[0] = str.substr(0, 8);
            bytes[1] = str.substr(8, 8);
            bytes[2] = str.substr(16, 8);
            bytes[3] = str.substr(24, 8);
            if(is_all_number(computer.blocks[address])){
                str = computer.blocks[address];
                while(str.size() < 4) str = "0" + str;
                str = bitset<32>(stoi(str)).to_string();
                for(int k = 0; k < 4; ++k){
                    converted_str[k] = str.substr(k * 8, 8);
                }
            } else {
                str = computer.blocks[address];
                while(str.size() < 4) str.push_back('0');
                for(int k = 0; k < 4; ++k){
                    string tmp = "";
                    tmp.push_back(str[k]);
                    converted_str[k] = bitset<8>(tmp).to_string();
                }
            }
            swap(converted_str[0], converted_str[3]);
            swap(converted_str[1], converted_str[2]);
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            for(int byte = ((immediate % 4) + 4) % 4, k = 0; byte < 4;){
                bytes[k++] = converted_str[byte++];
            }
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            str = "";
            for(int k = 0; k < 4; ++k) str += bytes[k];
            computer.registers[rt] = binary_to_int(str, true);
        } else if(opcode == "lwr"){
            immediate = sign16(immediate);
            int32_t address = (computer.registers[rs] + immediate) / 4;
            string str = bitset<32>(computer.registers[rt]).to_string();
            string bytes[4], converted_str[4];
            bytes[0] = str.substr(0, 8);
            bytes[1] = str.substr(8, 8);
            bytes[2] = str.substr(16, 8);
            bytes[3] = str.substr(24, 8);
            if(is_all_number(computer.blocks[address])){
                str = computer.blocks[address];
                while(str.size() < 4) str = "0" + str;
                str = bitset<32>(stoi(str)).to_string();
                for(int k = 0; k < 4; ++k){
                    converted_str[k] = str.substr(k * 8, 8);
                }
            } else {
                str = computer.blocks[address];
                while(str.size() < 4) str.push_back('0');
                for(int k = 0; k < 4; ++k){
                    string tmp = "";
                    tmp.push_back(str[k]);
                    converted_str[k] = bitset<8>(tmp).to_string();
                }
            }
            swap(converted_str[0], converted_str[3]);
            swap(converted_str[1], converted_str[2]);
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            for(int byte = ((immediate % 4) + 4) % 4, k = 3; byte >= 0;){
                bytes[k--] = converted_str[byte--];
            }
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            str = "";
            for(int k = 0; k < 4; ++k) str += bytes[k];
            computer.registers[rt] = binary_to_int(str, true);
        } else if(opcode == "swl"){
            immediate = sign16(immediate);
            int32_t address = (computer.registers[rs] + immediate) / 4;
            string str = bitset<32>(computer.registers[rt]).to_string();
            string bytes[4], converted_str[4];
            bytes[0] = str.substr(0, 8);
            bytes[1] = str.substr(8, 8);
            bytes[2] = str.substr(16, 8);
            bytes[3] = str.substr(24, 8);
            if(is_all_number(computer.blocks[address])){
                str = computer.blocks[address];
                while(str.size() < 4) str = "0" + str;
                str = bitset<32>(stoi(str)).to_string();
                for(int k = 0; k < 4; ++k){
                    converted_str[k] = str.substr(k * 8, 8);
                }
            } else {
                str = computer.blocks[address];
                while(str.size() < 4) str.push_back('0');
                for(int k = 0; k < 4; ++k){
                    string tmp = "";
                    tmp.push_back(str[k]);
                    converted_str[k] = bitset<8>(tmp).to_string();
                }
            }
            swap(converted_str[0], converted_str[3]);
            swap(converted_str[1], converted_str[2]);
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            for(int byte = ((immediate % 4) + 4) % 4, k = 0; byte < 4;){
                converted_str[byte++] = bytes[k++];
            }
            str = "";
            for(int k = 0; k < 4; ++k) str += converted_str[k];
            computer.type[address] = "word";
            computer.blocks[address] = str;
        } else if(opcode == "swr"){
            immediate = sign16(immediate);
            int32_t address = (computer.registers[rs] + immediate) / 4;
            string str = bitset<32>(computer.registers[rt]).to_string();
            string bytes[4], converted_str[4];
            bytes[0] = str.substr(0, 8);
            bytes[1] = str.substr(8, 8);
            bytes[2] = str.substr(16, 8);
            bytes[3] = str.substr(24, 8);
            if(is_all_number(computer.blocks[address])){
                str = computer.blocks[address];
                while(str.size() < 4) str = "0" + str;
                str = bitset<32>(stoi(str)).to_string();
                for(int k = 0; k < 4; ++k){
                    converted_str[k] = str.substr(k * 8, 8);
                }
            } else {
                str = computer.blocks[address];
                while(str.size() < 4) str.push_back('0');
                for(int k = 0; k < 4; ++k){
                    string tmp = "";
                    tmp.push_back(str[k]);
                    converted_str[k] = bitset<8>(tmp).to_string();
                }
            }
            swap(converted_str[0], converted_str[3]);
            swap(converted_str[1], converted_str[2]);
            swap(bytes[0], bytes[3]);
            swap(bytes[1], bytes[2]);
            for(int byte = ((immediate % 4) + 4) % 4, k = 3; byte >= 0;){
                converted_str[byte--] = bytes[k--];
            }
            str = "";
            for(int k = 0; k < 4; ++k) str += converted_str[k];
            computer.type[address] = "word";
            computer.blocks[address] = str;
        } else {
            return "[Error] unknown instruction occurs, found: " + opcode;
        }
    } else if(machine_code.substr(0, 5) == "00001"){
        if(machine_code[5] == '1'){
            computer.registers[31] = PC + 1;
        }
        PC = (int32_t) binary_to_int(machine_code.substr(6, 26)) - 1;
    } else {
        return "[Error] unknown machine code occurs, found: " + machine_code;
    }

    return "Success";
}
