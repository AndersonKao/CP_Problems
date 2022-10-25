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
char mat[8][8];
int dia[2][16] = {0}; // 0 for \, 1 for /
int occu[8] = {0};
int ans = 0;
void dfs(int r){
	if(r == 8){
		ans++;
		return;
	}
	for(int c = 0; c < 8; c++){
		if(mat[r][c] == '*') continue;
		if(occu[c]) continue;
		int diaid = r + c + 1;
		if(dia[1][diaid]) continue;
		int backdia = r + (8 - c - 1) + 1;
		if(dia[0][backdia]) continue;
		occu[c] = dia[0][backdia] = dia[1][diaid] = 1;
		dfs(r+1);
		occu[c] = dia[0][backdia] = dia[1][diaid] = 0;
	}
}
int main(){
	REP(i, 8){
		REP(j, 8){
			cin >> mat[i][j];
		}
	}
	dfs(0);
	cout << ans << endl;
	return 0;
}

