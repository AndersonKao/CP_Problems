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
ll ans = 0;
vec<pii> ansV;
void solve(int from, int to, int k){
	if(k == 1){
		ans++;
		ansV.eb(from, to);
		return;
	}
	int mid; 
	for(int i = 1; i <= 3; i++){
		if(i != from && i != to)
			mid = i;
	}
	solve(from, mid, k-1);
	solve(from, to, 1);
	solve(mid, to, k-1);
}

int main(){
	int n;
	cin >> n;
	solve(1, 3, n);
	printf("%lld\n", ans);
	for(pii v: ansV){
		printf("%d %d\n", v.F, v.S);
	}
	return 0;
}

