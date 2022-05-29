#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
const ll MOD = 998244353;
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ": " << x << endl;


int main(){
	cin.tie(0), ios_base::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	vec<ll>dp(M+1, 1);
	dp[0] = 0;
	
	for(int i = 1; i < N; i++){
		vec<ll> pre(M + 1, 0);
		for(int j = 1;j <= M; j++){
			pre[j] = (pre[j-1] + dp[j]) % MOD;
		}
		vec<ll> dp2(M+1, 0);
		for(int j = 1; j <= M; j++){
			int nl = j - (K);
			int nr = j + (K);
			if(nl == nr){
				dp2[j] += pre[M];
			}else{
				if(nl >= 1){
					dp2[j] += pre[nl];
					dp2[j] %= MOD;
				}	
				if(nr <= M){
					dp2[j] += pre[M] - pre[nr-1];
				}
			}
			dp2[j] %= MOD;
		} 	
		dp = dp2;
	}
	ll ans = 0;	
	for(ll&x: dp)
		ans = (ans + x)%MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
