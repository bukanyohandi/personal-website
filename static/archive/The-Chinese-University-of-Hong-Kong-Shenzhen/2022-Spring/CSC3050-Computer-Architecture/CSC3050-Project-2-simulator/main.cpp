/*
 * Project 2 - MIPS Simulator
 *
 *      Author:     Yohandi (120040025)
 *        Date:          3/20/22
 */

#include <iostream>
#include "phase1.h"
#include "phase2.h"
#include "checkpoints.h"
using namespace std;

int ins_count = 0;
memory computer;
int32_t dynamic_address;
vector<int> checkpointss;
map<int, memory> computer_state;

void print(){

    for(auto i: checkpointss){
        checkpoint2(i, computer_state[i]);
    }
    for(auto i: checkpointss){
        checkpoint(i, computer_state[i]);
    }

}

int main(int argc, char **argv){
    if(argc < 6){
        cerr << "[Error] lack of input validation" << endl;
        exit(1);
    }

    string assembly_file, assembled_binary_file, checkpoint_file, input_file, output_file;
    assembly_file = argv[1];
    assembled_binary_file = argv[2];
    checkpoint_file = argv[3];
    input_file = argv[4];
    output_file = argv[5];

    init_memory();
    separate_data_type(assembly_file);
    separated_text_type(assembly_file);
    text_store(assembled_binary_file);

    init_inverted_map();

    dynamic_address = computer.data_end;

    ifstream ifs(input_file);
    ofstream ofs(output_file);

    init_checkpoint(checkpoint_file);

    int32_t PC = computer.text_start;
    computer.PC = PC * 4;
    if(is_checkpoint(ins_count)){
        computer_state[ins_count] = computer;
        checkpointss.push_back(ins_count);
    }
    ins_count++;
//    checkpoint(ins_count++);

    for(; PC < computer.text_end;){
        string result = execute(ifs, ofs, PC, computer.blocks[PC]);
        PC += 1;
        computer.PC = PC * 4;
        if(is_checkpoint(ins_count)){
            computer_state[ins_count] = computer;
            checkpointss.push_back(ins_count);
        }
        ins_count++;
//        checkpoint(ins_count++);

        if(result.substr(0, 4) == "Exit"){
            print();
            ifs.close();
            ofs.close();

            exit(stoi(result.substr(5)));
        }

        if(result != "Success"){
            print();
            cerr << result << endl;
            exit(1);
        }
    }

    print();
    ifs.close();
    ofs.close();

    return 0;
}
