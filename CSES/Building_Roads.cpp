// AC 2022-03-01 09:05:07
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> G;
vector<bool> vis;
using PII = pair<int, int>;
int last = -1;
void DFS(int now, int p){
    vis[now] = true;
    last = now;
    for(int& u: G[now]){
        if(u == p || vis[u])
            continue;
        DFS(u, now);
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    G.resize(N);
    vis.resize(N, false);
    int u, v;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    vector<PII> ANS;
    for (int i = 0; i < N; i++){
        if(!vis[i]){
            if(last != -1){
                ANS.emplace_back(last + 1, i + 1);
            }
            DFS(i, -1);
        }
    }
    cout << ANS.size() << endl;
    for(auto& e: ANS){
        cout << e.first << " " << e.second << endl;
    }
    return 0;
}