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
const ll bound = 3*1e14;
int main(){
	yccc;		
	int t; cin >> t; 
	while(t--){
		ll n; cin >> n;
		ll sum = 4*1e12;
		ll root = 2*1e6;
		ll L = root - 1e6, R = root + 1e6;

		ll cnt = n/2;
		for(ll i = L; i < L + cnt; i++){
			cout << i << " ";
		}
		if(n & 1){
			cout << root << " ";
		}
		for(ll i = R; i > R - cnt; i--){
			cout << i << " ";
		}
		cout << endl;
	

	}
	return 0;
}

