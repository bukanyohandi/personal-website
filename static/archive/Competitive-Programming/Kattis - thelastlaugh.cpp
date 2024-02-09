#include <bits/stdc++.h>
using namespace std;
set<int> Set;
bool Moved;
char Op;
int A, B;
int Pos[5], Dif[4], LSB[400004];
inline void Reset() {
  sort(Pos, Pos + 4);
  Set.clear();
  for (int i = 0; i < 3; ++i) {
    Dif[i] = Pos[i + 1] - Pos[i];
    Set.insert(LSB[Dif[i]]);
  }
}
inline void Move() {
  for (int i = 0; i < 4; ++i)
    if (Pos[i] == A)
      Pos[i] = B;
  Reset();
  Moved = 1;
  return;
}
int main() {
  for (int i = 1; i <= 400000; ++i)
    for (int j = i; j % 2 == 0; j /= 2)
      LSB[i]++;
  for (int i = 0; i < 4; ++i)
    cin >> Pos[i];
  Reset();
  if (Set.size() == 1) {
    cout << 2 << endl;
    cin >> Op;
    if (Op != 'D') {
      cin >> A >> B;
      Move();
    }
  } else {
    cout << 1 << endl;
  }
  while (Op != 'D') {
    Moved = 0;
    for (int i = 0; i < 3 && !Moved; ++i) {
      if (*Set.begin() < LSB[Dif[(i + 1) % 3]]) {
        for (int j = 0; j < 2 && !Moved; ++j) {
          if ((i + 1) % 3 == 2 - 2 * j ||
              (*Set.begin() < LSB[Dif[2 * j]] && (i + 1) % 3 != 2 * j) || j) {
            A = Pos[3 * j];
            B = Pos[(i + 1) % 3] + (1 << *Set.begin());
            Move();
            cout << "M " << A << " " << B << endl;
          }
        }
      }
    }
    cin >> Op;
    if (Op != 'D') {
      cin >> A >> B;
      Move();
    } else {
      return 0;
    }
  }
}