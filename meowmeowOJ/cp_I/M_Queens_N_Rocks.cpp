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
int occr[20] = {0};
ll ans = 0;
int Anum, Bnum;
int N;
int MASK;
vec<p<int>> RowV;
inline int lowbit(int x){
	return x & (~x + 1);
}
void dfs2(int r, int b, int M){
	if(r == N){
			ans++;
		return;
	}
	if(occr[r]){
		dfs2(r+1, b, M);
	}
	else{
		int validmask = (~M & MASK);
		for(int res; validmask; validmask ^= res){
			res = lowbit(validmask);
			int c = __lg(res);
			int diaid = r + c + 1;
			if(dia[1][diaid]) continue;
			int backdia = r + (N - c - 1) + 1;
			if(dia[0][backdia]) continue;
			// else push Rock
			dfs2(r+1, b+1, M | res);
		}
	}
}
void dfs(int r, int a, int L, int M , int R){
	if(Anum - a > N - r){
		return;
	}
	if(r == N){
		if(Bnum != 0){
			dfs2(0, 0, M);
		}
		else{
			ans++;
		}
		return;
	}
//	debug(r);
	dfs(r+1, a, L << 1, M, R >> 1);
	occr[r] = 1;
	if(a < Anum){
//		cout << "push queen\n";
		int validmask = (~(L | M | R)) & MASK;
		for(int res; validmask; validmask ^= res){
			res = lowbit(validmask);
			int c = __lg(res);
			int diaid = r + c + 1;
			int backdia = r + (N - c - 1) + 1;
			dia[0][backdia] = dia[1][diaid] = 1;
			dfs(r+1, a+1, (L | res) << 1, M | res, (R | res) >> 1);
			dia[0][backdia] = dia[1][diaid] = 0;
		}
	}
	occr[r] = 0;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		ans = 0;
		cin >> Anum >> Bnum;
//		cout << "case: " << Anum << ", " << Bnum << endl;
		if(Anum == 0){
			ans = 1;	
			REP1(i, Bnum){
				ans *= i;
			}
		}
		else{
			N = Anum + Bnum;
			MASK = (1 << N) - 1;
			dfs(0, 0, 0, 0, 0);
		}
		cout << ans << endl;
	}
	return 0;
}

