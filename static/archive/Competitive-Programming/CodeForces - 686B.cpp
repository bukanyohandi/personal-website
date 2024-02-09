#include <bits/stdc++.h>
using namespace std;
int data[105];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> data[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (data[j] > data[j + 1]) {
        swap(data[j], data[j + 1]);
        cout << j + 1 << " " << j + 2 << endl;
      }
    }
  }
}