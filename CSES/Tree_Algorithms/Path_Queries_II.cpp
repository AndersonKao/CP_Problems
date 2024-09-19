#include <bits/stdc++.h>
using namespace std;
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 200001;
int val[maxn];
int seg[maxn*4];
vec<int> G[maxn];
int parent[maxn];
int heavy[maxn]; // the child on the other end of heavy edge
int depth[maxn];
int head[maxn];
int pos[maxn]; // position on segment tree;
int cur_pos = 1;;
int par[20][maxn];
int seq[maxn];
int tstamp = 0;
int D[maxn], L[maxn]; // discover time, leave time

int dfs(int u, int pa = 0, int d = 0){
	D[u] = tstamp++;
	parent[u] = pa;
	int size = 1;
	int max_c_size = 0;
	depth[u] = d;
	heavy[u] = 0;
	for(int v: G[u]){
		if(v == pa) continue;
		int c_size = dfs(v, u, d+1);
		if(c_size > max_c_size){
			max_c_size = c_size;
			heavy[u] = v;	
			size += c_size;
		}
	}
	L[u] = tstamp++;
	return size;
}

bool isAncestor(int u, int v){ // is u a an ancestor of v?
	return D[u] <= D[v] && L[v] <= L[u];
}

void decompose(int u, int h){
	head[u] = h, pos[u] = cur_pos++;
	if(heavy[u] != 0){
		decompose(heavy[u], h);
	}
	for(int v: G[u]){
		if(v != parent[u] && v != heavy[u]){
			decompose(v, v);
		}
	}
}

void segment_tree_build(int L, int R, int idx = 1){
	if(L == R){
		seg[idx] = seq[L];
		return;
	}
	if(R < L) return;
	int M = (L+R)>>1;
	segment_tree_build(L, M, idx * 2);
	segment_tree_build(M+1, R, idx * 2+1);
	seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}


int segment_tree_query(int l, int r, int L, int R, int idx = 1)
{
	if(L <= l && r <= R){
		return seg[idx];
	}
	if(R < l || r < L){
		return 0;
	}
	int M = (L+R)>>1;
	return max(segment_tree_query(l, r, L, M, idx * 2),
				segment_tree_query(l, r, M+1, R, idx * 2 + 1));
}

void segment_tree_modify(int pos, int x, int L, int R, int idx = 1){
	if(L == R){
		seg[idx] = x;
		return;
	}
	if(R < L)return;
	int M = (L+R)>>1;
	if(pos <= M)
		segment_tree_modify(pos, x, L, M, idx * 2);
	else
		segment_tree_modify(pos, x, M+1, R, idx * 2+1);
	seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}


int query(int a, int b, int n){ // query the path from a to b (or b to a)
	int res = 0;
	for(; head[a] != head[b]; b = parent[head[b]]){
		if(depth[head[a]] > depth[head[b]]) swap(a, b);
		debug(a);
		debug(head[a]);
		debug(b);
		debug(head[b]);
		int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b], 1, n);
		res = max(res, cur_heavy_path_max);
	}
	if(depth[a] > depth[b]){
		swap(a, b);
	}
	int last_heavy_path_max = segment_tree_query(pos[a], pos[b], 1, n);
	res = max(res, last_heavy_path_max);
	return res;
}

int LCA(int a, int b){
	for(int i = 20-1; i >= 0; i--){
		if(par[i][b] != 0 && isAncestor(par[i][b], a) == false){
			b = par[i][b];
		}
	}
	return par[0][b];
}

int main(){
//	yccc;		
	int n, q;
	cin >> n >> q;

	for(int u = 1; u <= n; u++){
		cin >> val[u];
	}
	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
	}

	dfs(1);
	decompose(1, 1);

	for(int u = 1; u <= n; u++){
		seq[pos[u]] = val[u];
	}

	segment_tree_build(1, n);

	for(int u = 1; u <= n; u++){
		par[0][u] = parent[u];
	}
	for(int i = 1; i < 20; i++){
		for(int u = 1; u <= n; u++){
			par[i][u] = par[i-1][par[i-1][u]];
		}
	}

	/*
	for(int u = 1; u <= n; u++){
		cout << u << ": " << D[u] << ", " << L[u] << endl;
		cout << parent[u];
		for(int i = 1; i < 3; i++){
			cout << " " << pa[u][i] << " ";
		}
		cout << endl;
	}
	(*/

	while(q--){
		int op;
		cin >> op;
		if(op == 1){
			int s, x;
			cin >> s >> x;
			segment_tree_modify(pos[s], x, 1, n);
		}
		else{
			int a, b;
			cin >> a >> b;
			int v = LCA(a, b);
			debug(v);
			cout << max(query(v, a, n), query(v, b, n)) << " ";
		}
	}

	return 0;
}

