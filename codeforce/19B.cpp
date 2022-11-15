
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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 2000;
int mt[maxn];
ll c[maxn];
ll dp[maxn][3*maxn];
const ll inf = 0x3f3f3f3f3f3f3f3f;
int main(){
	yccc;		
	int n;
	cin >> n;
	ll sum = 0;
	for(int i = 0; i < n; i++){
		cin >> mt[i] >> c[i];
		sum += c[i];
		mt[i] += 1;
		fill(dp[i], dp[i]+3 * maxn, inf);
	}
	dp[0][0] = 0;
	dp[0][mt[0]] = c[0];	
	for(int i = 1; i < n; i++){
		for(int t = 0; t < 3*maxn; t++){
			if(t >= mt[i])
				dp[i][t] = min(dp[i-1][t], dp[i-1][t - mt[i]] + c[i]);
			else
				dp[i][t] = dp[i-1][t];
		}
	}
	ll ans = inf;
	/*
	for(int i = 0; i < n; i++){
		cout << i << ": ";
		for(int t = 0; t <= 30; t++){
			cout << t << "=" << (dp[i][t] == inf ? -1 : dp[i][t]) << " ";
		}
		cout << endl;
	}*/
	for(int t = n; t < 3*maxn; t++){
		ans = min(ans, dp[n-1][t]);
	}
	cout << ans << endl;

	return 0;
}

