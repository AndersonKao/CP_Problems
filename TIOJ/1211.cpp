#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define enp pair<int, int>
int N, M;
//#define LL long long
// int or ...
vector<pair<int, int>> G[10001];

int primMST(){
    bool visited[10001];
    std::fill(visited, visited + N + 1, false);
    int ans = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 1);
    int cnt = 0;
    while(!pq.empty())
    {
        int dis = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;
        // cout << "visiting " << u << endl;
        cnt++;
        ans += dis;
        visited[u] = true;
        for (int i = 0; i < G[u].size(); i++)
        // for(auto e: G[u])
        {
            int v = G[u][i].second;
            int w = G[u][i].first;
            if (visited[v])
                continue;
            pq.emplace(w, v);
        }
    }
    if(cnt != N)
        return -1;
    return ans;
}
int primMST2(){
    vector<bool> vis;
    vis.resize(N+1, false);
    vis[1] = true;
    priority_queue<enp,vector<enp>, greater<enp>> pq;
    for(auto e: G[1]){
        pq.emplace(e.first, e.second);
    }
    int ans = 0; // min value for MST
    int cnt = 1;
    while(pq.size()){
        int w, v; // edge-weight, vertex index
        tie(w, v) = pq.top();
        pq.pop();
        if(vis[v])
            continue;
        vis[v] = true;
        cnt++;
        ans += w;
        for(auto e: G[v]){
            if(!vis[e.second])
            	pq.emplace(e.first, e.second);
        }
    }
    
    return (cnt == N ? ans : -1);
}
struct DSU{
    int pa[10001];
    DSU(int N){
        for (int i = 0; i <= N; i++)
            pa[i] = i;
    }
    int find(int k) { return pa[k] = (pa[k] == k ? k : find(pa[k])); }
    void merge(int x, int y){
        int pax = find(x), pay = find(y);
        pa[pay] = pax;
    }
};
int kruskalMST(){
    DSU dsu(N);
    vector<tuple<int, int, int>> E; // w, u ,v
    for (int i = 1; i <= N; i++){
        for(auto e : G[i]){
            E.emplace_back(e.first, i, e.second);
        }
    }
    sort(E.begin(), E.end());
    int cnt = 0;
    int ans = 0;
    for(auto e: E){
        int w, u, v;
        tie(w, u, v) = e;
        if(dsu.find(u) == dsu.find(v))
            continue;
        ans += w;
        dsu.merge(u, v);
        cnt++;
        /*
        if(cnt == N-1)
            break;
        */
    }
    if(cnt != N-1)
        return -1;
    return ans;
}



int main(){
    while(true)
    {
        cin >> N >> M;
        if (N == 0 && M == 0)
            break;
        int u, v, w;
        for (int i = 0; i <= N; i++){
            G[i].clear();
        }
        for (int i = 0; i < M; i++)
        {
            cin >> u >> v >> w;
            G[u].emplace_back(w, v);
            G[v].emplace_back(w, u);
        }
        cout << primMST() << endl;
        //cout << primMST2() << endl;
        //cout << kruskalMST() << endl;
        
    }

    return 0;
}