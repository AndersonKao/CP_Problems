#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

int dp[200001][2];

int main(){
	yccc;		
	int n;
	string s;
	cin >> n >> s;

	dp[0][0] = 0;
	dp[0][1] = 1;
	for(size_t i = 1; i < s.length(); i++){
		if(s[i] == s[i-1]){
			dp[i][0] = dp[i-1][1];
			dp[i][1] = dp[i-1][0] + 1;
		}
		else{
			dp[i][0] = dp[i-1][0];
			if(	(s[i] == 'P' && s[i-1] == 'S') || 
				(s[i] == 'R' && s[i-1] == 'P') || 
				(s[i] == 'S' && s[i-1] == 'R') )
				dp[i][0] = max(dp[i][0], dp[i-1][1]);
			dp[i][1] = dp[i-1][1] + 1;
			if(	(s[i] == 'P' && s[i-1] == 'R') || 
				(s[i] == 'R' && s[i-1] == 'S') || 
				(s[i] == 'S' && s[i-1] == 'P') )
				dp[i][1] = max(dp[i][1], dp[i-1][0]+1);
		}
	}
	cout << max(dp[n-1][0], dp[n-1][1]) << endl;

	return 0;
}
