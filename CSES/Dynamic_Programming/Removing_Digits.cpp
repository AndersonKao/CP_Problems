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
const int maxn = 1000000;
int dp[maxn+1];
const int inf = maxn*2;
int main(){
	yccc;		
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		dp[i] = inf;
		int res = i;
		while(res){
			dp[i] = min(dp[i], 1 + dp[i - (res % 10)]);
			res /= 10;
		}
	}
	cout << dp[n];
	return 0;
}

