
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
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		vec<p<int>> V(3);
		for(p<int> &e: V){
			cin >> e.F >> e.S;
		}
		bool ans = false;
		int r, c;
		cin >> r >> c;
		for(p<int> &e: V){
			if(r == e.F && c == e.S){
				cout << "YES\n";
				ans =true;
			}
		}
		if(ans)
			 continue;

		sort(al(V));
		p<int> ancor;
		if(V[0].F != V[1].F){
			/*
			*
			** 
			*/
			if(V[0].S == V[1].S){
				ancor = V[1];
			}
			else
				ancor = V[2];
		}
		else{
			/*
**
*
			*/
			if(V[0].S == V[2].S){
				ancor = V[0];
			}
			else
				ancor = V[1];
		}
		/*
		debug(ancor.F);
		debug(ancor.S);
		*/
		if((ancor.F == 1 || ancor.F == n) && (ancor.S == n || ancor.S == 1)){
			if(ancor.F == r || ancor.S == c){
				cout << "YES\n";
			}
			else
				cout << "NO\n";
		}
		else{
			int rdiff = abs(ancor.F - r);
			int cdiff = abs(ancor.S - c);
			if(rdiff & 1 && cdiff & 1)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
		
	return 0;
}

