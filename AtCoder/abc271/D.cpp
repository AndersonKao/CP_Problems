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
int C[2][100] = {0};
int dp[101][10001] = {0};
int state[101][10001] = {0};
int main(){
	int n, s;
	cin >> n >> s;
	REP(i, n)
		cin >> C[0][i] >> C[1][i];
	dp[0][0] = 1;
	for(int i = 0; i < n;i++){
		for(int v = 10000; v >= 0; v--){
			if(v - C[0][i] >= 0 && dp[i][v-C[0][i]]){
				dp[i+1][v] = 1;	
				state[i][v] = 0;
			}
			else if(v - C[1][i] >= 0 && dp[i][v-C[1][i]]){
				dp[i+1][v] = 1;	
				state[i][v] = 1;
			}
		}
	}
	/*
	for(int v =0; v <= 20; v++)
		cout <<setw(2) << v << " ";
	cout <<endl; 
	for(int i = 0; i <=n ; i++){
		for(int v =0; v <= 20; v++){
			cout << setw(2) << dp[i][v] << " ";
		}
		cout << endl;
	}
		cout << endl;
	for(int i = 0; i <=n ; i++){
		for(int v =0; v <= 20; v++){
			cout << setw(2) << state[i][v] << " ";
		}
		cout << endl;
	}
	*/
	if(dp[n][s] == 1){
		cout << "Yes\n";
		vec<char> ans(n);
		for(int i = n-1; i >=0; i--){
			ans[i] = (state[i][s] == 1 ? 'T' : 'H');
			s -= C[state[i][s]][i];
		}
//		if(s != 0)
//			cout << "Errrorrrr\n";
		REP(i, n)
			cout << ans[i];
		cout <<endl;
	}
	else
		cout << "No\n";
	return 0;
}

