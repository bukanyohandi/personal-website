#include <bits/stdc++.h>
using namespace std;
int data[20] = {2,  3,  4,  5,  7,  9,  11, 13, 17, 19,
                23, 25, 29, 31, 37, 41, 43, 47, 49},
    tmp;
string res;
int main() {
  tmp = 0;
  for (int i = 0; i < 19; ++i) {
    cout << data[i] << endl;
    cin >> res;
    if (res == "yes")
      tmp++;
    if (tmp > 1) {
      cout << "composite" << endl;
      return 0;
    }
  }
  cout << "prime" << endl;
  return 0;
}