// temporarily give up.
// outline dp approach
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
int inf = 0x3f3f3f3f;
int R, C;
int mat[11][6];
pair<int, int> Ast, Aed, Bst, Bed;
int ANS = inf;
int dp[11][6][20];
int up(int r, int c){
	int t = c == 0 ? 0 : 2*(c-1)+1;
	return ((1 << (2*C+1)) - 1) - ((1 << t) - 1);	
}
bool isA(int r, int c){
	return p<int>(r+1, c+1) == Ast || p<int>(r+1, c+1) == Aed;
}
bool isB(int r, int c){
	return p<int>(r+1, c+1) == Bst || p<int>(r+1, c+1) == Bed;
}
int exact(int state){
	int ans = 0;
	for(int i = 0; i < 3; i++){
		if(state & (0b11 << i))
			ans++;
	}
	return ans;
}
int type(int state){
	for(int i = 0; i < 3; i++){
		if(state & (0b11 << i))
			return (state & (0b11 << i) >> i;
	}
	return 0;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> R >> C;
		cin >> Ast >> Aed >> Bst >> Bed; 
		REP1(i, R){
			REP1(j, C){
				cin >> mat[i][j];
			}
		}
		for(int r = 0; r < 11; r++){
			for(int c = 0; c < 6; c++){
				for(int i = 0; i < 20; i++){
					dp[r][c][i] = inf;
				}
			}
		}
		ANS = inf;
		for(int c = 1; c <= C; c++){
			int t = c == 0 ? 0 : 2*c+1;
			int mask = (0b111111 << (2*(c-1)));
			if(bit & up){
				dp[r][c][bit] = inf;
			}
			else{
				int state = ((bit & mask) >>(2*(c-1))); // 0b??????
				if(isA(r, c)){
					if(exact(state) == 1){
						for(int k = 0; k < 3; k++){
							int pstate = bit & (~mask) + (type(state) << (2*c + k));
								
						}
						
					}
					else {
						dp[r][c][bit] = inf;
					}
				}
				else if(isB(r, c)){

				}
				else{
					if(exact(state) == 0){
						dp[r][c][bit] = min(dp[r][c][bit], dp[r][c-1][bit]);
					}
					else if(exact(state) == 1){
						for(int k = 0; k < 3; k++){
							int pstate = bit & (~mask) + (type(state) << (2*(c-1) + k));
							dp[r][c][bit] = min(dp[r][c][bit], dp[r][c-1][pstate] + mat[i][j]);
						}
					}
					else if(exact(state) == 2){
						int pstate = bit & (~mask);
						dp[r][c][bit] = dp[r][c-1][pstate] + mat[i][j];
					}
					else
						dp[r][c][bit] = inf;
				}
			}
		}
		for(int r = 0; r < R; r++){
			for(int c = 0; c < C; c++){
				for(int bit = 0; bit < (1 << 20); bit++){
							else{

					}

				}
			}
		}


		

		cout << ANS << "\n";
	}
	return 0;
}

