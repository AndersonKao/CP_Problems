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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
char room[1002][1002];
int n, m;
void dfs(int r, int c){
	if(r < 0 || r == n || c < 0 || c == m)
		return ;
	if(room[r][c] == '#')
		return;
	room[r][c] = '#';
	dfs(r+1, c);
	dfs(r, c+1);
	dfs(r-1, c);
	dfs(r, c-1);
}
int main(){
	yccc;		
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> room[i][j];
		}
	}
	int cnt = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(room[i][j] == '.'){
				dfs(i, j);
				cnt++;
			}
		}
	}
	cout << cnt << endl;
	return 0;
}

