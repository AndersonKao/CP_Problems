#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

using pli = pair<ll, int>;
const ll inf = 300000000000000;
ll val[200000];
ll sum[200000];
vector<vector<int>> G;
int main(){
	int n, m;
	cin >> n >> m;
	G.resize(n);
	for(int i = 0; i < n; i++){
		cin >> val[i];
	}
	REP(i, m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
		G[v].eb(u);
	}
	priority_queue<pli, vector<pli>, greater<pli>> mQ;
	for(int u = 0; u < n; u++){
		sum[u] = 0;
		for(int v: G[u]){
			sum[u] += val[v];
		}
		mQ.emplace(sum[u], u);
	}
	ll ans = 0;
	vector<bool> exist(n, true);
	while(mQ.size()){
		ll w;
		int u;
		tie(w, u) = mQ.top();
		mQ.pop();
		if(exist[u] == false || w != sum[u])
			continue;
		exist[u] = false;
		ans = max(w, ans);
		for(int v: G[u]){
			if(exist[v] == false){
				continue;
			}
			sum[v] -= val[u];
			mQ.emplace(sum[v], v);
		}
	}
	cout << ans << endl;

	return 0;
}

