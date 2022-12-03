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
int sol[200001];
int main(){
//	yccc;		
	int T;cin >> T;
	while(T--){
		int n, x;
		cin >> n >> x;
		fill(sol, sol + n + 1, 0);
		if(x == 1){
			cout << (n == 1 ? "1\n" : "-1\n");	
			continue;
		}
		if(n % x != 0){
			cout << "-1\n";
			continue;
		}
		sol[1] = x;
		while(x <= n){
			if(x == n){
				sol[x] = 1; break;
			}
			for(ll i = 2; i * x <= n ; i++){
				if(n % (i * x) == 0){
					sol[x] = i * x;
					x = i * x;
					break;
				}
			}
		}
		for(int i = 1; i <= n; i++){
			cout << (sol[i] == 0 ? i : sol[i]) << (i == n ? "\n" : " ");
		}
	}
	return 0;
}

