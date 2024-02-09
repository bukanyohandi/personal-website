#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;
int n;
double x, tmp1, tmp2;
int main() {
  priority_queue<double> bawah;
  priority_queue<double, vector<double>, greater<double>> atas;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> x;
    bawah.push(x);
    while (bawah.size() > atas.size()) {
      atas.push(bawah.top());
      bawah.pop();
    }
    while (atas.size() > 0 && bawah.size() > 0 && atas.top() < bawah.top()) {
      tmp1 = atas.top();
      tmp2 = bawah.top();
      atas.push(tmp2);
      bawah.push(tmp1);
      atas.pop();
      bawah.pop();
    }
    if ((bawah.size() + atas.size()) % 2 == 0) {
      cout << fixed << setprecision(1) << (bawah.top() + atas.top()) / 2
           << endl;
    } else {
      cout << fixed << setprecision(1) << atas.top() << endl;
    }
  }
}