#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int dj[100001]; // disjoint set
int sz[100001]; // disjoint set

int cnt;
int maxsize = 1;

int Find(int u){
	if(dj[u] == u){
		return u;
	}
	return dj[u] = Find(dj[u]);
}

void Union(int u, int v){
	int pu = Find(u);
	int pv = Find(v);
	if(pu == pv){
		return;
	}
	sz[pu] += sz[pv];
	dj[pv] = dj[pu];
	maxsize = max(maxsize, sz[pu]);
	cnt--;
}

int main() {
	yccc;
	int n, m;
	cin >> n >> m;
	cnt = n;
	for(int i = 1; i <= n; i++){
		sz[i] = 1;
		dj[i] = i;
	}

	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		Union(u, v);
		cout << cnt << " " << maxsize << endl;
	}

	return 0;
}
