
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

int x[100000];
ll dp[100000][101];
ll MOD = 1000000007;

int main() {
	yccc;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> x[i];
	}

	if(x[0] == 0){
		for(int j = 1; j <= m; j++){
			dp[0][j] = 1;
		}
	}
	else{
		dp[0][x[0]] = 1;
	}
	for(int i = 1; i < n; i++){
		if(x[i] != 0){
			for(int k = -1; k <= 1; k++){
				if(x[i] + k >= 1 && x[i] + k <= m){
					dp[i][x[i]] += dp[i-1][x[i] + k];
					dp[i][x[i]] %= MOD;
				}
			}
		}
		else if(x[i-1] == 0){
			for(int j = 1; j <= m; j++){
				for(int k = -1; k <= 1; k++){
					if(j + k >= 1 && j + k <= m){
						dp[i][j] += dp[i-1][j + k];
						dp[i][j] %= MOD;
					}
				}
			}
		}
		else{
			for(int k = -1; k <= 1; k++){
				if(x[i-1] + k >= 1 && x[i-1] + k <= m){
					dp[i][x[i-1] + k] = dp[i-1][x[i-1]];
					dp[i][x[i-1]] %= MOD;
				}
			}
		}
	}
	ll ans = 0;
	for(int i = 1; i <= m; i++){
		ans = (ans + dp[n-1][i]) % MOD;
	}
	cout << ans << endl;

	return 0;
}
