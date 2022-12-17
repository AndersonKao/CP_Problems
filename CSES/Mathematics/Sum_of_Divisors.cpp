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
const ll mod = 1000000007;
p<ll> extgcd(ll a, ll b){
	if(b == 0) return {1, 0};
	ll px, py;
	tie(px, py) = extgcd(b, a % b);
	return {py, px - (a / b) * py};
}
ll two_inv;

ll get_sum(ll begin, ll end){
	return ((((begin + end) % mod) * ((end - begin + 1) % mod) % mod) * two_inv) % mod; 
}

int main(){
	two_inv = (extgcd(2, mod).F % mod + mod) % mod;
	yccc;		
	ll n;
	cin >> n;
	ll ans = 0;
	ll cur = 1;
	while(cur <= n){
		ll q = n / cur;
		ll last_cur = n / q;
		ans += q * get_sum(cur, last_cur) % mod;	
		ans %= mod;
		cur = last_cur + 1;
	}

	cout << ans;

	return 0;
}

