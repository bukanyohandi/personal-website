/*
** The holy #include <bits/stdc++.h>
*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#define endl '\n'
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
int tmp;
double n, h;
int main() {
  boost();
  cin >> n >> h;
  tmp = n;
  for (int i = 1; i < tmp; ++i) {
    cout << fixed << setprecision(12) << (double)i * h / sqrt(n * i);
    if (i != tmp - 1)
      cout << " ";
    else
      cout << endl;
  }
}