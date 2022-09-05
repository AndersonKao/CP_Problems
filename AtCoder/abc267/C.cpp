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


int main(){
	int n, m;
	cin >> n >> m;
	vector<ll> V(n, 0);
	for(ll&v: V)
		cin >> v;
	reverse(V.begin(), V.end());
	vector<ll> pre(n, 0);
	pre[0] = V[0];
	for(int i = 1; i < n; i++){
		pre[i] = pre[i-1] + V[i];
	}
	ll ans = 0;
	for(int i = 0; i < m; i++){
		ans += pre[i];
	}
	ll cur = ans;
	for(int i = m; i < n; i++){
		ll res = cur - V[i-m] * m + pre[i] - pre[i-m];
		ans = max(ans, res);
		cur = res;
		
	}
	cout << ans  << endl;
	return 0;
}

