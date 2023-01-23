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
const int maxn = 400;
ll dp[maxn+1][maxn+1];
ll seq[maxn+1];
const ll inf = 1e15;
int main(){
	yccc;		
	int n; cin >> n;
	REP1(i, n){
		cin >> seq[i];
		seq[i] += seq[i-1];
	}
	for(int len = 1; len < n; len++){
		for(int i = 1; i + len <= n; i++){
			dp[i][i + len] = inf;
			for(int j = 0; j < len; j++){
				dp[i][i + len] = min(dp[i][i+len], dp[i][i + j] + dp[i + j + 1][i + len] + (seq[i + len] - seq[i-1]));
			}
		}	
	}
	cout << dp[1][n] << endl;
	return 0;
}

