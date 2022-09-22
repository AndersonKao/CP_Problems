#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define F first
#define S second

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

ll ext_gcd(ll a, ll b, ll&x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = ext_gcd(b, a%b, x1, y1);
	x = y1;
	y = x1 - y1 * (a/b);
	return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g){
	g = ext_gcd(abs(a), abs(b), x0, y0);

	if( c % g){
		return false;
	}

	x0 *= c/g;
	y0 *= c/ g;
	if(a < 0) x0 = -x0;
	if(b < 0) y0 = -y0;
	return true;
}


ll exp_mul(ll a, ll b, ll m){
	ll ans = 0;

	do {
		if (b % 2) (ans += a) %= m;
		(a += a) %= m;
	} while (b >>= 1);

	return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n;
	cin>>n;
	while(n--) {

		ll a1, a2, a3, b1, b2, b3;
		cin>>a1>>b1;
		cin>>a2>>b2;
		cin>>a3>>b3;

		ll x1; ll y1;
		ll g;

		find_any_solution(a1, -1*a2, b2-b1, x1, y1, g);

		ll ans1 = a1 * x1 + b1;
		ans1 = ((ans1 % (a1*a2)) + a1*a2) % (a1*a2);
		ll k; ll z;

		find_any_solution(a1*a2, -1*a3, b3-ans1, k, z, g);
		
		ll total = a1 * a2 * a3;
		k = ((k % total) + total) % total;
		ll ans = ans1 % total + exp_mul(exp_mul(a1, a2, total), k, total);
//		ll ans = ans1%total + a1%total *a2 %total *k%total;
		ans = (ans%total + total)%total;
		cout<<ans<<"\n";

	}
}
