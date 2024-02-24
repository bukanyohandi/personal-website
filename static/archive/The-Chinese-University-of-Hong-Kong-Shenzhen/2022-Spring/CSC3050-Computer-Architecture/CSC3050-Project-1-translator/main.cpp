/*
 * Project 1 - MIPS to Machine Code
 *
 *      Author:     Yohandi (120040025)
 *       Date:          2/28/22
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include "phase1.h"
#include "phase2.h"
#include "tester.h"
using namespace std;

int main(int argc, char **argv){
    if(argc < 4){
        cerr << "[Error] lack of input validation" << endl;
        exit(1);
    }

    string input_file, output_file, expected_output_file;
    input_file = argv[1];
    output_file = argv[2];
    expected_output_file = argv[3];
    ofstream ofs(output_file);

    vector<vector<string>> text;
    text = separated_text_type(input_file);

    int line_number = 1;
    vector<string> ans;
    for(auto argument: text){
        machine_code(ans, argument, line_number++);
    }

    for(auto returned_machine_code: ans){
        ofs << returned_machine_code << endl;
    }

    ofs.close();

    string result = compare_files(output_file, expected_output_file);
    cout << result << endl;

    return 0;
}
