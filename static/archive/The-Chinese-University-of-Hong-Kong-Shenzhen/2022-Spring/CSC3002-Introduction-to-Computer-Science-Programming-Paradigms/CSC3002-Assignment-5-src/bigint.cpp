/*
 * File: bigint.cpp
 * ----------------
 * This file implements the bigint.h interface.
 */

#include <cctype>
#include <string>
#include "bigint.h"
#include "error.h"
using namespace std;

/*
 * Implementation notes: BigInt constructor
 * ----------------------------------------
 * The code for this constructor offers a minimal implementation
 * that matches what we would expect on an exam.  In a more
 * sophisticated implementation, it would make sense to include
 * a test to avoid storing leading zeros in the linked list.  In
 * this implementation, calling BigInt("00042") creates a
 * BigInt with a different internal representation than
 * BigInt("42"), which is probably a bad idea.
 */

string reverse_string(string str){
    string ret = "";
    while(str.length() > 0){
        ret.push_back(str.back());
        str.pop_back();
    }
    return ret;
}

BigInt::BigInt(string str) {
    string tmp;
    start = new Cell();
    Cell *current = start;

    str = reverse_string(str);
    while(str.back() == '0') str.pop_back();
    str = reverse_string(str);

    for(; !str.empty(); str.pop_back()){
        current -> finalDigit = (int)(str.back() - '0');
        current -> leadingDigits = new Cell();
        current = current -> leadingDigits;
    }
}

/*
 * Implementation notes: BigInt destructor
 * ---------------------------------------
 * The code for the destructor is similar to that of the other
 * classes that contain a linked list.  You need to store the
 * pointer to the next cell temporarily so that you still have
 * it after you delete the current cell.
 */

BigInt::~BigInt() {
    Cell *current = start;
    while(current != NULL){
        Cell *tmp = current -> leadingDigits;
        delete current;
        current = tmp;
    }
}



/*
 * Implementation notes: toString
 * ------------------------------
 * This method could also be written as a wrapper method that
 * calls a recursive function that creates the reversed string
 * one character at a time.
 */

string BigInt::toString() const {
    string ret = "", tmp = "";
    Cell *current = start;

    while(current != NULL && current -> leadingDigits != NULL){
        tmp.push_back((char)(current -> finalDigit + '0'));
        current = current -> leadingDigits;
    }
    for(; !tmp.empty(); tmp.pop_back()){
        ret.push_back(tmp.back());
    }

    return ret;
}

/*
 * Implementation notes: operator+ and operator*
 * ------------------------------
 * Implement operator+ and operator*, make BigInt surpport addition and
 * multiplication.
 */

BigInt BigInt::operator+(const BigInt & b2) const {
    string  p = reverse_string(toString()),
            q = reverse_string(b2.toString()),
            ret = "";
    int     len_p = p.length(),
            len_q = q.length(),
            sum = 0,
            carry = 0;
    if(len_p > len_q) swap(p, q);

    for(int idx = 0; idx < len_q; ++idx){
        sum = (q[idx] + carry);
        if(idx < len_p) sum += p[idx];
        ret.push_back((char)(sum % 10 + '0'));
        carry = sum % 10;
    }
    if(carry > 0) ret.push_back((char)(carry + '0'));

    while(ret.back() == '0') ret.pop_back();

    return BigInt(reverse_string(ret));
}

BigInt BigInt::operator*(const BigInt & b2) const {
    string  p = reverse_string(toString()),
            q = reverse_string(b2.toString()),
            ret = "";
    int     len_p = p.length(),
            len_q = q.length(),
            carry = 0;
    int *result = new int[len_p + len_q];

    for(int idx = 0; idx < len_p + len_q; ++idx){
        result[idx] = 0;
    }

    for(int i = 0; i < len_p; ++i){
        for(int j = 0; j < len_q; ++j){
            result[i + j] += (p[i] - '0') * (q[j] - '0');
        }
    }
    for(int idx = 0; idx < len_p + len_q; ++idx){
        int tmp = result[idx];
        result[idx] = (tmp + carry) % 10;
        carry = (tmp + carry) / 10;

        ret.push_back((char)(result[idx] + '0'));
    }
    while(ret.back() == '0') ret.pop_back();

    return BigInt(reverse_string(ret));
}

