#include <iostream>
using namespace std;

int data[1000005] = {};
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> data[i];
    data[i]--;
    data[i] = (data[i] * (data[i] + 1)) / 2;
  }
  for (int i = 0; i < n; i++) {
    cout << data[i] << endl;
  }
}