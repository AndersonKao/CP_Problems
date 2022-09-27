// euler tour technique + RMQ.
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
int euler_tour[400000];
int fi[200000];
int h[200000];
int stamp = 0;
vec<int> G[200000];
void dfs(int u, int pa,int d){
	fi[u] = stamp;
	euler_tour[stamp++] = u;
	h[u] = d;
	for(int v: G[u]){
		if(v == pa) continue;
		dfs(v, u, d+1);
		euler_tour[stamp++] = u;
	}
}
int seq[1600000];
int min_vertex(int u, int v){
	if(u == -1)
		return v;
	if(v == -1)
		return u;
	return (fi[u] < fi[v] ? u : v);
}

void build(int l, int r, int* arr, int idx){
	if(l == r){
		seq[idx] = arr[l];
		return ;
	}
	int m = (l+r) >> 1;
	build(l, m, arr, idx*2 + 1);
	build(m+1, r, arr, idx*2 + 2);
	seq[idx] = min_vertex(seq[idx * 2 + 1], seq[idx * 2 + 2]);
}

int query(int l, int r, int ql, int qr, int idx){
	if(r < ql || qr < l){
		return -1;
	}
	if(ql <= l && r <= qr){
		return seq[idx];	
	}
	int m = (l + r) >> 1;
	return min_vertex(query(l, m, ql, qr, idx * 2 + 1), query(m+1, r, ql, qr, idx * 2 + 2));
}

int main(){
	int n, q;		
	cin >> n >> q;
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
		G[v].eb(u);
	}
	dfs(0, -1, 0);
	memset(seq, -1, sizeof(seq));
	build(0, stamp-1, euler_tour, 0);

	REP(i, q){
		int u, v;
		cin >> u >> v;
		u--, v--;
		if(fi[u] > fi[v]) swap(u, v);
		int lca = query(0, stamp-1, fi[u], fi[v], 0);
		cout << h[u] + h[v] - 2 * h[lca] << endl;
	}
	return 0;
}

