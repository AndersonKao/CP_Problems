#include <bits/stdc++.h>
using namespace std;
using LL = long long;
vector<vector<int>> G;
vector<int> d;
vector<LL> s;
vector<LL> ANS;
int N;
int preDFS(int now, int p, int depth){
    d[now] = depth;
    int size = 1;
    for(auto& u: G[now]){
        if(u == p)
            continue;
        size += preDFS(u, now, depth + 1);
    }
    return s[now] = size;
}
void ansDFS(int now, int p){
    for(auto& u: G[now]){
        if(u == p)
            continue;
        ANS[u] = ANS[now] + (N - s[u]) - s[u];
        ansDFS(u, now);
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N;
    int u, v;
    G.resize(N);
    d.resize(N, 0);
    s.resize(N, 0);
    ANS.resize(N);
    for (int i = 0; i < N - 1; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    preDFS(0, -1, 0);
    ANS[0] = 0;
    for (int i = 1; i < N; i++)
        ANS[0] += d[i];
    ansDFS(0, -1);
    for (int i = 0; i < N; i++)
    {
        cout << ANS[i] << (i == N - 1 ? "\n" : " ");
    }
    return 0;
}
