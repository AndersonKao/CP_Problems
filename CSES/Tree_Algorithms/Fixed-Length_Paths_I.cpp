#include <bits/stdc++.h>
#include <sys/time.h>
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
bool been_centroid[maxn+5];
int depth[maxn+5], sz[maxn+5];
vector<list<int>> G;
int cnt[maxn + 5];
ll ans = 0;
int n, k;

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
int gloc;

void tree_centroid(int u, int pa, int tree_size, int d =1)
{
//	debug(d);
//	debug(u);
	sz[u] = 1;
    int maxsub = 0; // max subtree size of u

	for(int v: G[u]){
		if(been_centroid[v]) continue;
        if (v==pa){
			continue;
		}
         tree_centroid(v, u, tree_size, d+1);
        maxsub = max(maxsub, sz[v]);
        sz[u] += sz[v];
    }
    maxsub = max(maxsub, tree_size-sz[u]);

    if (maxsub <= tree_size/2)
    {
		gloc = u;
	//	return u;
    }
//    return -1;
}

void dfs_count(int u, int pa, int d = 1){
	if(k > d){
		ans += cnt[k - d];
	}
	else{
		return;
	}


	for(auto it = G[u].begin(); it != G[u].end(); it++){
		if(been_centroid[*it]) continue;

		int v = *it;
		if(v == pa) continue;

		dfs_count(v, u, d+1);
	}
}

void dfs_update(int u, int pa, int d = 1){
	cnt[d]++;
	sz[u] = 1;
	for(int v: G[u]){
		if(v == pa) continue;
		if(been_centroid[v]){
			continue;
		}	
		dfs_update(v, u, d+1);
		sz[u] += sz[v];
	}
}

void solve(int subtree_u, int subtree_sz){ // subtree: maximum subtree containing u and all nodes haven't been centroid before.
	if(subtree_sz == 1 || subtree_sz < k) return;

//	debug(subtree_u);
//	debug(subtree_sz);
	tree_centroid(subtree_u, -1, subtree_sz);
	int centroid = gloc;
	been_centroid[centroid] = true;

	memset(cnt, 0, sizeof(int) * (k + 1));

	for(int child: G[centroid]){
		if(been_centroid[child]) continue;
		dfs_count(child, -1);
		dfs_update(child, -1);
	}

	ans += cnt[k];

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
