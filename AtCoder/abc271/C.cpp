
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
	cin >> n;
	vec<int> V(n);		
	set<int> mS;
	int useless = 0;
	REP(i, n){
		cin >> V[i];
		if(mS.count(V[i]))
			useless++;
		mS.insert(V[i]);
	}
	vec<int> cp = V;	
	sort(al(V));
	V.resize(distance(V.begin(), unique(al(V))));
	
	int cur = 1;
	for(int i = 0; i < V.size(); i++){
		if(V[i] != cur){
			if(V.size() - i + useless >= 2){
				if(useless >= 2)
					useless-=2;
				else {
					for(int i = 0; i< 2-useless; i++)
						V.pop_back();
					useless = 0;
				}
				i--;
			}
			else{
				break;
			}
		}
		cur++;
	}
	cout << cur-1 + useless / 2 << endl;
	return 0;
}

