/*
 * File: MergeSort.cpp
 * -------------------
 * This file implements the merge sort algorithm using arrays rather
 * than vectors.
 */

#include "MergeSort.h"

/*
 * Function: printArray
 * Usage: printArray(array, n);
 * ----------------------------
 * Prints the elements of the array on a single line with the elements
 * enclosed in braces and separated by commas.
 */

void printArray(int array[], int n) {
   cout << "{ ";
   for (int i = 0; i < n; i++) {
      if (i > 0) cout << ", ";
      cout << array[i];
   }
   cout << " }" << endl;
}

void sort(int array[], int n){
    if(n > 1){
        int half_size = n / 2;
        int first_half[half_size], second_half[n - half_size];

        for(int idx = 0; idx < half_size; ++idx){
            first_half[idx] = array[idx];
        }
        sort(first_half, half_size);

        for(int idx = half_size; idx < n; ++idx){
            second_half[idx - half_size] = array[idx];
        }
        sort(second_half, n - half_size);

        int first_pointer = 0;
        int second_pointer = 0;
        int pointer = 0;
        while(first_pointer < half_size && second_pointer < n - half_size){
            if(first_half[first_pointer] < second_half[second_pointer]){
                array[pointer++] = first_half[first_pointer++];
            } else {
                array[pointer++] = second_half[second_pointer++];
            }
        }
        while(first_pointer < half_size) array[pointer++] = first_half[first_pointer++];
        while(second_pointer < n - half_size) array[pointer++] = second_half[second_pointer++];
    }

    return;
}
