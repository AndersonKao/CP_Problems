#include <bits/stdc++.h>
#include <sys/resource.h>

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
bool been_centroid[maxn+1];
int sz[maxn+1];
vector<int> G[maxn+1];
int cnt[maxn+1];
int total_cnt[maxn+1];
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
		if(been_centroid[v] || v== pa) continue;
        int centroid = tree_centroid(v, u, tree_size, d+1);
		if(centroid != -1){
			return centroid;
		}
        maxsub = max(maxsub, sz[v]);
        sz[u] += sz[v];
    }
    maxsub = max(maxsub, tree_size-sz[u]);

    if (maxsub <= tree_size/2)
		return u;
	return -1;
}

int dfs_count(int u, int pa, int d = 1){ // return max depth
	cnt[d]++;
	sz[u] = 1;
	int maxd = d;
	for(int v: G[u]){
		if(been_centroid[v] || v == pa) continue;
		maxd = max(maxd, dfs_count(v, u, d+1));
		sz[u] += sz[v];
	}
	return maxd;
}

void solve(int subtree_u, int subtree_sz){ // subtree: maximum subtree containing u and all nodes haven't been centroid before.
	if(subtree_sz == 1 || subtree_sz < k1) return;

	int centroid = tree_centroid(subtree_u, -1, subtree_sz);
	been_centroid[centroid] = true;

	int initial_sum = 0;
	int mx_depth = 0;
	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		int subtree_depth = dfs_count(child, -1);
		int partial_sum = initial_sum;
		for(int d = 1; d <= subtree_depth; d++){
			ans += cnt[d] * partial_sum;		
			if(k1 - d - 1 > 0){
				partial_sum += total_cnt[k1-d-1];
			}
			if(k2 - d > 0)
				partial_sum -= total_cnt[k2-d];	
		}
		for(int d = 1; d <= subtree_depth; d++){
			total_cnt[d] += cnt[d];
			if(k1 - 1 <= d && d <= k2 - 1){
				initial_sum += cnt[d];
			}
		}
//		memset(cnt, 0, sizeof(int) * (subtree_depth + 1));
		fill(cnt, cnt + (subtree_depth + 1), 0);
		mx_depth = max(subtree_depth, mx_depth);
	}

	ans += (initial_sum - total_cnt[k1-1] + total_cnt[k2]);

//	memset(total_cnt, 0, sizeof(int) * (k2 + 1));
	fill(total_cnt, total_cnt + (mx_depth + 1), 0);

	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		solve(child, sz[child]);
	}
}

int main(){
	struct rlimit rl;
	getrlimit(RLIMIT_STACK, &rl);
	rl.rlim_cur *= 10;
	setrlimit(RLIMIT_STACK, &rl);
	yccc;
	cin >> n >> k1 >> k2;
	for(int i = 0; i < n-1; i++){
		int a, b;
		cin >> a >> b;
		G[a].eb(b);
		G[b].eb(a);
	}
	solve(1, n);
	cout << ans << endl;
	return 0;
}
