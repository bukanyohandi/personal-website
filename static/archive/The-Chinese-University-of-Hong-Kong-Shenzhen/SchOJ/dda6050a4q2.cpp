// idk anymore :<

#include <bits/stdc++.h>
using namespace std;

int p[100];
set<int> st;

int find(int x){
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

int mst(int n, int m, vector<int> &u, vector<int> &v, vector<int> &w, int exc){
    for(int i = 0; i < n; ++i){
        p[i] = i;
    }
    priority_queue<pair<int, pair<int, pair<int, int>>>> pq;
    for(int i = 0; i < m; ++i){
        if(i != exc){
            pq.push({-w[i], {i, {u[i], v[i]}}});
        }
    }

    int ans = 0;
    int last = -1;
    while(!pq.empty()){
        int cost = -pq.top().first;
        int nn = pq.top().second.first;
        int a = pq.top().second.second.first;
        int b = pq.top().second.second.second;
        pq.pop();
        if(find(a) == find(b)){
            if(exc == -1){
                if(last == cost)
                    st.insert(nn);
            }
            continue;
        }
        if(exc == -1){
            st.insert(nn);
            // cout << "> " << nn << endl;
            last = cost;
        }
        ans += cost;
        p[find(a)] = find(b);
    }

    return ans;
}

int main(){
    int n;
    cin >> n;

    int aa, bb, c;
    vector<int> u, v, w;
    while(cin >> aa >> bb >> c){
        u.push_back(aa);
        v.push_back(bb);
        w.push_back(c);
    }

    int m = (int)u.size();

    // int dist[105][105];
    // for(int i = 0; i < n; ++i){
    //     for(int j = 0; j < n; ++j){
    //         dist[i][j] = 100005;
    //     }
    // }
    // for(int i = 0; i < n; ++i){
    //     dist[i][i] = 0;
    // }
    // for(int i = 0; i < m; ++i){
    //     dist[u[i]][v[i]] = w[i];
    //     dist[v[i]][u[i]] = w[i];
    // }

    // for(int k = 0; k < n; ++k){
    //     for(int i = 0; i < n; ++i){
    //         for(int j = 0; j < n; ++j){
    //             dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    //         }
    //     }
    // }

    // vector<int> saved;
    // for(int i = 0; i < m; ++i){
    //     bool ok = true;
    //     for(int j = 0; j < n; ++j){
    //         if(dist[u[i]][j] + dist[j][v[i]] < w[i]){
    //             ok = false;
    //             break;
    //         }
    //     }
    //     if(ok){
    //         saved.push_back(i); //only need to find the "key" ones.
    //     }
    // }
    
    int ans = mst(n, m, u, v, w, -1);
    vector<bool> fs(m, true);
    for(int i = 0; i < m; ++i){
        if(mst(n, m, u, v, w, i) > ans){
            fs[i] = false;
        }
    }
    vector<int> saved;
    for(auto c: st){
        saved.push_back(c);
    }
    vector<int> a, b;
    for(int i = 0; i < (int)saved.size(); ++i){
        if(!fs[saved[i]]){
            a.push_back(saved[i]);
        } else {
            b.push_back(saved[i]);
        }
    }
    for(int i = 0; i < a.size(); ++i){
        if(i != 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    for(int i = 0; i < b.size(); ++i){
        if(i != 0) cout << " ";
        cout << b[i];
    }
    cout << endl;
}