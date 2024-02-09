#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  int cur = 0;
  scanf("%d", &t);
  // getchar();
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    // scanf("%s",&s);
    if (s[1] == '+') {
      cur++;
    } else {
      cur--;
    }
  }
  printf("%d\n", cur);
}