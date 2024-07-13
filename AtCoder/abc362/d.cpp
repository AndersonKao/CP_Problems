#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

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
vec<pair<int, ll>> G[400005];
using edge = pair<ll, int>;

int main() {
	yccc;
	int n, m;
	cin >> n >> m;

	for(int u = 1; u <= n; u++){
		ll w;
		cin >> w;
		G[u].eb(n+u, w);
	}

	for(int i = 0; i < m; i++){
		int u, v;
		ll w;
		cin >> u >> v >> w;
		G[n+u].eb(v, w);
		G[n+v].eb(u, w);
	}
	vec<ll> dis(2*(n+1), LLONG_MAX);

	int st = 1;
	priority_queue<edge, vec<edge>, greater<edge>> pq;
	pq.emplace(0, st);
	dis[st] = 0;
	while(pq.size()){
		int u; ll d;
		tie(d, u) = pq.top();
		//cout << "now: " << u << ", " << d << endl;
		pq.pop();
		if(d != dis[u]) continue;
		for(pair<int, ll> e: G[u]){
			int v; ll w;
			tie(v, w) = e;
			//cout << "relax " << v << " with " << w << endl;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				pq.emplace(dis[v], v);
			}
		}
	}
	/*
	for(int u = 1; u <= n; u++){
		cout << dis[u] << ", " << dis[2*u] << endl;
	}
	*/
	for(int i = 2; i <= n; i++){
		cout << dis[n+i] << (i == n ? '\n' : ' ');
	}


	return 0;
}
