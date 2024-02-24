/*
 * File: intarray.cpp
 * ------------------
 * This file inplements the intarray.h interface.
 */

#include "intarray.h"

IntArray::IntArray(int n){
    array = new int[n];
    for(int idx = 0; idx < n; ++idx){
        array[idx] = 0;
    }
    nElements = n;
}

IntArray::~IntArray(){
    delete[] array;
}

int IntArray::size(){
    return nElements;
}

int IntArray::get(int index){
    if(index >= nElements){
        cout << "[Error] index is outside the vector bounds" << endl;
        exit(1);
    }
    return array[index];
}

void IntArray::put(int index, int value){
    if(index >= nElements){
        cout << "[Error] index is outside the vector bounds" << endl;
        exit(1);
    }
    array[index] = value;
    return;
}

int &IntArray::operator[](int index){
    if(index >= nElements){
        cout << "[Error] index is outside the vector bounds" << endl;
        exit(1);
    }
    return array[index];
}

IntArray::IntArray(const IntArray & src){
    deepCopy(src);
}

IntArray &IntArray::operator=(const IntArray & src){
    if(this == &src)
        return *this;
    delete[] array;
    deepCopy(src);
    return *this;
}

void IntArray::deepCopy(const IntArray & src){
    nElements = src.nElements;

    int *tempArray = new int[nElements];
    for(int idx = 0; idx < nElements; ++idx){
        tempArray[idx] = src.array[idx];
    }

    array = tempArray;

    return;
}
