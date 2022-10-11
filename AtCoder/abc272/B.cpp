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
int meet[101][101] = {0};
int main(){
	int n;
	cin >> n;
	int m;
	cin >> m;
	vec<vec<int>> V(m);
	REP(i, m){
		int k;
		cin >> k;
		V[i].resize(k);
		REP(j, k){
			cin >> V[i][j];
		}
		REP(j, k){
			for(int j2 = j + 1; j2 < k; j2++){
				meet[V[i][j]][V[i][j2]] = meet[V[i][j2]][V[i][j]] = 1;
			}
		}
	}
	bool ans = true;
	REP1(i, n){
		for(int j = i+1; j<= n; j++){
			if(meet[i][j] == 0)
				ans = false;
		}
	}
	cout << (ans ? "Yes" : "No") << endl;
	return 0;
}

