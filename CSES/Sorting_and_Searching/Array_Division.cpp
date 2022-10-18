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
	vec<int> V(n);
	ll l = 1;
	for(int&e: V){
		cin >> e;
		l = max(l, (ll)e);
	}

	ll r = 200000*2*1e9;
	while(l < r){
		ll m = (l+r) >> 1;
		int num = 0;
		ll cur = 0;
		for(int v : V){
			if(cur + v < m){
				cur += v;	
			}
			else if(cur + v == m){
				num++;
				cur = 0;
			}
			else{
				num++;	
				cur = v;
				if(v > m){
					num = 500000;
					break;
				}
			}
		}
		if(cur != 0){
			num++;
		}
		/*
		debug(l);
		debug(r);
		debug(m);
		debug(num);
		*/
		if(num <= k){
			r = m;
		}
		else{
			l = m + 1;
		}
	}
	cout << l << endl;
	return 0;
}

