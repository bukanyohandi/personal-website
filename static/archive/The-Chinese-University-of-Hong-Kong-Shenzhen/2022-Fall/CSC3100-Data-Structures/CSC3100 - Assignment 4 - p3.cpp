/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

long long n, M;
long long a[2000], P[2000];
long long ans;
priority_queue<pair<long long, int>> edges;

int find(int u){
    if(P[u] == u) return u;
    return P[u] = find(P[u]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> M;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        P[i] = i;
    }

    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            edges.push({(a[i] * a[j]) % M, i * 2000 + j});
        }
    }

    while(!edges.empty()){
        pair<int, int> edge = edges.top();
        edges.pop();

        long long cost = edge.first;
        int u = edge.second / 2000;
        int v = edge.second % 2000;

        if(find(u) == find(v)) continue;

        P[find(u)] = find(v);
        ans += cost;
    }

    cout << ans << endl;
}