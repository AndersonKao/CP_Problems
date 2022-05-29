
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;

#define debug(x) cout << #x << ": " << x << endl;
map<int ,ll > S;
int main(){
	cin.tie(0), ios_base::sync_with_stdio(false);
	int Q;
	cin >> Q;
	while(Q--){
		int op;
		cin >> op;
		if(op == 1){
			int x;
			cin >> x;
			auto it = S.find(x);
			if(it != S.end() && it->F == x)
				(it->S)++;
			else
				S.emplace(x, 1);
		}
		else if(op == 2){
			int x;
			ll m;
			cin >> x >> m;
			auto it = S.lower_bound(x);
			if(it != S.end() && it->F == x){
				it->S -= min(it->S, m);
				if( it->S == 0)
					S.erase(it);	
			}
		}
		else if(op == 3){
			cout << (--S.end())->F - S.begin()->F << endl;
		}
	}
	return 0;
}
