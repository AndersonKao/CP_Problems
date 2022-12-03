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

int main(){
//	yccc;		
	int q; cin >> q;
	while(q--){
		ll k; cin >> k;
		if(k <= 9){
			cout << k << "\n"; continue;
		}
		ll res = 9;
		ll base = 0;
		ll len = 1;
		while(k > res * len){
			k -= res * len;	
			base += res;
			res *= 10;
			len++;
		}
		base += k / len;
		ll rem = k % len;			
		if(rem == 0){
			cout << base % 10 << '\n'; continue;
		}
		base += 1;
		for(int i = 0; i < len - rem; i++){
			base /= 10;	
		}
		cout << base % 10 << '\n';
	}
	return 0;
}

