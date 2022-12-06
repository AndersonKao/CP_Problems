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
const int maxn = 1000000;
const int mod = 1e9+7;
int fact[maxn+1];
int tcaf[maxn+1];
int binpow(int a, int b, int p = mod){
	if(b < 0){
		b += (p-1);
	}
	int res = a;
	int ans = 1;
	while(b){
		if(b & 1){
			ans = (1LL * ans * res) % mod;	
		}
		b >>= 1;
		res = (1LL * res * res) % mod;
	}
	return ans;
}
void build(){
	fact[0] = tcaf[0] = 1;
	fact[1] = tcaf[1] = 1;
	for(int i = 2; i <= maxn; i++){
		fact[i] = (1LL * fact[i-1] * i) % mod;
	}
	for(int i = 2; i <= maxn; i++){
		tcaf[i] = (1LL * tcaf[i-1] * binpow(i, -1)) % mod;
	}
}
int main(){
	yccc;		
	build();
	int n;
	cin >> n;
	while(n--){
		int a, b;
		cin >> a >> b;
		cout << (1LL * fact[a] * tcaf[b] % mod * tcaf[a-b] % mod) << endl;
	}
	return 0;
}

