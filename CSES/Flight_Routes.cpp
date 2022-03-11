// AC 	2022-02-25 19:10:53
// referred
// 當你從pq拿出點u的第i個最短路徑時，指向u的所有點v_i的前i個最短路徑都已經做完了
#include <bits/stdc++.h>
using namespace std;
#define MAXD 2000000000000
int T;
using LL = long long;
using edge = pair<LL, int>;
vector<priority_queue<LL>> dis;
void Dijkstra(int st, vector<vector<edge>>&G, int k){

    dis[0].emplace(0);

    priority_queue<edge, vector<edge>, greater<edge>> pq;
    int u, v;
    LL w, d;
    pq.emplace(0, 0);
    while(!pq.empty()){
        tie(d, u) = pq.top();
        pq.pop();
        if(d > dis[u].top())
            continue;
        for(edge& e: G[u]){
            tie(w, v) = e;
            LL value = d + w;
            if(dis[v].size() < k){
                dis[v].emplace(value);
                pq.emplace(value, v);
            }
            else if(value < dis[v].top()){ // dis[v].size only == k
                dis[v].pop();
                dis[v].emplace(value);
                pq.emplace(value, v);
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M, k;
    cin >> N >> M >> k;
    vector<vector<edge>> G(N);
    dis.resize(N);
    int u, v;
    LL w;
    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        u--, v--;
        G[u].emplace_back(w, v);
    }
    Dijkstra(0, G, k);
    stack<LL> ans;
    while(dis[N-1].size()){
        ans.emplace(dis[N - 1].top());
        dis[N - 1].pop();
    }
    while(ans.size()){
        cout << ans.top() << (ans.size() == 1 ? "\n" : " ");
        ans.pop();
    }

    return 0;
}