#include <bits/stdc++.h>
using namespace std;
int N, M, Le, Ri, Index, X, Now;
int P[300003];
vector<int> Ans;
pair<int, int> Val;
pair<int, int> Arr[300003], Order[300003];
pair<pair<int, int>, pair<int, int>> tmp;
pair<pair<int, int>, pair<int, int>> Tree[1200012];
pair<pair<int, int>, pair<int, int>>
Merge(pair<pair<int, int>, pair<int, int>> A,
      pair<pair<int, int>, pair<int, int>> B) {
  pair<pair<int, int>, pair<int, int>> Ret, OA = A, OB = B;
  if (A.first.second != -1 && A.first.second != -1 &&
      (Arr[A.first.second].first == Arr[B.first.second].first)) {
    swap(A.second, B.second);
    Ret = max(A, B);
  } else {
    Ret = {max(A.first, B.first), min(A.first, B.first)};
  }
  return max(Ret, max(OA, OB));
}
pair<pair<int, int>, pair<int, int>> Build(int Low, int High, int Pos) {
  if (Low == High)
    return Tree[Pos] = {{0, -1}, {0, -1}};
  int Mid = (Low + High) / 2;
  return Tree[Pos] =
             Merge(Build(Low, Mid, 2 * Pos), Build(Mid + 1, High, 2 * Pos + 1));
}
pair<pair<int, int>, pair<int, int>> Update(int Low, int High, int Pos) {
  if (Low == High) {
    if (Val > Tree[Pos].first) {
      if (Tree[Pos].first.second == -1 ||
          Arr[Val.second].first != Arr[Tree[Pos].first.second].first)
        swap(Tree[Pos].second, Tree[Pos].first);
      Tree[Pos].first = Val;
    } else if (Val > Tree[Pos].second &&
               (Tree[Pos].first.second == -1 ||
                Arr[Val.second].first != Arr[Tree[Pos].first.second].first)) {
      Tree[Pos].second = Val;
    }
    return Tree[Pos];
  }
  int Mid = (Low + High) / 2;
  if (X <= Mid) {
    return Tree[Pos] = Merge(Update(Low, Mid, 2 * Pos), Tree[2 * Pos + 1]);
  } else {
    return Tree[Pos] = Merge(Tree[2 * Pos], Update(Mid + 1, High, 2 * Pos + 1));
  }
}
pair<pair<int, int>, pair<int, int>> Query(int Low, int High, int Pos) {
  if (High < Le || Ri < Low)
    return {{0, -1}, {0, -1}};
  if (Le <= Low && High <= Ri)
    return Tree[Pos];
  int Mid = (Low + High) / 2;
  return Merge(Query(Low, Mid, 2 * Pos), Query(Mid + 1, High, 2 * Pos + 1));
}
int main() {
  cin >> N >> M;
  for (int i = 1; i <= N; ++i)
    cin >> Arr[i].first >> Arr[i].second;
  for (int i = 1; i <= N; ++i)
    Order[i] = {Arr[i].second, -i};
  Build(1, N + 1, 1);
  sort(Order + 1, Order + N + 1);
  for (int i = 1; i <= N; ++i) {
    Index = -Order[i].second;
    Le = 1;
    Ri = Index;
    tmp = Query(1, N + 1, 1);
    if (Arr[tmp.first.second].first != Arr[Index].first) {
      P[Index] = tmp.first.second;
      X = Index + 1;
      Val = {tmp.first.first + 1, Index};
      Update(1, N + 1, 1);
    } else {
      P[Index] = tmp.second.second;
      X = Index + 1;
      Val = {tmp.second.first + 1, Index};
      Update(1, N + 1, 1);
    }
  }
  Le = 1;
  Ri = N + 1;
  Now = Query(1, N + 1, 1).first.second;
  while (Now != -1) {
    Ans.push_back(Now);
    Now = P[Now];
  }
  cout << Ans.size() << endl;
  for (int i = (int)Ans.size() - 1; i >= 0; --i) {
    cout << Ans[i] << " ";
  }
  cout << endl;
}