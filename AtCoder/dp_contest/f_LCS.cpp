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

int dp[3001][3001] = {0};
p<int> from[3001][3001];
int main(){
	yccc;		
	string s, t;
	cin >> s >> t;
	for(int i = 1; i <= s.length(); i++){
		for(int j = 1; j <= t.length(); j++){
			if(s[i-1] == t[j-1]){
				dp[i][j] = dp[i-1][j-1] + 1;
				from[i][j] = {i-1, j-1};
			}
			else{
				if(dp[i-1][j] > dp[i][j-1]){
					from[i][j] = {i-1, j};
				}
				else{
					from[i][j] = {i, j-1};
				}
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
	string ans = "";
	p<int> cur(s.length(), t.length());
	while(cur.F > 0 && cur.S > 0){
		p<int> pre = from[cur.F][cur.S];
		if(pre.F != cur.F && pre.S != cur.S){
			ans += s[cur.F-1];
		}	
		cur = pre;
	}
	reverse(ans.begin(), ans.end());
	if(ans.length())
		cout << ans;
	return 0;
}

