#include <iostream>
using namespace std;

int data[100005];
int main() {
  int j = 1, i, n, k;
  cin >> n >> k;
  for (i = 0; i < n; i++) {
    cin >> data[i];
  }
  while (k >= j) {
    k = k - j;
    j++;
  }
  if (k == 0) {
    k = k + j - 1;
  }
  cout << data[k - 1] << endl;
}