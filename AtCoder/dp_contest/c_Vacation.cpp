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
int val[100000][3];
int dp[100000][3];
int main(){
	yccc;		
	int n;
	cin >> n;
	REP(i, n){
		REP(j, 3){
			cin >> val[i][j];
		}
	}
	REP(j, 3){
		dp[0][j] = val[0][j];
	}

	for(int i = 1; i < n; i++){
		REP(j, 3){
			REP(k, 3){
				if(k == j) continue;
				dp[i][j] = max(dp[i-1][k] + val[i][j], dp[i][j]);
			}
		}
	}
	int ans = 0;
	REP(j, 3){
		ans = max(ans, dp[n-1][j]);
	}
	cout << ans << endl;
	

	return 0;
}

