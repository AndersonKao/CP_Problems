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
	int s;
	cin >> n >> s;
	vec<p<int>> V(n);
	for(int i = 0; i < n; i++){
		cin >> V[i].F;
		V[i].S = i + 1;
	}
	sort(al(V));
	bool found = false;
	int l,r;
	for(int i = 0; i < n; i++){
		auto it = lower_bound(al(V), p<int>(s-V[i].F, -1));	
		if(it != V.end() && it->F == s-V[i].F){
			if(it - V.begin() == i){
				it++;
				if(it != V.end() && it->F == s-V[i].F){
					l = V[i].S;	
					r = it->S;
					found = true;
				}
			}
			else{
					found = true;
					l = V[i].S;
					r = it->S;
			}
		}
	}
	if(found){
		swap(l, r);
		cout << l << " " << r << endl;
	}
	else{
		cout << "IMPOSSIBLE\n";
	}
			
	return 0;
}

