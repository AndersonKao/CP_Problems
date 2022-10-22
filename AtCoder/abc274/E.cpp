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
struct point{
	ll x, y;
	point(){}
	point(ll x, ll y):x(x), y(y){}
};
vec<point> pts;
double dis(int i, int j){
	ll xd = pts[i].x - pts[j].x;
	ll yd = pts[i].y - pts[j].y;
	return sqrt(xd*xd + yd*yd);
}
int lowbit(int x){
	return (x & (~x + 1));
}
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n + m; i++){
		ll x, y;
		cin >> x >> y;
		pts.eb(x, y);
	}
	vec<vec<double>> dp(17, vec<double>(1<<17, 1e20));
	for(int i = 0; i < n+m; i++){
		dp[i][(1 << i)] = sqrt(pts[i].x * pts[i].x + pts[i].y * pts[i].y);
	}
	for(int amask = 1; amask < (1 << (n+m)); amask++){
		if(amask == lowbit(amask)) continue;
		for(int res = amask;res; res -= lowbit(res)){
			int i = __lg(lowbit(res));
//			cout << "gen: " << bitset<5>(amask) << "-----\n";
//			debug(i);
			int fromask = amask - lowbit(res);
			int acced = 1;	
			int acmask = fromask >> n;
			while(acmask){
				acced <<= (acmask & 1);
				acmask >>= 1;
			}
//			cout << bitset<17>(fromask) << endl;
//			debug(acced);
			for(int resfrom = fromask; resfrom; resfrom -= lowbit(resfrom)){
				int j = __lg(lowbit(resfrom));
				dp[i][amask] = min(dp[i][amask], dp[j][fromask] + dis(i, j) / (double)acced);
				/*
				cout << "get from: " << bitset<5>(fromask) << "-----\n";
				debug(j);
				debug(dp[j][fromask]);
				debug(dis(i, j));
				*/	
			}
		}
	}

	/*
	for(int amask = 0; amask < (1 << (m+n)); amask++){
		for(int res = amask; res; res -= lowbit(res)){
			int i = __lg(lowbit(res));
			cout << "dp of " << bitset<5>(amask) << " and ";
			debug(i);
			debug(dp[i][amask]);
		}
	}
	*/
	double ans = numeric_limits<double>::max();
	int cmask = (1 << n) - 1;
	for(int amask = 0; amask < (1 << m); amask++){
		int tmask = cmask + (amask << n);	
		int acced = 1;	
		int acmask = amask;
		while(acmask){
			acced <<= (acmask & 1);
			acmask >>= 1;
		}
		for(int res = tmask; res; res -= lowbit(res)){
			int i = __lg(lowbit(res));

			double toans = dp[i][tmask] + sqrt(pts[i].x * pts[i].x + pts[i].y * pts[i].y) / (double)acced;
			ans = min(ans, toans);
		}	
	}
	cout << fixed << setprecision(8) << ans << endl;
	
	return 0;
}

