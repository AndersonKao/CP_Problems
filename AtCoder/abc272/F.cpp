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

int main(){
	int n;
	cin >> n;
	vec<int> V(n);
	for(int &v: V)
		cin >> v;
	bool found = false;
	int m = 3;
	for(m = 3; !found && m <= 5000; m++){
		vec<int> cnt(m, 0);
		for(int& v:V){
			cnt[v % m]++;
		}
		int mx = 0;
		for(int nu: cnt)
			mx = max(mx, nu);
		if(2*mx > n)
			found = true;
	}
	cout << (m == 5001 ? -1 : m-1) << endl;
	return 0;
}

