#include <bits/stdc++.h>
using namespace std;
bool data[1000005];
int main() {
  string a, b;
  while (getline(cin, a) && getline(cin, b)) {
    int tmp = 0, na = 0, nb = 0, nanb = 0, best = 0;
    for (int i = 0; i < a.length(); ++i) {
      if (a[i] == ' ') {
        na++;
        data[tmp] = true;
        best = max(best, tmp);
        tmp = 0;
      } else {
        tmp = tmp * 10 + a[i] - '0';
      }
    }
    na++;
    data[tmp] = true;
    best = max(best, tmp);
    tmp = 0;
    for (int i = 0; i < b.length(); ++i) {
      if (b[i] == ' ') {
        nb++;
        if (data[tmp]) {
          nanb++;
        }
        data[tmp] = true;
        best = max(best, tmp);
        tmp = 0;
      } else {
        tmp = tmp * 10 + b[i] - '0';
      }
    }
    nb++;
    if (data[tmp])
      nanb++;
    best = max(best, tmp);
    if (na == nb && na == nanb) {
      cout << "A equals B" << endl;
    } else if (na == nanb) {
      cout << "A is a proper subset of B" << endl;
    } else if (nb == nanb) {
      cout << "B is a proper subset of A" << endl;
    } else if (nanb == 0) {
      cout << "A and B are disjoint" << endl;
    } else {
      cout << "I'm confused!" << endl;
    }
    for (int i = 0; i <= best; ++i) {
      data[i] = false;
    }
  }
}