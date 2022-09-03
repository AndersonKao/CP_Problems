#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// O(V^2E) O(VE) finding argument path
// if unit capacity network then O(min(V^(2/3), E^1/2) E)
// solving bipartite matching O(E sqrt(V)) better than konig and flow(EV)

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
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

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
                
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        
        level[v] = -1;
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

const ll maxT = 10001; // |E| <= 10^4, and plus the last time.
ll mat[101][101];
int main(){
	int n;
	cin >> n;
	memset(mat, 0, sizeof(mat));
	Dinic mD(n+1, 0, n);
	for(int u = 0; u < n; u++){
		char K[10];
		cin >> K;
		if(K[0] == '*'){
			int v;
			cin >> v;
			v--;
			if(v == 0)
				v = n;
			mat[u][v] = maxT+1;
		}
		else{
			int k = atoi(K);
			for(int j = 0; j < k; j++){
				int v; 
				cin >> v;
				v--;
				if(v == 0)
					v = n;
				mat[u][v]++;
			}
		}
	}
	for(int u = 0; u < n; u++){
		for(int v = 0; v <= n; v++){
			if(mat[u][v] != 0){
				mD.add_edge(u, v, mat[u][v]);
			}
		}
	}
	ll ans = mD.flow();

	if(ans >= maxT){
		cout << "*\n";
	}
	else{
		cout << ans + 1<< endl;
	}
	return 0;
}

