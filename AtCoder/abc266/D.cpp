#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const ll INF = 1000000000000000LL;
struct data{
	int t, x, a;
};

int main(){
	int N;
	cin >> N;
	vector<vector<ll>> sn(100001, vector<ll>(5, 0));
	REP(i, N){
		int t, x, a;
		cin >> t >> x >> a;
		sn[t][x] += a;
	}
	vector<vector<ll>> dp(100001, vector<ll>(5, -INF));
	dp[0][0] = 0;
	for(int t = 1; t <= 100000; t++){
		for(int i = 0; i < 5; i++){
			if(i - 1 >= 0 && dp[t-1][i-1] != -INF)
				dp[t][i] = max(dp[t-1][i-1] + sn[t][i], dp[t][i]); 
			if(dp[t-1][i] != -INF)
				dp[t][i] = max(dp[t-1][i] + sn[t][i], dp[t][i]); 
			if(i+1<5 && dp[t-1][i+1] != -INF)
				dp[t][i] = max(dp[t-1][i+1] + sn[t][i], dp[t][i]); 
		}
	}
	ll ans = 0;
	for(int i = 0; i < 5; i++)
		ans = max(ans, dp[100000][i]);
	cout << ans << endl;
	return 0;
}

