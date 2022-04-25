#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define minp first
#define maxp second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;

vec<vec<int>> seq;
vec<vec<ll>> dp;
vec<pii> peak; // 

/*
ll getcost(ll st, ll ed, pll peak){
	if(st >= ed){
		if(peak.maxp >= st && st >= ed && ed >= peak.minp){
			return peak.maxp - st + peak.maxp - peak.minp + ed - peak.minp;
		}else if(peak.maxp >= st && st >= ed && peak.minp == ed){
			return peak.maxp - st + peak.maxp - ed;
		}else if(st >= peak.maxp && peak.minp == ed) {
			return st - ed;
		}else if(st >= peak.maxp && peak.maxp >= ed && ed >= peak.minp) {
			return peak.kkkk	
		}
	}
	else{

	}
}
*/

int main(){
	yccc;	
	int T;
	cin >> T;
	int cnt = 1;
	while(T--){
		int n, p;
		cin >> n >> p;
		seq.clear();
		seq.resize(n, vec<int>(p));
		dp.clear();
		dp.resize(n, vec<ll>(p, numeric_limits<ll>::max()));
		peak.clear();
		peak.resize(n, {numeric_limits<int>::max(), numeric_limits<int>::min()});
		REP(i, n){
			REP(j, p){
				cin >> seq[i][j];
				peak[i].minp = min(peak[i].minp, seq[i][j]);
				peak[i].maxp = max(peak[i].maxp, seq[i][j]);
			}
		}
		REP(j, p){
			dp[0][j] = abs(peak[0].maxp - 0) + abs(peak[0].maxp - abs(seq[0][j]));
		}	
		for(int i = 1; i < n; i++){
			REP(j, p){
				REP(k, p){
//					dp[i][j] = 
					if(seq[i-1][k] >= seq[i][j])
						dp[i][j] = min(dp[i][j], abs(peak[i].maxp - seq[i-1][k]) + abs(peak[i].maxp -peak[i].minp) + abs(seq[i][j] - peak[i].minp) +dp[i-1][k]);
					if(seq[i-1][k] <= seq[i][j])
						dp[i][j] = min(dp[i][j], abs(peak[i].minp - seq[i-1][k]) + abs(peak[i].maxp -peak[i].minp) + abs(seq[i][j] - peak[i].maxp) +dp[i-1][k]);
				}	
			}	
		}
		ll ans = numeric_limits<ll>::max();
		REP(j, p){
			ans = min(dp[n-1][j], ans);
		}
		cout << "Case #" << cnt++ << ": " << ans  << endl;


	}	
}
