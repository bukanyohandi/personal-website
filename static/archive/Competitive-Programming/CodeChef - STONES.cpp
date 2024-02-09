#include <iostream>
#include <string.h>
using namespace std;

int suka[1000005];

int main() {
  int g = 0, i, j, k, l, n;
  string s, d;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> s;
    cin >> d;
    for (k = 0; k < s.length(); k++) {
      for (l = 0; l < d.length(); l++) {
        if (d[l] == s[k]) {
          d[l] = '.';
          g++;
        }
      }
    }
    suka[i] = g;
    g = 0;
  }
  for (i = 0; i < n; i++) {
    cout << suka[i] << endl;
  }
}