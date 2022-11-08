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
const int maxn = 1000;
char mat[maxn+1][maxn+1];
int dp[maxn+1][maxn+1];
const int mod = 1e9+7;
int main(){
	yccc;		
	int n;
	cin >> n;
	REP1(i, n){
		REP1(j, n){
			cin >> mat[i][j];
		}
	}
	dp[0][1] = 1;	
	REP1(i, n){
		REP1(j, n){
			if(mat[i][j] == '.')
				dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
		}
	}
	cout << dp[n][n];
	return 0;
}

