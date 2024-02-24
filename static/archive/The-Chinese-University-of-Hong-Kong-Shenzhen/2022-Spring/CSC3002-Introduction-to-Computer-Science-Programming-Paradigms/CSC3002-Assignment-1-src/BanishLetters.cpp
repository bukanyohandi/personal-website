/*
 * File: BanishLetters.cpp
 * -----------------------
 * This program removes all instances of a set of letters from
 * an input file.
 */

#include "BanishLetters.h"

void banishLetters(){
    /*
     * Idea: Prepare two strings, one for the lowercase letters and
     *       the other is for the uppercase letters that are to be
     *       banished. Then, read each character and compare it to
     *       every character in both strings. To solve the file, use
     *       the stream function provided by Stanford C++ Library.
     */

    string input_file, output_file, banished_letters;
    char current_char;

    cout << "Input file: ";
    getline(cin, input_file);
    cout << "Output file: ";
    getline(cin, output_file);
    cout << "Letters to banish: ";
    getline(cin, banished_letters);

    string uppercase_banished_letters = toUpperCase(banished_letters);
    string lowercase_banished_letters = toLowerCase(banished_letters);

    ifstream ifs;
    ifs.open(input_file);
    ofstream ofs(output_file);

    while(!ifs.eof()){
        ifs.get(current_char);
        bool banished = false;
        for(int i = 0; i < (int)banished_letters.length(); ++i){
            if(current_char == uppercase_banished_letters[i]) banished = true;
            if(current_char == lowercase_banished_letters[i]) banished = true;
        }
        if(banished != true){
            ofs << current_char;
        }
    }

    ifs.close();
    ofs.close();

    return;
}
