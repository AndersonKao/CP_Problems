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
char str[50];

int visited[9][9] = {false};
int len;
int ans = 0;
int dir[4][2] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};
inline int toid(char ch){
	if(ch == 'D'){
		return 1;
	}
	else if(ch == 'U'){
		return 3;	
	}
	else if(ch == 'L'){
		return 2;	
	}
	return 0;	
}
void DFS(int x, int y, int lasti, int idx){
	if(idx == len){
		if(x == 1 && y == 7){
			ans++;
		}
		return;
	}
	if(x == 1 && y == 7){
		return;
	}
	if(x == 1 || x == 7){
		if(!visited[x][y-1] && !visited[x][y+1]){
			return;
		}
	}
	if(y == 1 || y == 7){
		if(!visited[x-1][y] && !visited[x+1][y]){
			return;
		}
	}
	int px = x + dir[lasti][0], py = y + dir[lasti][1];
	if(visited[px][py]){
		int x1 = x + dir[(lasti ^ 1)][0], y1 = y + dir[(lasti ^ 1)][1];
		int x2 = x + dir[(lasti ^ 3)][0], y2 = y + dir[(lasti ^ 3)][1];
		if(!visited[x1][y1] && !visited[x2][y2]){
			return;
		}
	}

	visited[x][y] = true;
	if(str[idx] == '?'){
		for(int i = 0; i < 4; i++){
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if(visited[nx][ny]) continue;
			DFS(nx, ny, i, idx+1);
		}
	}
	else{
		int nx = x + dir[toid(str[idx])][0], ny = y + dir[toid(str[idx])][1];
		if(visited[nx][ny] == false){
			DFS(nx, ny, toid(str[idx]), idx+1);
		}
	}
	visited[x][y] = false;
}
int main(){
	cin >> str;
	len = strlen(str);
	for(int i = 0; i < 9; i++){
		memset(visited[i], false, sizeof(visited[i]));
	}
	for(int i = 0; i < 9; i++){
		visited[0][i] = visited[8][i] = true;
		visited[i][0] = visited[i][8] = true;
	}
	DFS(1, 1, 0, 0);

	cout << ans << endl;
	return 0;
}

