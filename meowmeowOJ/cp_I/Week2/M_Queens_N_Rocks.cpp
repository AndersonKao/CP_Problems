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
int dia[2][40] = {0}; // 0 for \, 1 for /
int hasrock[2][40] = {0}; // 0 for \, 1 for /
int occu[20] = {0};
int occr[20] = {0};
ll ans = 0;
int M, N;
vec<p<int>> RowV;
void dfs2(int id, int R){
	if(id == N){
			ans++;
		return;
	}
	int r = RowV[id].S;
	if(occr[r]){
		dfs2(id+1, R);
	}
	else if(R < N){
		for(int c = 0; c < M+N; c++){
			if(occu[c]) continue;
			int diaid = r + c + 1;
			if(dia[1][diaid]) continue;
			int backdia = r + (M+N - c - 1) + 1;
			if(dia[0][backdia]) continue;
			// else push Rock
			occu[c] = 1;
			dfs2(id+1, R+1);
			occu[c] = 0;
		}
	}
}
void dfs(int r, int Q){
	if(r == M+N){
		if(Q == M){
			/*
			if(N != 0){
				dfs2(0, 0);
			}
			else
			*/
				ans++;
		}
		return;
	}
	if(M-Q > M + N - r){
//		cout << "cut\n";
		return;
	}
	dfs(r+1, Q);
	occr[r] = 1;
	if(Q < M){
		for(int c = 0; c < M+N; c++){
			if(occu[c]) continue;
			int diaid = r + c + 1;
			if(dia[1][diaid]) continue;
			int backdia = r + (M+N - c - 1) + 1;
			if(dia[0][backdia]) continue;
			// put Queen
			occu[c] = dia[0][backdia] = dia[1][diaid] = 1;
			
			dfs(r+1, Q+1);
			occu[c] = dia[0][backdia] = dia[1][diaid] = 0;
		}
	}
	occr[r] = 0;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		ans = 0;
		cin >> M >> N;
		cout << "case: " << M << ", " << N << endl;
		if(M == 0){
			ans = 1;	
			REP1(i, N){
				ans *= i;
			}
		}
		else
			dfs(0, 0);
		cout << ans << endl;
	}
	return 0;
}

