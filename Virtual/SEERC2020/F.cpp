#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int MOD = 1000000007;
int main(){
	int n;
	cin >> n;
	vec<int> V(n+2);	
	for(int i = 1; i <= n; i++)
		cin >> V[i];
	vec<int> Li(n+1, 0), Ri(n+1, n+1);

	stack<int> ms;

	for(int i = 1; i <= n; i++){
		while(ms.size() && V[ms.top()] > V[i])
			ms.pop();
		if(ms.size())
			Li[i] = ms.top();
		ms.emplace(i);
	}
	while(ms.size()) ms.pop();

	for(int i = n; i > 0; i--){
		while(ms.size() && V[ms.top()] > V[i])
			ms.pop();
		if(ms.size())
			Ri[i] = ms.top();
		ms.emplace(i);
	}

	vec<vec<int>> dp(n+1, vec<int>(n+1, 0));
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++){
		vec<int> prefix(n+1, 0);
		prefix[0] = dp[i-1][0];
		for(int j = 1; j <= n; j++){
			prefix[j] = prefix[j-1] + dp[i-1][j];	
			prefix[j] %= MOD;
		}
		for(int j = 1; j <= n; j++){
			if(Li[j] < i && i < Ri[j])
				dp[i][j] = prefix[j];
			else
				dp[i][j] = 0;
		}
	}
	ll ans = 0;
	for(int j = 1; j <= n; j++){
		if(Li[j] < n && n < Ri[j]){
			ans += dp[n][j];
			ans %= MOD;
		}
	}
	cout << ans << endl;


	return 0;
}

