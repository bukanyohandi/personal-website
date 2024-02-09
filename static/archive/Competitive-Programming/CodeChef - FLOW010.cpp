#include <bits/stdc++.h>
using namespace std;
int T;
char C;
int main() {
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cin >> C;
    if (C == 'B' || C == 'b') {
      cout << "BattleShip" << endl;
    } else if (C == 'C' || C == 'c') {
      cout << "Cruiser" << endl;
    } else if (C == 'D' || C == 'd') {
      cout << "Destroyer" << endl;
    } else {
      cout << "Frigate" << endl;
    }
  }
}