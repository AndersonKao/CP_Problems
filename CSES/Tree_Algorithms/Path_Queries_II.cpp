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
#define yccc cin.tie(0); ios_base::sync_with_stdio(false); cout.tie(0);
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
int heavy[maxn]; // the child on the other end of heavy edge
int depth[maxn];
int head[maxn];
int pos[maxn]; // position on segment tree;
int cur_pos = 0;
int par[maxn];
int N = 1;

int segment_tree_query(int l, int r)
{
	int idx_l = l + N, idx_r = r + N;
	int res = 0;
	while(idx_l <= idx_r){
		if(idx_l & 1){
			res = max(res, seg[idx_l]);
			idx_l++;
		}
		if((idx_r & 1) == 0){
			res = max(res, seg[idx_r]);	
			idx_r--;
		}
		idx_l >>= 1; idx_r >>= 1;
	}
	return res;
}

void segment_tree_modify(int pos, int x){
	int idx = pos + N; // place at pos + (100...00) (ceil(logN) 0-bits)
	seg[idx] = x; idx >>=1;
	while(idx > 0){
		seg[idx] = max(seg[2*idx], seg[2*idx+1]);
		idx>>=1;
	}
}

int dfs(int u, int pa = 0){
	par[u] = pa;
	int size = 1;
	int max_c_size = 0;
	heavy[u] = 0;
	for(int v: G[u]){
		if(v == pa) continue;
		depth[v] = depth[u] + 1;
		int c_size = dfs(v, u);
		if(c_size > max_c_size){
			max_c_size = c_size;
			heavy[u] = v;
		}
		size += c_size;
	}
	return size;
}

void decompose(int u, int h){
	head[u] = h, pos[u] = cur_pos++;
	segment_tree_modify(pos[u], val[u]);
	if(heavy[u] != 0){
		decompose(heavy[u], h);
	}
	for(int v: G[u]){
		if(v != par[u] && v != heavy[u]){
			decompose(v, v);
		}
	}
}

int query(int a, int b){ // query the path from a to b (or b to a)
	int res = 0;
	while(head[a] != head[b]){
		if(depth[head[a]] > depth[head[b]]) swap(a, b);
		int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
		res = max(res, cur_heavy_path_max);
		b = par[head[b]];
	}
	if(depth[a] > depth[b]){
		swap(a, b);
	}
	int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
	res = max(res, last_heavy_path_max);
	return res;
}

int main(){
	yccc;		
	int n, q;
	cin >> n >> q;
	while(N < n){
		N <<= 1;
	}

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

	while(q--){
		int op;
		cin >> op;
		if(op == 1){
			int s, x;
			cin >> s >> x;
			segment_tree_modify(pos[s], x);
		}
		else{
			int a, b;
			cin >> a >> b;
			cout << query(a, b) << " ";
		}
	}

	return 0;
}

