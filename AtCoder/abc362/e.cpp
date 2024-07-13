
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

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
const ll MOD = 998244353;

map<int, ll> M[81][80]; // (k), d, i;

int main() {
	yccc;
	int n; 
	cin >> n;
	vec<ll> V(n);
	for(int i = 0; i < n; i++){
		cin >> V[i];
	}
	vec<ll> Ds;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			Ds.eb(V[i] - V[j]);
		}
	}
	sort(al(Ds));
	Ds.resize(unique(al(Ds)) - Ds.begin());

	/*
	cout << "Ds: " ;
	for(int d: Ds){
		cout << d << ' ';
	}
	cout << endl;
	*/
	
	cout << n << ' ';

	for(int i = 0; i < n; i++){
		for(int d: Ds){
			M[1][i][d] = 1;
		}
	}

	for(int k = 2; k <= n; k++){
		//cout << "k = " << k << endl;
		ll ans = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < i; j++){
				int d = V[i] - V[j];
				auto it = M[k][i].find(d);
				if(it == M[k][i].end()){
					M[k][i][d] = M[k-1][j][d];
				}
				else{
					it->second += M[k-1][j][d];
					it->second %= MOD; 
				}
			}
			for(auto& node :M[k][i]){
				ans += node.second;
				ans %= MOD;
			}
		}

		/*
		for(int i = 0; i < n; i++){
			for(auto& node: M[k][i]){
//			cout << "d = " << node.first.first << " i = " << node.first.second << " : " << node.second << endl;
				ans += node.second;
			}
		}
		*/
		cout << ans << (k == n ? '\n' : ' ');
	}

	return 0;
}
