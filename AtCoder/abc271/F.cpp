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
int mat[21][21];
int N;		
vec<int> mS[2][21];
int dir[2][2][2]= {
	{
	{1, 0},
	{0, 1},
	},
	{
	{-1, 0},
	{0 ,-1}
	}
};
inline bool valid(int r, int c){
	return (r > 0 && r <= N && c > 0 && c <= N);
}
void dfs(int r, int c, int cur, int st){
	if(r + c == N+1){
		mS[st][c].eb(cur);	
		return;
	}
	cur ^= mat[r][c];
	REP(i, 2){
		int nr = r + dir[st][i][0], nc = c + dir[st][i][1];
		if(valid(nr, nc) == false)
			continue;
		dfs(nr, nc, cur, st);
	}
}

int main(){
	cin >> N;
	REP1(i, N){
		REP1(j, N){
			cin >> mat[i][j];
		}
	}
	dfs(1, 1, 0, 0);
	dfs(N, N, 0, 1);
	REP1(i, N){
		sort(al(mS[1][i]));
	}
	ll ans = 0;
	REP1(c, N){
		for(int v: mS[0][c]){
			v ^= mat[N+1-c][c];
			auto itl = lower_bound(al(mS[1][c]), v);
			auto itu = upper_bound(al(mS[1][c]), v);
			ans += itu - itl;
		}
	}
	cout << ans << endl;
	return 0;
}

