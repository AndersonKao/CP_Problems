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
	int n, q;
	cin >> n >> q;
	vec<ll> v(n+1, 0);	
	for(int i = 1; i<= n;i++){
		int val;
		cin >> val;
		v[i] = v[i-1] + val;
	}
	for(int i = 1; i<= q;i++){
		int l, r;
		cin >> l >> r;
		cout << v[r] - v[l-1] << endl;
	}

	return 0;
}

