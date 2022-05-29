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

int main(){
	char table[102][102];
	int h, w;
	cin >> h >> w;
	pii st, ed;
	st = ed = {-1, -1};
	REP(i, h){
		REP(j, w){
			cin >> table[i][j];
			if(table[i][j] == 'o'){
				if(st.F == -1)
					st.F = i, st.S = j;
				else
					ed.F = i, ed.S = j;
			}	
		}
	}
	cout << abs(st.F - ed.F) + abs(st.S - ed.S) << endl;
	

	return 0;
}
