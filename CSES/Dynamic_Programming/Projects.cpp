
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
const int maxn = 200000;
ll dp[maxn*2+1];
struct event{
	int a, b;
	ll p;
};
int main(){
	yccc;		
	int n;
	cin >> n;
	vec<event> proj(n);
	vec<int> dates;
	for(event&e: proj){
		cin >> e.a >> e.b >> e.p;
		dates.eb(e.a), dates.eb(e.b);
	}
	sort(al(dates));
	dates.resize(unique(al(dates)) - dates.begin());
	for(event& e: proj){
		e.a = lower_bound(al(dates), e.a) - dates.begin() + 1;
		e.b = lower_bound(al(dates), e.b) - dates.begin() + 1;
	}
	sort(al(proj), [](event& e1, event& e2){
			return e1.b < e2.b;	
		}
	);
	dp[0] = 0;
	ll ans = 0;
	int idx = 0;
	for(int i = 1; i <= dates.size(); i++){
		dp[i] = dp[i-1];
		while(idx< n && proj[idx].b == i){
			event &e = proj[idx];	
			dp[e.b] = max(dp[e.b], dp[e.a-1] + e.p);
			idx++;
		}
		ans = max(ans, dp[i]);
	}

	cout << ans << endl;

	return 0;
}

