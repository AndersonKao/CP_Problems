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
vec<int> ans;

int main(){
	int n;
	cin >> n;
	ans.resize(1 << n);
	ans[0] = 0;
	ans[1] = 1;
	for(int k = 1; k < n; k++){
		for(int i = (1 << k); i < (1 << (k+1)); i++){
			ans[i] = ans[(1 << k) - 1 - (i - (1 << k))] + (1 << k);
		}
	}
	for(int k = 0; k < (1 << n); k++){
		for(int i = n-1; i >= 0; i--)
			cout <<	((ans[k] & (1 << i)) ? "1" : "0");
		cout << "\n";
	}
	return 0;
}

