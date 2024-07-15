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
using edge = pair<ll, int>;
const ll MOD = 1000000007;

vec<edge> G[100001];
ll ways[100001];


int main() {
	yccc;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
		ll w;
		cin >> u >> v >> w;
		G[u].eb(w, v);
	}
	vec<ll> dis(n+1, LLONG_MAX);
	vec<ll> minlen(n+1, LLONG_MAX);
	vec<ll> maxlen(n+1, 0);
	
	dis[1] = 0;
	ways[1] = 1;
	minlen[1] = maxlen[1] = 0;

	priority_queue<edge, vec<edge>, greater<edge>> pq;
	pq.emplace(dis[1], 1);
	while(pq.size()){
		int u; ll d;
		tie(d, u) = pq.top();
		pq.pop();
		if(d > dis[u]) continue;
		for(edge &e: G[u]){
			int v; ll w;
			tie(w, v) = e;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				pq.emplace(dis[v], v);
				ways[v] = ways[u];
				minlen[v] = minlen[u] + 1;
				maxlen[v] = maxlen[u] + 1;
			}
			else if(dis[v] == dis[u] + w){
				ways[v] = (ways[v] + ways[u]) % MOD;
				minlen[v] = min(minlen[v], minlen[u] + 1);
				maxlen[v] = max(maxlen[v], maxlen[u] + 1);
			}
		}
	}

	cout << dis[n] << " " << ways[n] << " " << minlen[n] << " " << maxlen[n] << endl;	

	return 0;
}
