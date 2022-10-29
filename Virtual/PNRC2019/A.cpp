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
const int maxn = 100000;
struct edge{
	int u, v;
	ll w;
	edge(){}
	edge(int u, int v, int w):u(u), v(v), w(w){}
};

vec<edge> Es;
vec<int> G[maxn];
ll tval[maxn];
int sz[maxn] = {0};
ll Tsum[maxn] = {0};
ll Dsum[maxn] = {0};
ll Dpasum[maxn] = {0};
ll ans[maxn];
int n;
ll totalT = 0;

void addedge(int u, int v, int w){
	G[u].eb(Es.size());
	Es.eb(u, v, w);
	G[v].eb(Es.size());
	Es.eb(v, u, w);
}

int dfsz(int u, int pa){
	sz[u] = 1;
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		sz[u] += dfsz(Es[eid].v, u);
	}
	return sz[u];
}

void dfs_T(int u, int pa){
	Tsum[u] = tval[u];
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		dfs_T(Es[eid].v, u);
		Tsum[u] += Tsum[Es[eid].v];
	}
}

void dfs_D(int u, int pa){
	Dsum[u] = 0;
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		int v = Es[eid].v;
		dfs_D(Es[eid].v, u);
		Dsum[u] += Dsum[v];
		Dsum[u] += Es[eid].w * sz[v];
	}
}
void dfs_Dpa(int u, int pa){
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		int v = Es[eid].v;
		Dpasum[v] = Dsum[u] + Dpasum[u] - (Dsum[v] + Es[eid].w * sz[v]) + Es[eid].w * (n - sz[v]);
		dfs_Dpa(v, u);
	}
}

void dfs_ans0(int u, int pa, ll curd){
	ans[0] += (tval[0] + tval[u]) * curd;
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		int v = Es[eid].v;
		dfs_ans0(v, u, curd + Es[eid].w);
	}	
}

void dfs_ansall(int u, int pa){
//	ll Dall = Dpasum[u] + Dsum[u];
	for(int eid: G[u]){
		if(Es[eid].v == pa) continue;
		int v = Es[eid].v;
		ans[v] = ans[u];
		ll Dua = ( Dpasum[u] + Dsum[u] ) - (Dsum[v] + Es[eid].w * sz[v]);
		ans[v] += (tval[v] - tval[u]) * Dua ;
		ans[v] += tval[v] * (n - sz[v] - 1) * Es[eid].w;
		ans[v] += (totalT - Tsum[v] - tval[u]) * Es[eid].w;

		ll Dub = Dsum[v] + (Es[eid].w * (sz[v] - 1));
		ans[v] += (tval[v] - tval[u]) * Dub;
		ans[v] -= tval[v] * (sz[v] - 1) * Es[eid].w;
		ans[v] -= (Tsum[v] - tval[v]) * Es[eid].w;

		dfs_ansall(v, u);
	}	
}

int main(){
	cin >> n;	
	
	for(int i = 0; i < n; i++){
		cin >> tval[i];
		totalT += tval[i];
	}
	for(int i = 0; i < n-1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		addedge(u, v, w);
	}
	dfsz(0, 0);	
	dfs_T(0, 0);
	dfs_D(0, 0);
	dfs_Dpa(0, 0);

	dfs_ans0(0, 0, 0);
	dfs_ansall(0, 0);
	for(int u = 0; u < n; u++){
		cout << ans[u] << endl;
	}
	/*
	for(int u = 0; u < n; u++){
		debug(u);
		debug(tval[u]);
	}
	for(int u = 0; u < n; u++){
		debug(u);
		debug(sz[u]);
	}
	for(int u = 0; u < n; u++){
		debug(u);
		debug(Tsum[u]);
	}
	for(int u = 0; u < n; u++){
		debug(u);
		debug(Dsum[u]);
		debug(Dpasum[u]);
	}
	*/


	return 0;
}

