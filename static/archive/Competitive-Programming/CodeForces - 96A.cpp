#include <iostream>
#include <string>
using namespace std;

int main() {
  size_t c;
  int d;
  d = 0;
  string s, s2, s3;
  s2 = "0000000";
  s3 = "1111111";
  cin >> s;
  c = s.find(s2);
  if (c != string::npos) {
    d++;
  }
  c = s.find(s3);
  if (c != string::npos) {
    d++;
  }

  if (d > 0) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
}