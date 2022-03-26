// AC 2022-02-22 13:44:02
// refer https://codeforces.com/blog/entry/79518
// WA
// backtrace 進負環這件事要等先判tail == -1之後才能進行
// WA
// 根本不對，DFS是錯的
#include <bits/stdc++.h>
using namespace std;

#define MAXD 0 
int N, M;
using LL = long long;
using PII = pair<int, int>;
using edge = tuple<int, int, LL>;

vector<vector<int>> G(2500);
vector<edge> E;
vector<LL> dis(2500, MAXD);
int baap[2500]; // where did shortest come from
int BellmanFord(){
    int u, v;
    LL w;
    int tail;
    for (int i = 0; i < N ; i++){
        tail = -1;
        for(edge &e: E){
            tie(u, v, w) = e;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                baap[v] = u;
                tail = v;
            }
        }
    }
    return tail;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int u, v;
    LL w;
    fill(baap, baap + N, -1);
    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        u--, v--;
        G[u].emplace_back(E.size());
        E.emplace_back(u, v, w);
    }
    int cycletail= BellmanFord();
    if (cycletail != -1)
    {
        cout << "YES\n";
        for (int i = 0; i < N; i++){
                cycletail = baap[cycletail]; // 走回負環裡面
        }
        int cnt = 0;
        stack<int> S;
        for (int u = cycletail;; u = baap[u])
        {
            S.emplace(u + 1);
            if (S.size() > 1 && u == cycletail)
                break;
        }
        while (!S.empty())
        {
            cout << S.top();
            S.pop();
            cout << (S.empty() ? '\n' : ' ');
        }
    }
    else
        cout << "NO\n";

    return 0;
}