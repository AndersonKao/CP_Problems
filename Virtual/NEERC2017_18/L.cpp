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
struct tdata{
	ll a, b;
	int na, nb;
	tdata(){}
	tdata(ll a, int na, ll b, int nb):a(a), na(na), b(b), nb(nb){}
};
vec<tdata> ans;
int main(){
	freopen("little.in", "r", stdin);
	freopen("little.out", "w", stdout);
	
	ll n;
	cin >> n;
	if((n & (-n)) == n){
		cout << "-1\n";
		return 0;
	}
	ans.eb(n, 1, 0, 0);

	ll sqn = sqrt(n);
	for(ll i = sqn - 2; i <= sqn+2; i++){
		if(i * i == n){
			ans.eb(i, 2, 0, 0);
		}
		if(i * (i+1) == n){
			ans.eb(i, 1, i+1, 1);
		}
	}

	for(ll i = 2; i * i * i <= n; i++){
		if(n % i == 0){
			vec<ll> tmp;
			ll res = n;
			int na = 0, nb = 0;
			while(res > 1 && res % i == 0){
				res /= i;
				na++;
			}
			while(res > 1 && res % (i+1) == 0){
				res /= (i+1);
				nb++;
			}
			if(res == 1)
				ans.eb(i, na, i+1, nb);
		}
	}
	cout << ans.size() << "\n";	
	for(tdata& t: ans){
		cout << t.na + t.nb;
		REP(i, t.na){
			cout << " " << t.a;
		}
		REP(i, t.nb){
			cout << " " << t.b;
		}
		cout << "\n";
	}

		
	return 0;
}

