#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

const int maxn = 200001;
vector<int> G[maxn];
int pa[20][maxn];
int depth[maxn];
int dis[maxn]; // discover
int fin[maxn]; // finish
int ans[maxn];
// for paths that two endpoints are incomparable
int LCAat[maxn];
int endpointAt[maxn]; 
// for paths that endpoint is ancestor of another
int endAt[maxn]; 
int startAt[maxn];
int tstamp = 0;

void DFS(int u, int par, int d){
	if(u != 1){
		pa[0][u] = par;
	}
	depth[u] = d;
	dis[u] = tstamp++;
	for(int v: G[u]){
		if(v == par) continue;
		DFS(v, u, d+1);
	}
	fin[u] = tstamp++;
}

bool isAnc(int u, int v){ // is u an ancestor of v?
	return dis[u] <= dis[v] && fin[v] <= fin[u];
}

int lca(int u, int v){
	if(isAnc(u, v))
		return u;
	if(isAnc(v, u))
		return v;
	for(int i = 19; i >= 0; i--){
		if(pa[i][u] != 0 && !isAnc(pa[i][u], v)){
			u = pa[i][u];
		}
	}
	return pa[0][u];
}

int solve(int u){ // return active paths
	int active = 0;
	for(int v: G[u]){
		if(v == pa[0][u]){
			continue;
		}
		active += solve(v);
	}
	active += startAt[u];
	active += endpointAt[u];
	ans[u] = active - LCAat[u];
	active -= endAt[u];
	active -= LCAat[u] * 2;
	return active;
}

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
	}
	DFS(1, -1, 1);
	for(int k = 1; (1 << k) <= n; k++){
		for(int u = 1; u <= n; u++){
			pa[k][u] = pa[k-1][pa[k-1][u]];
		}
	}
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u>> v;
		if(isAnc(u, v)){
			startAt[v]++;
			endAt[u]++;
		}
		else if(isAnc(v, u)){
			startAt[u]++; endAt[v]++;
		}
		else{
			endpointAt[u]++;
			endpointAt[v]++;
			LCAat[lca(u, v)]++;
		}
	}

	solve(1);
	for(int u = 1; u <= n; u++){
		cout << ans[u] << (u == n ? '\n' : ' ');
	}

	return 0;
}
