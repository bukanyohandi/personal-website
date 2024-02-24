/*
 * File: Combinatorics.cpp
 * -----------------------
 * This file implements the combinatorics.h interface.
 */

#include "Combinatorics.h"

int permutations(int n, int k){
    /*
     * P(n, k) = n! / (n - k)!
     *         = n * (n - 1) * ... * (n - k + 1)
     * -----------------------------------------
     * Idea: Use for loop to multiply those numbers.
     */

    int ans = 1;

    for(int i = 0; i < k; ++i){
        ans *= (n - i);
    }

    return ans;
}

int combinations(int n, int k){
    /*
     * C(n, k) = n! / ((n - k)! k!)
     *         = n * (n - 1) * ... * (n - k + 1) / (k * ... * 1)
     * ---------------------------------------------------------
     * Idea: Similar to permutation function, use for loop to
     *       multiply those numbers. To solve the denominator,
     *       use for loop to divide the numerator with each
     *       number.
     *
     * Note: This problem can be solved by using the help of the
     *       Euclidean algorithm. However, for small numbers of n
     *       and k, the help of the Euclidean algorithm is not
     *       necessary.
     */

    int ans = 1;

    for(int i = 0; i < k; ++i){
        ans *= (n - i);
    }

    for(int i = 1; i <= k; ++i){
        ans /= i;
    }

    return ans;
}
