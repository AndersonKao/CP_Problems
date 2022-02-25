#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PLL = pair<LL, LL>;
using edge = pair<int, LL>;
int N, M;
vector<PLL> dis(10000);
vector<vector<edge>> G;
void Dijsktra(){
    priority_queue<pair<LL, int>> pq;
    pq.emplace(0, 0);
    int u, v;
    LL w, d;
    while(!pq.empty()){
        tie(u, w) = pq.top();
        for(edge& e: G[u]){
            tie(v, d) = e;
            if(dis[v].second > dis[u].second + d){
                dis[v].second = dis[u].second + d;
            }
            if(dis)
        } 
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int u, v;
    LL w;
    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }
    Dijsktra();


    return 0;
}