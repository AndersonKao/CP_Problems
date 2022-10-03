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
char to(int x){
	if(x < 10){
		return '0'+x;
	}
	else{
		return 'A' + (x-10);
	}
}

int main(){
	int n, q;
	cin >> n >> q;	
	vec<vec<int>> V(n);
	REP(i, n){
		int k;
		cin >> k;
		V[i].resize(k);
		REP(j, k)
			cin >> V[i][j];	
	}
	REP(i, q){
		int s, t;
		cin >> s >> t;
		s-- ,t--;
		cout << V[s][t] << "\n";
	}
	return 0;

}

