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
char mat[1000][1000];
int main(){
	int n, m;
	cin >> n  >> m;
	REP(i, n){
		REP(j, m){
			cin >> mat[i][j];
		}
	}
	REP(j, m){
		int cnt = 0;
		REP(i, n){
			if(mat[i][j] == '#')
				cnt++;
		}
		cout << cnt << " ";
	}
	return 0;
}

