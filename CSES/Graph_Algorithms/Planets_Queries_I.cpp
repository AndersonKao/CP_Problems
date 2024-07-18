#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int nt[200001][32]; // nt(u, i) start from u, jump for 2^i steps;

void build(int n){
	for(int i = 1; i < 32; i++){
		for(int u = 1; u <= n; u++){
			nt[u][i] = nt[nt[u][i-1]][i-1];
		}
	}
}

int main() {
	yccc;
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> nt[i][0];
	}
	build(n);
	while(q--){
		int x, k;
		cin >> x >> k;
		int u = x;
		for(int i = 0; (1 << i) <= k; i++){
			if(k & (1 << i)){
				u = nt[u][i];
			}
		}
		cout << u << endl;
	}
	return 0;
}
