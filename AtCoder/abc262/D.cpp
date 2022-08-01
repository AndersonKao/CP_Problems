#include <bits/stdc++.h>
using namespace std;
vector<int> V;
using ll = long long;
const ll MOD = 998244353;
int main(){
	int N;
	cin >> N;
	V.resize(N+1);
	for(int i = 1; i <= N; i++)
		cin >> V[i];
	ll ans = 0;
	for(int i = 1;i <= N; i++){
		vector<vector<vector<ll>>> dp(N+1, vector<vector<ll>>(N+1, vector<ll>(N+1, 0)));
	
		dp[0][0][0] = 1;
	
		for(int j = 0; j < N; j++){
			for(int k = 0; k <= i; k++){
				for(int t = 0; t < i; t++){
					dp[j+1][k][t] += dp[j][k][t];
					dp[j+1][k][t] %= MOD;
					int y = (t + V[j+1]) % i;
					if(k != i){
						dp[j+1][k+1][y] += dp[j][k][t];
						dp[j+1][k+1][y] %= MOD;
					}
				}
			}
		}
		ans += dp[N][i][0];
		ans %= MOD;
	}
	cout << ans << endl;
	
	return 0;
}
