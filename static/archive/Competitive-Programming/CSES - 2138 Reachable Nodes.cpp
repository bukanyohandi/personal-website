#include <bits/stdc++.h>
using namespace std;

bitset<50000> ans[50000];

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> degree(n, 0);
    vector<vector<int>> edge(n);
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        degree[u - 1] += 1;
        edge[v - 1].push_back(u - 1);
    }
    queue<int> topo;
    for(int i = 0; i < n; ++i){
        if(degree[i] == 0){
            topo.push(i);
            ans[i][i] = 1;
        }
    }
    while(!topo.empty()){
        int u = topo.front();
        topo.pop();

        for(auto v: edge[u]){
            degree[v] -= 1;
            ans[v] = ans[v] | ans[u];

            if(degree[v] == 0){
                topo.push(v);
                ans[v][v] = 1;
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(i != 0) cout << " ";
        cout << ans[i].count();
    }
    cout << endl;
}