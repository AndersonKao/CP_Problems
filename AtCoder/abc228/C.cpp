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
	int n, k;
	cin >> n >> k;	
	vec<p<int>> V(n, p<int>(0, 0));
	for(int i = 0; i < n; i++){
		int v;
		V[i].S = i;
		REP(j, 3){
			cin >> v;
			V[i].F += v;
		}
	}
	sort(al(V));
	vec<bool> ans(n, false);
	for(int i = 0; i < n; i++){
		int score, id;
		tie(score, id) = V[i];
		int rank = (V.end() -  upper_bound(al(V), p<int>(score + 300, n+2))) + 1;
		if(rank <= k){
			ans[id] = true;
		}
	}
	for(int i = 0; i < n; i++){
		cout << (ans[i] ? "Yes" : "No") << endl;
	}
	return 0;
}

