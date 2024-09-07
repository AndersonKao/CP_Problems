
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second
char grid[100][100];

int main() {
	yccc;
	int H, W;
	cin >> H >> W;
	int x, y;
	cin >> x >> y;
	for(int i = 1; i <= W; i++){
		grid[0][i] = grid[H+1][i] = '#';
	}
	for(int i = 1; i <= H; i++){
		grid[i][0] = grid[i][W+1] = '#';
	}
	for(int i = 1; i <= H; i++){
		for(int j = 1; j <= W; j++){
			cin >> grid[i][j];
		}
	}
	string step;
	cin >> step;
	for(size_t i = 0; i < step.length(); i++){
		if(step[i] == 'U' && grid[x-1][y] == '.'){
			x--;
		}
		if(step[i] == 'D' && grid[x+1][y] == '.'){
			x++;
		}
		if(step[i] == 'L' && grid[x][y-1] == '.'){
			y--;;
		}
		if(step[i] == 'R' && grid[x][y+1] == '.'){
			y++;
		}
	}
	cout << x << " " << y;
	return 0;
}
