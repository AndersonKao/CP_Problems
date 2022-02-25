// 
// WA
// 要注意不能已經走到N之後又在往前走
#include <bits/stdc++.h>
using namespace std;
#define DISMAX 10000000000000

/*
5 5 
1 2 3
2 3 -4
3 4 -2
4 2 3
3 5 6


8 9
1 2 1
2 3 1
3 4 1
4 2 1
1 8 1
5 8 1
5 6 1
6 7 1
7 5 1

*/

int N, M;
using LL = long long;
using edge = tuple<int, int, LL>;
vector<edge> E;
vector<vector<int>> G;
vector<bool> incycle;
vector<bool> Rroot; // Reachable from root.
vector<bool> visited;
vector<LL> dis;

bool DFS(int u){

    int st, ed;
    LL w;
    visited[u] = true;
    if(incycle[u] && Rroot[u])
        return true;
    bool ans = false;
    for(auto&e: G[u]){
        tie(ed, st, w) = E[e];
        if(st != u || visited[ed])
            continue;
        
        ans = (ans || DFS(ed));
    }
    return ans;
}
void Reaching(int u){
    int st, ed;
    LL w;
    Rroot[u] = true;
    for(auto &e:G[u]){
        tie(st, ed, w) = E[e];
        if(st != u || Rroot[ed])
            continue;
        DFS(ed);
        
    }
}


int main(){
    cin.tie(0); 
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int u, v;
    LL w;
    G.resize(N + 1);
    dis.resize(N + 1, DISMAX);
    Rroot.resize(N + 1, false);
    incycle.resize(N + 1, false);
    visited.resize(N + 1, false);
    dis[1] = 0;
    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        G[u].emplace_back(E.size());
        G[v].emplace_back(E.size());
        E.emplace_back(u, v, -w);
    }
    bool cycle = false;
    bool relaxed;
    for (int i = 0; i < N - 1; i++){
        for(auto &e: E){
            tie(u, v, w) = e;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
            }
        }
    }
    
    for(auto &e: E){
        tie(u, v, w) = e;
        if(dis[u] + w < dis[v]){
            cycle = true;
            incycle[u] = true;
            incycle[v] = true;
            //cout << u << ", " << v << " is in cycle!\n";
        }
    }
    if(cycle && DFS(N)){
        cout << -1 << endl;
    }
    else
        cout << -dis[N] << endl;


    return 0;
}


