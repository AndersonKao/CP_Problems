// AC 2022-03-01 09:34:35
#include <bits/stdc++.h>
using namespace std;

#define MAXD 1000000000
vector<vector<int>> G;
vector<bool> vis;
vector<int> dis, path;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vis.resize(N, false);
    G.resize(N);
    dis.resize(N, MAXD);
    path.resize(N, -1);
    int u, v;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    queue<int> Q;
    Q.emplace(0);
    vis[0] = true;
    dis[0] = 0;
    while(Q.size()){
        u = Q.front();
        Q.pop();
        for(int& v: G[u]){
            if(vis[v])
                continue;
            vis[v] = true;
            dis[v] = dis[u] + 1;
            path[v] = u;
            Q.emplace(v);
        }
    }
    if(vis[N-1] == false){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    stack<int> ANS;
    u = N - 1;
    while(u != 0){
        ANS.emplace(u + 1);
        u = path[u];
    }
    ANS.emplace(1);
    cout << ANS.size() << endl;
    while(ANS.size()){
        cout << ANS.top() << (ANS.size() == 1 ? "\n" : " ");
        ANS.pop();
    }

    return 0;
}