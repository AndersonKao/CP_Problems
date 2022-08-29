#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9+7;
ll dp[2][(1 << 10)] = {0};
int main(){
	int n, m;
	cin >> n >> m;
	dp[0][(1 << n) - 1] = 1;
	for(int j = 0; j < m; j++){
		for(int i = 0; i < n; i++){
			for(int mask = 0; mask < (1 << n); mask++){
				if(0 == (mask & (1 << i))){
					dp[1][mask] = dp[0][mask ^ (1 << i)]; // no tile
						cout << "none\n";
				}
				else{
					dp[1][mask] = 0;
					if(j > 0){
						dp[1][mask] += dp[0][mask ^ (1 << i)];// horizontal tile
						cout << "hori\n";
					}
					if(i > 0 && (mask & (1 << i)) && (mask & (1 << (i-1)))){ //vertical tile
						dp[1][mask] += dp[0][mask ^ (1 << (i-1))];
						cout << "verti\n";
					}

				}
				while(dp[1][mask] >= MOD){
					dp[1][mask] -= MOD;
				}
				cout << i << ", " << j << ", " << bitset<4>(mask) << ": " << dp[1][mask] << endl;
			}
			for(int mask = 0; mask < (1 << n); mask++){
				dp[0][mask] = dp[1][mask];
			}
		}
	}
	cout << dp[0][(1 << n) - 1] << endl;
	return 0;
}

