/*
 * File: morsecode.cpp
 * -------------------
 * This file implements the morsecode.h interface.
 */
#include <iostream>
#include <string>
#include "error.h"
#include "map.h"
#include "simpio.h"
#include "strlib.h"
#include "console.h"
#include "morsecode.h"
using namespace std;

std::string translateLettersToMorse(std::string line){
    /*
     * Idea: Since it only requires each character converting
     *       to translate the letters to morse, simply do a
     *       for loop and convert each character that is an
     *       alphabet.
     */

    string ans = "";
    for(auto ch: line)
        if(ch >= 'A' && ch <= 'Z')
            ans += LETTERS_TO_MORSE[string(1, ch)] + " ";
    ans.pop_back();
    return ans;
}

std::string translateMorseToLetters(std::string line){
    /*
     * Idea: The case of translating morse to letters is a bit
     *       tricky compared to translating letters to morse.
     *       Since each morse code is separated by a space,
     *       push each character to a temporary string, any
     *       other characters will be ignored. After finding a
     *       space, push the converted morse code to letters.
     *       Unknown code will be converted as a question mark ("?").
     */

    string ans = "", tmp = "";
    line += " ";
    for(auto ch: line){
        if(ch == '.' || ch == '-'){
            tmp.push_back(ch);
        } else if(ch == ' '){
            if(MORSE_TO_LETTERS.containsKey(tmp)){
                ans += MORSE_TO_LETTERS[tmp];
            } else {
                ans += "?";
            }
            tmp = "";
        }
    }
    return ans;
}

Map<string,string> createMorseCodeMap() {
   Map<string,string> map;
   map["A"] = ".-";
   map["B"] = "-...";
   map["C"] = "-.-.";
   map["D"] = "-..";
   map["E"] = ".";
   map["F"] = "..-.";
   map["G"] = "--.";
   map["H"] = "....";
   map["I"] = "..";
   map["J"] = ".---";
   map["K"] = "-.-";
   map["L"] = ".-..";
   map["M"] = "--";
   map["N"] = "-.";
   map["O"] = "---";
   map["P"] = ".--.";
   map["Q"] = "--.-";
   map["R"] = ".-.";
   map["S"] = "...";
   map["T"] = "-";
   map["U"] = "..-";
   map["V"] = "...-";
   map["W"] = ".--";
   map["X"] = "-..-";
   map["Y"] = "-.--";
   map["Z"] = "--..";
   return map;
}


Map<std::string,std::string> invertMap(const Map<std::string,std::string> & map){
    /*
     * Idea: Inverting a map requires a loop of the entire
     *       contents inside the target map. Since the target
     *       map contains only each capitalized alphabet from
     *       A to Z, simply revert it back by filling each key
     *       with a specific alphabet key value.
     */

    Map<string, string> inverted_map;
    for(char ch = 'A'; ch <= 'Z'; ++ch){
        inverted_map[map[string(1, ch)]] = string(1, ch);
    }
    return inverted_map;
}
