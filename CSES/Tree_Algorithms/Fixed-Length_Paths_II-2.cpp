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
bool been_centroid[maxn+5];
int depth[maxn+5], sz[maxn+5];
vector<vector<int>> G;
int cnt[maxn + 5];
ll ans = 0;
int n, k1, k2;
 
void print_tree(int u, int pa = -1){
	cout << u << " ";
 
	for(int v: G[u]){
		if(v == pa) continue;
		if(been_centroid[v]){
			continue;
		}	
		print_tree(v, u);
	}
}
 
int tree_centroid(int u, int pa, int tree_size, int d =1)
{
	sz[u] = 1;
    int maxsub = 0; // max subtree size of u
	for(int v: G[u]){
		if(been_centroid[v]) continue;
        if (v==pa){
			continue;
		}
        int c = tree_centroid(v, u, tree_size, d+1);
		if(c != -1){
			return c;
		}
        maxsub = max(maxsub, sz[v]);
        sz[u] += sz[v];
    }
    maxsub = max(maxsub, tree_size-sz[u]);
 
    if (maxsub <= tree_size/2)
    {
		return u;
    }
	return -1;
}
 
void dfs_count(int u, int pa, int partial_sum, int d = 1){
	ans += partial_sum;	
	if(k1-d-1 >= 0){
		partial_sum += cnt[k1-d-1];
	}
	if(k2-d >= 0){
		partial_sum -= cnt[k2-d];
	}
	for(auto it = G[u].begin(); it != G[u].end(); it++){
		if(been_centroid[*it]) continue;
 
		int v = *it;
		if(v == pa) continue;
		
		dfs_count(v, u, partial_sum, d+1);
	}
}
 
void dfs_update(int u, int pa, int &initial_sum, int &maxd, int d = 1){ // return max depth
	cnt[d]++;
	if(d >= k1-1 && d <= k2-1){
		initial_sum += 1;
	}
	sz[u] = 1;
	maxd = max(maxd, d);
	for(int v: G[u]){
		if(v == pa) continue;
		if(been_centroid[v]){
			continue;
		}	
		dfs_update(v, u, initial_sum, maxd, d+1);
		sz[u] += sz[v];
	}
}
 
void solve(int subtree_u, int subtree_sz){ // subtree: maximum subtree containing u and all nodes haven't been centroid before.
	if(subtree_sz == 1 || subtree_sz < k1) return;
 
	int centroid = tree_centroid(subtree_u, -1, subtree_sz);
	been_centroid[centroid] = true;
 
	int initial_sum = 0;
	int maxd = 0;
	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		dfs_count(child, -1, initial_sum);
		dfs_update(child, -1, initial_sum, maxd);
	}
 
	ans += (initial_sum - cnt[k1-1] + cnt[k2]); 
	memset(cnt, 0, sizeof(int) * (maxd + 1));
	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		solve(child, sz[child]);
	}
}
 
int main(){
	yccc;
	cin >> n >> k1 >> k2;
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

