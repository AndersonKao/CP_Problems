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
const int maxn = 200001;
vec<int> pq[maxn];

int dsu[maxn];
int sz[maxn];

int query(int u){
	if(dsu[u] != u){
		return dsu[u] = query(dsu[u]);
	}
	return u;
}

void merge(int u, int v){
	u = query(u);
	//debug(u);
	v = query(v);
	//debug(v);
	if(u == v) return;
	for(int x: pq[v]){
		pq[u].eb(x);
	}
	dsu[v] = u;

	sort(al(pq[u]), greater<int>());
	pq[u].resize(unique(al(pq[u])) - pq[u].begin());
	if(pq[u].size() > 10)
		pq[u].resize(10);
}

int main(){
	//yccc;		

	int n, q;
	cin >> n >> q;
	for(int u = 1; u <= n; u++){
		pq[u].eb(u);
		dsu[u] = u;
	}
	while(q--){
		int op;
		cin >> op;
		
		if(op == 1){
			int u, v;
			cin >> u >> v;
			merge(u, v);
		}
		else{
			int v, k;
			cin >> v >> k;
			v = query(v);
			if(k <= pq[v].size())
				cout << pq[v][k-1] << endl;
			else
				cout << -1 << endl;
		}
	}
	return 0;
}

