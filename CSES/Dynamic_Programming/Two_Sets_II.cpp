#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;
vector<ll> dp;
int main(){
	int n;
	cin >> n;
	ll limit = (1LL + n) * n / 2;
	if(limit & 1){
		cout << 0 << endl;
		return 0;
	}
	limit /= 2;
//	cout << limit << endl;
	dp.resize(limit + 1, 0);
	dp[0] = 1;
	for(int i = 2; i <= n; i++){
		for(int j = limit; j >= i; j--){
			dp[j] = (dp[j] + dp[j-i]) % MOD;
		}
	}	
	cout << dp[limit] << endl;

	return 0;
}
