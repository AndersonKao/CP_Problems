#include<bits/stdc++.h>
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
int mat[9][9];
void printmat(){
		REP(i, 9){
			if(i % 3 == 0)
				cout << "------------\n";
			REP(j, 9){
				if(j % 3 == 0){
					cout << '|';
				}
				cout << mat[i][j];
			}
			cout << "|\n";
		}
		cout << "------------\n\n";
}
int contain[3][3][10];
int rowcon[9][10];
int colcon[9][10];

bool dfs(int r, int c){
	if(r >= 9){
		return true;
	}
	if(mat[r][c] == 0){
		int sr = r/3, sc = c/3;
		for(int i = 1; i <= 9; i++){
			if(rowcon[r][i] || colcon[c][i] || contain[sr][sc][i])
				continue;
			rowcon[r][i] = colcon[c][i] = contain[sr][sc][i] = 1;
			mat[r][c] = i;	
			if(c == 8){
				if(dfs(r+1, 0))
					return true;
			}
			else{
				if(dfs(r, c+1)){
					return true;
				}
			}
			mat[r][c] = 0;
			rowcon[r][i] = colcon[c][i] = contain[sr][sc][i] = 0;
		}
	}
	else{
		if(c == 8)
			return dfs(r+1, 0);
		else
			return dfs(r, c+1);
	}
	return false;
}
int main(){
	string str;
	while(cin >> str){
		if(str == "end") break;
		int idx = 0;
		REP(i, 9){
			REP(j, 9){
				mat[i][j] = (str[idx] == '.' ? 0 : str[idx] - '0');
				idx++;
			}
		}
		memset(contain, 0, sizeof(contain));
		memset(rowcon, 0, sizeof(rowcon));
		memset(colcon, 0, sizeof(colcon));
		bool sol = true;
		REP(r, 9){
			REP(c, 9){
				int sr = r/3, sc = c/3;
				if(mat[r][c] == 0) continue;
				int i = mat[r][c];	
				if(rowcon[r][i] || colcon[c][i] || contain[sr][sc][i]){
					sol = false;
				}
				contain[sr][sc][mat[r][c]] = 1;
				rowcon[r][mat[r][c]] = 1;
				colcon[c][mat[r][c]] = 1;
			}
		}
		if(sol && dfs(0, 0)){
			REP(i, 9){
				REP(j, 9){
					cout << mat[i][j];
				}
			}
			cout << "\n";
		}
		else
			cout << "No solution.\n";
	}
	return 0;
}

