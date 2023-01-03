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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
vec<int> G[50000];
bitset<50000> mask[50000];
bool vis[50000];
vec<int> topo; // topological order
void dfs(int u){
	vis[u] = true;
	for(int v: G[u]){
		if(!vis[v])
			dfs(v);
	}
	topo.eb(u);
}
int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	REP(i, m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
	}
	REP(u, n){
		mask[u].set(u);
		if(!vis[u]) dfs(u);
	}
	vec<int> ans(n);
	for(int u: topo){
		for(int v: G[u]){
			mask[u] |= mask[v];
		}
				ans[u] = mask[u].count();
	}
	REP(u, n){
		cout << ans[u] << " ";
	}
	return 0;
}

