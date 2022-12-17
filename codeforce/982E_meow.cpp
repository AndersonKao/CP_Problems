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
ll extgcd(ll& x, ll& y, ll a, ll b){
	if ( b == 0 ){
		x = 1, y = 0;
		return a;
	}	
	ll xp, yp;
	ll g = extgcd(xp, yp, b, a % b);
	x = yp, y = xp - (a / b) * yp;
	return g;
}
int main(){
//	yccc;		
	int T;
	cin >> T;
	while(T--){

		ll n, m, x, y, vx ,vy;
		cin >> n >> m >> x >> y >> vx >> vy;
		if (vx==0){
			if (x==0||x==n){
				if (vy==1)
					cout << x << " " << m << endl;
				else
					cout << x << " " << 0 << endl;
			}
			else
				cout << -1 << endl;
			continue;
		}
		if (vy==0){
			if (y==0||y==m){
				if (vx==1)
					cout << n << " " << y << endl;
				else
					cout << 0 << " " << y << endl;
			}
			else
				cout << -1 << endl;
			continue;
		}
		bool refx = false, refy = false;
		if(vx == -1){
			refx = true, x = n - x;
		}
		if(vy == -1){
			refy = true, y = m - y;
		}

		ll c = x - y;
		ll px, py, g;
		g = extgcd(px, py, n, m);
		if(c % g != 0){
			cout << -1 << endl;
			continue;
		}
		
		ll t = c / g;
		px *= t, py *= t;
		ll _m = m / g, _n = n / g;
		ll _px = ((px % _m) + 2 * _m-1) % _m + 1; // _px can't be 0
		ll _py = - (c - _px * n) / m; // take (-) for latter usage.
		ll ansx = 0, ansy = 0;
		if(_px & 1)
			ansx = n;
		if(_py & 1)
			ansy = m;
			
		if(refx)
			ansx = n - ansx;
		if(refy)
			ansy = m - ansy;
		cout << ansx << " " << ansy << endl;

	}

	return 0;
}

