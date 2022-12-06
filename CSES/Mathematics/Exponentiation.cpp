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
const ll mod = 1e9 + 7;
ll binpow(ll a, ll b, ll p = mod){
	ll ans = 1;
	while(b){
		if(b & 1)
			(ans *= a) %= p;
		b >>= 1;
		(a *= a) %= p;
	}
	return ans;
}
int main(){
	yccc;		
	ll a, b;
	int n; 	
	cin >> n;
	while(n--){
		cin >> a >> b;
		cout << binpow(a, b) << endl;
	}
	return 0;
}

