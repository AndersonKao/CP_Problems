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
	vec<int> layer(5 * 100000, 0);
	for(int &e: V){
		cin >> e;
	}
	for(int i = 0; i < n; i++){
		layer[(i+1) * 2] = layer[V[i]] + 1;
		layer[(i+1) * 2 + 1] = layer[V[i]] + 1;
	}
	for(int i = 1; i <= 2*n+1; i++){
		cout << layer[i] << endl;
	}
	return 0;
}

