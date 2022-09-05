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


ll dp[2000][2000];
const ll inf = 300000000000000;
int main(){
	int n, m;
	cin >> n >> m;
	vector<ll> V(n, 0);
	for(ll&v: V)
		cin >> v;
	REP(i, n){
		REP(j, n){
			dp[i][j] = -inf;
		}
	}
	dp[0][0] = V[0];
	for(int i = 0; i < n; i++){
		if(i > 0)
			dp[i][0] = max(dp[i-1][0], V[i]);
		for(int j = 1; j < min(m, i+1); j++){
			if(i > 0)
				dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + V[i] * (j+1));
		}
	}
	cout << dp[n-1][m-1] << endl;
	return 0;
}

