
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

vec<int> G[100001];
int backtrack[100001];
int visited[100001];

void DFS(vec<int>& rtopo, int u){
	visited[u] = true;
	for(int v: G[u]){
		if(!visited[v])
			DFS(rtopo, v);
	}
	rtopo.eb(u);
}

int main() {
	yccc;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
	}
	vec<int> topo;
	DFS(topo, 1);
	reverse(al(topo));
	vec<int> dis(n+1, 0);
	dis[1] = 1;
	for(int u: topo){
		for(int v: G[u]){
			if(dis[u] + 1 > dis[v]){
				dis[v] = dis[u] + 1;
				backtrack[v] = u;
			}
		}
	}

	if(dis[n] == 0){
		cout << "IMPOSSIBLE\n";
		return 0;
	}

	cout << dis[n] << endl;
	vec<int> btarr;
	int u = n;
	while(u != 0){
		btarr.eb(u);
		u = backtrack[u];
	}
	reverse(al(btarr));
	for(int u: btarr){
		cout << u << " ";
	}

	return 0;
}
