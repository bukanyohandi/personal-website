#include <iostream>
using namespace std;
long long x, ans;
int main() {
  cin >> x;
  if (x > 11)
    ans = x / 11, x -= ans * 11, ans *= 2;
  if (x > 6)
    ans += 2;
  else if (x > 0)
    ans++;
  cout << ans << endl;
}