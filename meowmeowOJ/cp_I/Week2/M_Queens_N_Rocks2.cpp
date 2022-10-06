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
ll ans = 0;
int M, N;
void dfs(int r, int Q, int R){
	if(r == M+N){
		ans++;
		return;
	}
	for(int k = r; k < M+N; k++){
		int t = 0;
		for(int c = 0; c < M+N; c++){
			if(occu[c]) continue;
			int diaid = k + c + 1;
			if(dia[1][diaid]) continue;
			int backdia = k + (M+N - c - 1) + 1;
			if(dia[0][backdia]) continue;
			t++;	
		}
		if(t == 0) return;
	}
	for(int c = 0; c < M+N; c++){
		if(occu[c]) continue;
		int diaid = r + c + 1;
		if(dia[1][diaid]) continue;
		int backdia = r + (M+N - c - 1) + 1;
		if(dia[0][backdia]) continue;
		// push Queen
		if(Q < M && hasrock[0][backdia] == 0 && hasrock[1][diaid] == 0){
			occu[c] = dia[0][backdia] = dia[1][diaid] = 1;
			dfs(r+1, Q+1, R);
			occu[c] = dia[0][backdia] = dia[1][diaid] = 0;
		}
		if(R < N){
			// else push Rock
			occu[c] = 1;
			hasrock[0][backdia]++;
			hasrock[1][diaid]++;
			dfs(r+1, Q, R+1);
			occu[c] = 0;
			hasrock[0][backdia]--;
			hasrock[1][diaid]--;
		}
	}
}
int main(){
	int T;
	cin >> T;
	while(T--){
		ans = 0;
		cin >> M >> N;
		if(M == 0){
			ans = 1;	
			REP1(i, N){
				ans *= i;
			}
		}
		else
			dfs(0, 0, 0);
		cout << ans << endl;
	}
	return 0;
}
