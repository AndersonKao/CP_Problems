#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;
vector<char> hier = {
'W', 'A', 'K', 'J', 'S', 'D'
};
using pii = pair<int, int>;
vector<vector<int>> visited;
vector<vector<char>> table;
vector<vector<int>> belong;

int H, W;
int counter = 0;
int wcnt = 0;
vector<pii> direc = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};
void DFS(int r, int c, int type, int& touch){
	visited[r][c] = 1;
	if(type == 1){
		belong[r][c] = counter;
	}
	for(int i = 0; i < 4; i++){
		int nr = r + direc[i].first, nc = c + direc[i].second;
		if(nr < 0 || nr >= H || nc < 0 || nc >= W){
			if(type == 0){
				touch = -2;
			}
			continue;
		}
		if(visited[nr][nc]){
			if(type == 0 && table[nr][nc] == '1'){
				if(touch == -1)
					touch = belong[nr][nc];
				else if(touch != belong[nr][nc])
					touch = -2;
			}
			continue;
		}
		if(type == 0 && table[nr][nc] == '0'){
				DFS(nr, nc, 0, touch);
		}
		else if(type == 1 && table[nr][nc] == '1'){
				DFS(nr, nc, 1, touch);	
		}
	}

}

int main(){
	int caseN= 1;
	while(cin >> H >> W){
		if(H == 0 && W == 0)
			break;
		W*=4;
		string str;
		visited.clear();
		visited.resize(H, vector<int>(W, 0));
		table.clear();
		table.resize(H, vector<char>(W, '0'));
		belong.clear();
		belong.resize(H, vector<int>(W, 0));
		for(int i = 0 ; i < H; i++){
			cin >> str;
			for(int j = 0; j < str.length(); j++){
				int mask = 0;
				if(str[j] >= 'a' && str[j] <= 'f'){
					mask = 10 + (str[j] - 'a');
				}
				else
					mask = str[j] - '0';
				for(int k = 3; k >= 0; k--){
		//			debug(j*4 + (3-k));
					if(mask & (1 << k)){
						table[i][j*4 + (3 - k)] = '1';
					}
				}
			}
		}
		/*
		for(int i = 0 ; i < H; i++){
			for(int j = 0; j < W; j++){
				cout << table[i][j];
			}
			cout << endl;
		}
		*/
		counter=0;
		vector<int> dier;
		for(int r = 0; r < H; r++){
			for(int c = 0; c < W; c++){
				if(visited[r][c] == 0){
					if(table[r][c] == '1'){
		//				cout << "new \n";
//						debug(r);
//						debug(c);
						counter++;
						dier.resize(counter, 0);
						int touch = -1;
						DFS(r, c, 1, touch);
					}
					else{
						int touch = -1;
						DFS(r, c, 0, touch);
						if(touch != -2){
							dier[touch-1]++;
						}
					}
				}
			}
		}
		sort(dier.begin(), dier.end(), [](int a, int b){
			return hier[a] < hier[b];
		});
		/*
		for(int i = 0; i < dier.size(); i++){
			debug(dier[i]);
		}
		*/
		cout << "Case " << caseN++ << ": ";
		for(int i = 0; i < dier.size(); i++){
			cout << hier[dier[i]];
		}
		cout << endl;
	}
	return 0;
}
