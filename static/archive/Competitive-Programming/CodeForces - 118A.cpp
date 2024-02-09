#include <bits/stdc++.h>
using namespace std;
string S;
char Vowel[] = {'A', 'O', 'Y', 'E', 'U', 'I', 'a', 'o', 'y', 'e', 'u', 'i'};
int main() {
  cin >> S;
  for (auto &i : S) {
    bool Ok = true;
    for (int j = 0; j < 12 && Ok; ++j) {
      if (i == Vowel[j]) {
        Ok = false;
      }
    }
    if (Ok) {
      if ('A' <= i && i <= 'Z')
        i += 'a' - 'A';
      cout << "." << i;
    }
  }
  cout << endl;
}