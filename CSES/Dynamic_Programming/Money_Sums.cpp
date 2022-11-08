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
const int maxn = 100;
const int maxv = 1000;
int val[maxn];
bool dp[maxn][maxv * maxn+1];
int main(){
	yccc;		
	int n;
	cin >> n;
	REP(i, n)
		cin >> val[i];
	dp[0][0] = true;
	dp[0][val[0]] = true;
	for(int i = 1; i < n; i++){
		for(int v = 0; v < val[i]; v++){
			dp[i][v] = dp[i-1][v];
		}
		for(int v = val[i]; v <= n * maxv; v++){
			dp[i][v] = dp[i-1][v - val[i]] || dp[i-1][v];
		}
	}
	vec<int> ans;
	for(int v = 1; v <= n * maxv; v++){
		if(dp[n-1][v])
			ans.eb(v);
	}	
	cout << ans.size() << endl;
	for(int v: ans){
		cout << v << " ";
	}

	return 0;
}

