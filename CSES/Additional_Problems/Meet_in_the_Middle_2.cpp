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

vector<ll> ways, waysback;
int V[40];
int n;
ll x;
void getsubset(int l, int r, vector<ll>& res){
	int len = (r - l) + 1;
	for(int mask = 0; mask < (1 << len); mask++){
		ll sum = 0;
		for(int i = 0; i < len; i++){
			if(mask & (1 << i)){
				sum += V[l+i];
			}
		}
		res.eb(sum);
	}
}
int main(){
	cin >> n >> x;
	REP(i, n){
		cin >> V[i];
	}
	getsubset(0, n/2-1, ways);	
	getsubset(n/2, n-1, waysback);	
	sort(al(ways));
	sort(al(waysback));
	ll ans = 0;
	for(ll&val: ways){
		auto itl = lower_bound(al(waysback), x-val);
		auto itu = upper_bound(al(waysback), x-val);
		ans += itu - itl;
	}
	cout << ans << endl;
		
	return 0;
}

