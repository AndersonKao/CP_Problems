#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 200000;

ll prex[maxn+5];
ll prey[maxn+5];
ll cnt[2000001];

int main(){
	yccc;		
	int n, D;
	cin >> n >> D;
	vec<int> X(n);
	vec<int> Y(n);
	for(int i = 0; i < n; i++){
		cin >> X[i];
		cin >> Y[i];
//		cin >> V[i].F >> V[i].S;
	}

	sort(al(X));
	sort(al(Y));

	for(int i = 0; i < n; i++){
		prex[i+1] = prex[i] + X[i];	
		prey[i+1] = prey[i] + Y[i];
	}
	/*for(int i = 0; i < n; i++){
		debug(i);
		debug(prex[i]);
		debug(prey[i]);
	}*/

	/*
	int mid = 0;
	for(int i = 0; i <= n; i++){
		int y = Y[i]-1;
		yD[i] += (y * i - prey[i]);
		yD[i] += ((prey[n] - prey[i]) - y * (n-i));
		if(yD[i] < yD[mid]){
			mid = i;
		}
	}*/
	int yi = 0;
	for(ll y = -2000000; y <= 2000000; y++){
		ll curD = 0;
		while(yi < n && Y[yi] == y){
			yi++;
		}
		curD += (y * yi - prey[yi]);
		curD += (prey[n] - prey[yi] - y * (n - yi));
		if(curD <= D){
			cnt[curD]++;
		}
	}
	for(int i = 1; i <= D; i++){
		cnt[i] = cnt[i-1] + cnt[i];
	}

	ll ans = 0;
	int xi = 0;
	for(ll x = -2000000; x <= 2000000; x++){
		ll curD = 0;
		while(xi < n && X[xi] == x){
			xi++;
		}
		curD += (x * xi - prex[xi]);
		curD += (prex[n] - prex[xi] - x * (n - xi));
		if(curD > D)
			continue;
		ll remainD = D - curD;
		ans += cnt[remainD];
	}
	cout << ans << endl;

	return 0;
}

