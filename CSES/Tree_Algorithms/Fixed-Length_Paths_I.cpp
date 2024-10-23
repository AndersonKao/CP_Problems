#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
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
const int maxn = 200000;
bool been_centroid[maxn];
int depth[maxn], sz[maxn];
vector<vector<int>> G;
int cnt[maxn + 1];
ll ans = 0;
int n, k;

int tree_centroid(int u, int pa, int tree_size)
{
	sz[u] = 1;
    int maxsub = 0; // max subtree size of u

    for(int v:G[u])
    {
        if (v==pa)continue;
        if (been_centroid[v])continue;
        int c = tree_centroid(v, u, tree_size);
		if(c != -1){
			return c;
		}
        maxsub = max(maxsub, sz[v]);
        sz[u] += sz[v];
    }
    maxsub = max(maxsub, tree_size-sz[u]);

    if (maxsub <= G.size()/2)
    {
		return u;
    }
    return -1;
}

void dfs_depth_size(int u, int pa){
	if(pa == -1){
		depth[u] = 0;
	}
	else{
		depth[u] = depth[pa] + 1;
	}
	sz[u] = 1;

	for(int v: G[u]){
		if(v == pa) continue;
		if(been_centroid[v]) continue;
		dfs_depth_size(v, u);
		sz[u] += sz[v];
	}
}

void dfs_count(int u, int pa, bool addin){
	if(addin){
		cnt[depth[u]]++;
	}
	else if(k > depth[u]){
		ans += cnt[k-depth[u]];
	}
	for(int v: G[u]){
		if(v == pa) continue;
		if(been_centroid[v]) continue;
		dfs_count(v, u, addin);
	}
}

void solve(int subtree_u, int subtree_sz){ // subtree: maximum subtree containing u and all nodes haven't been centroid before.
	if(subtree_sz == 1) return;
	int K = min(subtree_sz, k);
	int centroid = tree_centroid(subtree_u, -1, subtree_sz);
	been_centroid[centroid] = true;
	dfs_depth_size(centroid, -1);
	memset(cnt, 0, sizeof(int) * (K + 1));

	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		dfs_count(child, -1, false);
		dfs_count(child, -1, true);
	}

	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		solve(child, sz[child]);
	}

}

int main(){
	yccc;
	cin >> n >> k;
	G.resize(n);
	for(int i = 0; i < n-1; i++){
		int a, b;
		cin >> a >> b;
		a--,b--;
		G[a].eb(b);
		G[b].eb(a);
	}
	solve(0, n);
	cout << ans << endl;
	return 0;
}
