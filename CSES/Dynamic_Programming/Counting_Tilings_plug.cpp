// tips: what you put in this round, your transition is from last round and pull out what you just put.
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

const int MOD = 1000000007;
int dp[1001][11][(1 << 11)] = {0};
// transpose
// definition, all grid from (1,1), (1, 2) ...(2, 1), (2,2), ...(i, j-1) is filled.
// the mask 
/*       j...   m
         --------
01.(j-1)|
--------
*/
int main(){
	int n, m;
	cin >> n >> m;
	swap(n, m);
	
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			for(int mask = 0; mask < (1 << (m+1)); mask++){
				dp[i][j][mask] = 0;
			}
		}
	}
	dp[0][m][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int mask = 0; mask < (1 << (m+1)); mask++){
			if(!(mask & 1))
				dp[i][0][mask] += dp[i-1][m][mask >> 1];
		}
		for(int j = 1; j <= m; j++){
			for(int mask = 0; mask < (1 << (m+1)); mask++){
				int jbit = mask & (1 << j), j_1bit = mask & (1 << (j-1));
				if(jbit && !j_1bit && j < m){ // horizontal 
					dp[i][j][mask] += dp[i][j-1][mask ^ (1 << j)];
				}
				else if(!jbit && j_1bit){ // vertical
					dp[i][j][mask] += dp[i][j-1][mask ^ (1 << (j-1))];
				}
				else if(!jbit && !j_1bit){
					// cover by previous horizontal
					dp[i][j][mask] += dp[i][j-1][mask ^ (1 << j)];
					// cover by previous vertical
					dp[i][j][mask] += dp[i][j-1][mask ^ (1 << (j-1))];
				}
				dp[i][j][mask] %= MOD;
			}
		}
	}
	cout << dp[n][m][0] % MOD << endl;
	return 0;
}

