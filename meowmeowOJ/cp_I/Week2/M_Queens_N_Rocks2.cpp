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
int Anum, Bnum;
int N;
int MASK;
inline int lowbit(int x){
	return (x & (~x + 1));
}

void dfs(int r, int a, int b, int L, int M, int R/*, int qL, int qM, int qR*/){
	if(r == N){
		ans++;
		return;
	}
	int validmask = (~(L | M | R)) & MASK;
//	cout << bitset<20>(validmask) << endl;
	int res;
	for(;validmask; validmask ^= res){
		res = lowbit(validmask);
		int c = N - __lg(res) - 1;
		int diaid = r + c + 1;
		int backdia = r + (N - c - 1) + 1;
		// push Queen
		if(a < Anum && hasrock[0][backdia] == 0 && hasrock[1][diaid] == 0){
			dfs(r+1, a+1, b, (L | res) << 1, M | res, (R | res) >> 1);
		}
		if(b < Bnum){	// push Rock
			hasrock[0][backdia]++;
			hasrock[1][diaid]++;
			dfs(r+1, a, b + 1, L << 1, M | res, R >> 1);
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
			/*
			for(int i = 0; i < N; i++){
				cout << i << ": " << lowbit(i) << "   " << __lg(lowbit(i)) << endl;
			}
			*/
			MASK = (1 << N) - 1;
			dfs(0, 0, 0, 0, 0, 0/*, 0, 0, 0*/);
		}
		cout << ans << endl;
	}
	return 0;
}
