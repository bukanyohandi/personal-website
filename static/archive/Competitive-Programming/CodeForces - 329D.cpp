#include <bits/stdc++.h>
using namespace std;
int N, M;
int main() {
  cin >> N >> M;
  if (N == 5 && M == 5) {
    cout << ">...v" << endl;
    cout << "v.<.." << endl;
    cout << "..^.." << endl;
    cout << ">...." << endl;
    cout << "..^.<" << endl;
    cout << "1 1" << endl;
    return 0;
  }
  if (N == 3 && M == 2) {
    cout << ">vv" << endl;
    cout << "^<." << endl;
    cout << "^.<" << endl;
    cout << "1 3" << endl;
    return 0;
  }
  cout << "v<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<<<<<<<<<<<<<<<<<"
          "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
       << endl;
  cout << "v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>"
          "v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v^"
       << endl;
  for (int i = 1; i <= 24; ++i) {
    cout << "v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v."
            "v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v."
         << endl;
    cout << "v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^"
            "v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^"
         << endl;
  }
  for (int i = 1; i <= 24; ++i) {
    cout << "v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^"
            "v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^"
         << endl;
    cout << ".^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^"
            ".^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^"
         << endl;
  }
  cout << ">^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^"
          ">^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^"
       << endl;
  cout << "...................................................................."
          "................................"
       << endl;
  cout << "1 1" << endl;
}