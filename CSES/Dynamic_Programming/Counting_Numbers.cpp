#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

ll dpa[20][2][10]; // i-th,  tight, i-th number;
ll dpb[20][2][10]; // i-th,  tight, i-th number;

inline int nu(char a){
	return a - '0';
}

ll fill(ll dp[][2][10], string& str){
	if(str.length() == 1 && str[0] == '0')
		return 1;
	// base case
	// tight
	dp[str.length()-1][1][nu(str[0])] = 1;
	// loose
	for(int d = 1; d < nu(str[0]); d++){
		dp[str.length()-1][0][d] = 1;	
	}
	// inductive case
	for(int i = str.length() - 2; i >= 0; i--){
		int sid = str.length() - 1 - i;
		int tightnum = nu(str[sid]);
		int pretightnum = nu(str[sid-1]);
		// tight
		if(tightnum != pretightnum){
			dp[i][1][tightnum] += dp[i+1][1][pretightnum];
		}
		// loose
		for(int d = 1; d <= 9; d++)
			dp[i][0][d] += 1; // leading zero
		for(int d = 0; d <= 9; d++){
			for(int x = 0; x <= 9; x++){
				if(x == d) continue;
				dp[i][0][d] += dp[i+1][0][x];
			}
			if(d != pretightnum && d < tightnum){
				dp[i][0][d] += dp[i+1][1][pretightnum];
			}
		}
	}

	ll ans = 0;
	for(int d = 0; d <= 9; d++){
		ans += dp[0][0][d];
		ans += dp[0][1][d];
	}

	return ans + 1; // +1 for "0";
}

bool valid(string& number){
	for(size_t i = 1; i < number.length(); i++){
		if(number[i] == number[i-1])
			return false;
	}
	return true;
}

int main() {
	yccc;
	string a, b;
	cin >> a >> b;

	ll ans_a = fill(dpa, a);
	ll ans_b = fill(dpb, b);

	ll ans = ans_b - ans_a;
	if(valid(a)){
		ans++;
	}
	cout << ans << endl;

	return 0;
}
