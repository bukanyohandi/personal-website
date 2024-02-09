#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  n--;

  int week = n / 7;
  int day = n % 7;
  cout << week * 5 + min(day, 5) << endl;
}