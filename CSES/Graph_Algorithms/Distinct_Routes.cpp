// AC
// pop_back before dfs down.
// otherwise something like 2->5, 5->2 will cause inf loop.
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

// O(u^2E) O(VE) finding argument path
// if unit capacity network then O(min(u^(2/3), E^1/2) E)
// solving bipartite matching O(E sqrt(u)) better than konig and flow(EV)

struct FlowEdge {
    int u, v;
    long long cap, flow = 0;
    FlowEdge(int u, int v, long long cap) : u(u), v(v), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, long long cap) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].v] != -1) continue;
                level[edges[id].v] = level[u] + 1;
                q.push(edges[id].v);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, long long pushed) {
        if (pushed == 0) return 0;
        if (u == t) return pushed;
        
        for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
            int id = adj[u][cid];
            int v = edges[id].v;
            if (level[u] + 1 != level[v] || edges[id].cap - edges[id].flow < 1)
                continue;
                
            long long tr = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
            
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        
        level[u] = -1;
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
int cnt = 0;
void dfs(int u,vec<vec<int>>& G, vec<int>& ansV){
	ansV.eb(u);
	if(u == G.size()-1)
		return;
	int v = G[u].back();
	G[u].pop_back();
	dfs(v, G, ansV);
}
int main(){
	int n, m;
	cin >> n >> m;
	Dinic mF(n, 0, n-1);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		mF.add_edge(u-1, v-1, 1);
	}
	cout << mF.flow() << endl;
	vec<vec<int>> G(n);
	for(FlowEdge& e: mF.edges){
		if(e.flow == 1 && e.cap == 1){
			G[e.u].eb(e.v);
		}
	}
	/*
	for(int u = 0; u < n; u++){
		cout << u+1 << ": ";
		for(int v: G[u]){
			cout << v + 1 << " ";
		}
		cout << endl;
	}
	*/
	while(G[0].size()){
		vec<int> ansV;
		cnt = 0;
		dfs(0, G, ansV);
		cout << ansV.size() << endl;
		for(int u: ansV){
			cout << u +1 << " ";
		}
		cout << endl;
	}
		
	return 0;
}

