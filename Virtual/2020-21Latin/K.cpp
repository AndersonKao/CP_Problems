#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define LC(x) (2*x+1)
#define RC(x) (2*x+2)
const ll MOD = 1000000000 + 7;

vector<vector<ll>> table;
vector<ll> step;
using iter = vector<ll>::iterator;

int K, L, N;
int dp[10001][750] = {0};
int main(){
	cin >> K >> L;
	table.resize(K, vector<ll>(K));
	REP(i, K){
		REP(j, K){
			cin >> table[i][j];
		}
	}
	cin >> N;
	step.resize(N-1);
	for(ll &v: step)
		cin >> v;
	for(int k = 0; k < K; k++)
		dp[N-1][k] = k + 1;
	for(int i = N-2; i >= 0; i--){
		ll up = step[i] + L, down = step[i] - L;
		for(int j = 0; j < K; j++){
			int lb = lower_bound(al(table[j]), down) - table[j].begin();
			int ub = upper_bound(al(table[j]), up) - table[j].begin();
//			debug(N);
//			cout << i << ", " << j << ": " << lb - table[j].begin() << ", " << ub - table[j].begin() << endl;
			dp[i][j] = j > 0 ? dp[i][j-1] : 0;
			if(lb < ub){
				ll vl = lb > 0 ? dp[i+1][lb - 1] : 0;
				ll vr = ub > 0 ? dp[i+1][ub - 1] : 0;
				dp[i][j] = (dp[i][j] + vr - vl + MOD) % MOD; 
			}
		}
	}
	/*
	for(int i = 0; i < N; i++){
		for(int j = 0; j < K; j++){
			cout << setw(3) << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/
	cout << dp[0][K-1] << endl;

	return 0;
}
