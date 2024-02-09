#include <bits/stdc++.h>
using namespace std;
int data[1005];
int main() {
  int p1 = 0, p2 = 0, n, a, b;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> data[i];
  }

  a = 0;
  b = n - 1;
  if (a == b) {
    p1 += data[a];
  }
  while (a != b) {
    if (data[a] > data[b]) {
      p1 += data[a];
      a++;
    } else {
      p1 += data[b];
      b--;
    }
    if (a == b) {
      p2 += data[a];
      break;
    }
    if (data[a] > data[b]) {
      p2 += data[a];
      a++;
    } else {
      p2 += data[b];
      b--;
    }
    if (a == b) {
      p1 += data[a];
      break;
    }
  }
  cout << p1 << " " << p2 << endl;
}