#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define eb emplace_back
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

char table[3000][3000];
char curt[3000][3000];
bool inq[3000][3000];
int R, C;
int dir[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};
int counta(int i, int j){
	int ans = 0;
	for(int k = 0; k < 4; k++){
		int ni = i + dir[k][0], nj = j + dir[k][1];
		if(ni >= 0 && ni < R && nj >= 0 && nj < C){
			if(curt[ni][nj] == '^')
				ans++;
		}
	}
	return ans;	
}

int main(){
	int T;
	cin >> T;
	int casen = 1;
	while(T--){
		cin >> R >> C;
		bool hastree = false;
		vector<pii> rocks;
		REP(i, R){
			REP(j, C){
				cin >> table[i][j];
				if(table[i][j] == '^')
					hastree = true;
				if(table[i][j] == '#'){
					rocks.eb(i, j);
				}
			}
		}
		if(hastree && (R == 1 || C == 1)){
			cout << "Case #" << casen++ << ": Impossible\n";
			continue;
		}
		REP(i, R){
			REP(j, C){
				curt[i][j] = table[i][j];
				inq[i][j] = false;
			}
		}
		queue<pii> die;
		for(pii& e: rocks){
			int i = e.F, j = e.S;
			curt[i][j] = '#';
			for(int k = 0; k < 4; k++){
				int ni = i + dir[k][0], nj = j + dir[k][1];
				if(ni >= 0 && ni < R && nj >= 0 && nj < C){
					if(inq[ni][nj] == false && curt[ni][nj] == '^'){
						int live = counta(ni, nj);
						if(live < 2){
							die.emplace(ni, nj);
							inq[ni][nj] = true;
						}
					}
				}
			}
		}
		while(die.size()){
			int i, j;
			tie(i, j) = die.front();
			die.pop();
			if(curt[i][j] != '^')
				continue;
			curt[i][j] = '.';
			inq[i][j] = false;
			for(int k = 0; k < 4; k++){
				int ni = i + dir[k][0], nj = j + dir[k][1];
				if(ni >= 0 && ni < R && nj >= 0 && nj < C){
					if(inq[ni][nj] == false && curt[ni][nj] == '^'){
						int live = counta(ni, nj);
						if(live < 2){
							die.emplace(ni, nj);
							inq[ni][nj] = true;
						}
					}
				}
			}
		}
		bool sol = true;
		REP(i, R){
			REP(j, C){
				if(table[i][j] == '^' && table[i][j] != curt[i][j]){
					sol = false;
				}
			}
		}
		if(sol == false){
			cout << "Case #" << casen++ << ": Impossible\n";
		}
		else{
			cout << "Case #" << casen++ << ": Possible\n";
			REP(i, R){
				REP(j, C){
					cout << curt[i][j];
				}
				cout << endl;
			}
		}
	}
	return 0;
}

