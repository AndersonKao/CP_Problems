
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << x.first << ", " << x.second << endl;
using ll = long long;
using pii = pair<int, int>;
int main(){
	int r, c;
	bool ans = false;
	cin >> r >> c;
	vector<vector<int>> table(17, vector<int>(17, 0));
	int L = 1, R = 15;
	for(int i = 1; i <= 8; i++){
		table[i][L] = table[i][R] = 1;
		for(int j = 1;j <= L; j+= 2){
			table[i][j] = 1;
		}
		for(int j = 15;j >= R; j-= 2){
			table[i][j] = 1;
		}
		if(i & 1){
			for(int j = L; j <= R; j++){
				table[i][j] = 1;
			}
		}
		else{
			L+=2, R-=2;
		}
	}
	L = 7, R = 9;
	for(int i = 9; i <= 15; i++){
		table[i][L] = table[i][R] = 1;
		for(int j = 1;j <= L; j+= 2){
			table[i][j] = 1;
		}
		for(int j = 15;j >= R; j-= 2){
			table[i][j] = 1;
		}
		if(i & 1){
			for(int j = L; j <= R; j++){
				table[i][j] = 1;
			}
			L-=2, R+=2;
		}
		else{
		}
	}
	/*
	REP1(i, 15){
		REP1(j, 15){
			cout << table[i][j];
		}
		cout << endl;
	}
	*/
	if(table[r][c] == 1){
		cout << "black\n";
	}
	else
		cout << "white\n";
	return 0;
}
