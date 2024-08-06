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

ll G[21][21];
const ll MOD = 1000000000 + 7;

ll dp[(1 << 20)][21];
ll nid[(1 << 20)];
inline int lowbit(int x){
	return (x & (~(x-1)));	
}

int main() {
	int n, m;
	cin >> n >> m;
	for(int u = 1; u <= n; u++){
		nid[(1 << (u-1))] = u;
	}
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		G[u][v]++;
	}

	dp[1][1] = 1;

	for(int V = 2; V < (1 << n); V++){
		int cV = V;
		while(cV){
			int x = lowbit(cV);
			int v = nid[x];
			cV -= x;
			int subV = V - x;
			if(subV <= 0) continue;
			int uV = subV;
			while(uV){
				int y = lowbit(uV);
				int u = nid[y];
				uV -= y;
				if(G[u][v] > 0){
					dp[V][v] += dp[subV][u] * G[u][v];
					dp[V][v] %= MOD;
				}
			}
		}
	}
	/*
	for(int V = 1; V < (1 << n); V++){
		cout << V << "\n";
		for(int u = 1; u <= n; u++){
			cout << u << ": ";
			cout << dp[V][u] << ", ";
		}
		cout << endl;
	}*/
	cout << dp[(1<<n)-1][n] << endl;
	return 0;
}
