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
const int maxn = 1000;
p<ll> pts[maxn];
int main(){
	yccc;		
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> pts[i].F >> pts[i].S;
	}
	ll ans = 0;
	for(int i = 0; i < n; i++){
		int ni = i + 1 == n ? 0 : i + 1;
		ans += (pts[i].F * pts[ni].S - pts[i].S * pts[ni].F);
	}
	cout << abs(ans) << endl;
	return 0;
}

