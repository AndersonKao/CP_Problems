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

const ll MOD = 1000000007LL;
ll dp[10][1000][(1 << 10)] = {0};
int main(){
	int n, m;
	cin >> n >> m;
	dp[0][0][((1 << n) - 1) - 1] = 1;
	//cout << 0 << ", " << 0 << ", " << bitset<4>((1 << n) - 1 - 1) << ": " << dp[0][0][(1<<n) - 1 -1] << endl;
	for(int j = 0; j < m; j++){
		for(int i = 0; i < n; i++){
			if(i == 0 && j == 0)
				continue;
			int pi = i-1, pj = j;
			if(pi < 0){
				pi = n-1;
				pj = j-1;
			}
			for(int mask = 0; mask < (1 << n); mask++){
				dp[i][j][mask] = 0;
				if(mask & (1 << i)){
					if(j > 0){
						dp[i][j][mask] += dp[pi][pj][mask ^ (1 << i)];// horizontal tile
//						cout << "hori\n";
					}
					if(i > 0 && (mask & (1 << i)) && (mask & (1 << (i-1)))){ //vertical tile
						dp[i][j][mask] += dp[pi][pj][mask ^ (1 << (i-1))];
//						cout << "verti\n";
					}
				}
				else{
					dp[i][j][mask] = dp[pi][pj][mask ^ (1 << i)]; // no tile
//					cout << "none\n";
				}
				while(dp[i][j][mask] >= MOD)
					dp[i][j][mask] -= MOD;
//				cout << i << ", " << j << ", " << bitset<4>(mask) << ": " << dp[i][j][mask] << endl;
			}
		}
	}
	cout << dp[n-1][m-1][(1 << n) - 1] << endl;
	return 0;
}

