/*
 * File: tester.cpp
 * ----------------
 * This file implements the tester.h interface.
 */

#include "tester.h"

string compare_files(string output_file, string expected_output_file){
    char ch1, ch2;
    string files = output_file + " and " + expected_output_file;
    FILE* out = fopen(output_file.c_str(), "r");
    FILE* expected_out = fopen(expected_output_file.c_str(), "r");

    do{
        ch1 = fgetc(out);
        ch2 = fgetc(expected_out);
        if(ch1 != ch2) return "Both " + files + " are not identical.";
    } while(ch1 != EOF && ch2 != EOF);

    if(ch1 != EOF || ch2 != EOF) return "Both " + files + " are not identical";

    fclose(out);
    fclose(expected_out);

    return "Both " + files + " are identical.";
}
