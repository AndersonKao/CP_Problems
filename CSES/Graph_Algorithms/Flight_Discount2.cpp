#include <bits/stdc++.h>
using namespace std;
#define MAXDIS 1000000000000000
using LL = long long;
using PLL = pair<LL, LL>;
using edge = pair<int, LL>;
using pqE = tuple<LL, bool, int>;
int N, M;
vector<PLL> dis;
vector<vector<edge>> G;
void Dijsktra(){
    priority_queue<pqE, vector<pqE>, greater<pqE>> pq;
    dis[0].first = dis[0].second = 0;
    pq.emplace(0, false, 0);
    int u, v;
    LL w, d;
    bool free;
    while(!pq.empty()){
        tie(w, free, u) = pq.top();
        pq.pop();
        if(w != (free? dis[u].second : dis[u].first))
            continue;
        for(edge& e: G[u]){
            tie(v, d) = e;
            if(free){
                if(dis[v].second > dis[u].second + d){
                    dis[v].second = dis[u].second + d;
                    pq.emplace(dis[v].second, true, v);
                }
            }else{
                if(dis[v].first > dis[u].first + d){
                    dis[v].first = dis[u].first + d;
                    pq.emplace(dis[v].first, false, v);
                }
                if(dis[v].second > dis[u].first + d/2){
                    dis[v].second= dis[u].first + d/2;
                    pq.emplace(dis[v].second, true, v);
                }
            }
        } 
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int u, v;
    LL w;
    G.resize(N);
    dis.resize(N, PLL(MAXDIS, MAXDIS));
 
    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        u--, v--;
        G[u].emplace_back(v, w);
    }
    Dijsktra();
        /*
        for (int i = 0; i < N; i++){
            cout << i << ": " << dis[i].first << ", " << dis[i].second << "\n";
        }
 
*/
    cout << min(dis[N - 1].first, dis[N - 1].second) << endl;
 
    return 0;
}