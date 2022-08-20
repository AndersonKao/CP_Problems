// just use getL, getR
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define F first
#define S second
using pii = pair<int ,int>;

int H, W, N, Q, M;
vector<vector<int>> table;
vector<vector<int>> preL, preR; /* L for \, R for / */
bool valid(int i, int j){
	if(0 <= i && i <= H+1 && 0 <= j && j <= W+1){
		return true;
	}
	return false;
}
int getR(int i, int j){
	int ans = 0;

	int pi = i, pj = j;
	if(i <= 0 || j >= W+1)
		return 0;
	if(valid(0, j) == false){
		pj = max(0, j);
		pi = i - abs(j - pj);
	}
	else if(valid(i, 0) == false){
		pi = min(H+1, i);
		pj = j + abs(i - pi);
	}
#ifdef DgetR
	printf("getR ask %d, %d\n", i, j);
	printf("pruned %d, %d\n", pi, pj);
#endif
	if(valid(pi, pj) == false)
		return 0;
	ans += preR[pi][pj];
	i -= (M + 1);
	j += (M + 1);
	if(valid(i, j) == false)
		return ans;
	ans -= preR[i][j];
	return ans ;
}
int getL(int i, int j){
	int ans = 0;
	int pi = i, pj = j;
	if(i <= 0 || j <= 0)
		return 0;
	if(valid(0, j) == false){
		pj = min(W+1, j);
		pi = i - abs(j - pj);
	}
	else if(valid(i, 0) == false){
		pi = min(H+1, i);
		pj = j - abs(i - pi);
	}
	if(valid(pi, pj) == false)
		return 0;
	ans += preL[pi][pj];
	i -= (M + 1);
	j -= (M + 1);
	if(valid(i, j) == false)
		return ans;
	ans -= preL[i][j];
	return ans ;
}

int main(){
	int caseN= 1;
	while(cin >> H >> W >> N >> Q){
		if(H == 0 && W == 0)
			break;
		table.clear();
		table.resize(H + 2, vector<int>(W + 2, 0));
		preL.clear(), preR.clear();
		preL.resize(H + 2, vector<int>(W + 2, 0));
		preR.resize(H + 2, vector<int>(W + 2, 0));
		for(int i = 1; i <= N; i++){
			int x, y;	
			cin >> x >> y;
			table[x][y] = 1;
		}
		for(int i = 1; i <= H + 1; i++){
			for(int j = 1; j <= W + 1; j++){
				preL[i][j] = preL[i-1][j-1] + table[i][j];
			}
		}
		for(int i = 1; i <= H + 1; i++){
			for(int j = W; j >= 0; j--){
				preR[i][j] = preR[i-1][j+1] + table[i][j];
			}
		}
#ifdef Dinit
		cout << "table-------------\n";
		for(int i = 0; i <= H + 1; i++){
			for(int j = 0; j <= W + 1; j++){
				cout << setw(3) << table[i][j];
			}
			cout << endl;
		}
		cout << "preL-------------\n";
		for(int i = 0; i <= H + 1; i++){
			for(int j = 0; j <= W + 1; j++){
				cout << setw(3) << preL[i][j];
			}
			cout << endl;
		}
		cout << "preR-------------\n";
		for(int i = 0; i <= H + 1; i++){
			for(int j = 0; j <= W + 1; j++){
				cout << setw(3) << preR[i][j];
			}
			cout << endl;
		}
		cout << "------------------\n";
#endif
		cout<< "Case " << caseN++ << ":\n";
		while(Q--){
			cin >> M;
			if(M == 0){
				bool find = false;
				int i, j;
				for(j = 1; j <= W; j++){	
					for(i = 1; i <= H; i++){	
							if(table[i][j] == 1){find = true;	break;}
					}
					if(find) break;
				}
				printf("%d (%d,%d)\n", (find ? 1 : 0), (find ? i : 1), (find ? j : 1)); 
				continue;
			}
			int curANS = 0;
			for(int i = 1; i <= 1+M; i++){
				curANS += getR(i, 1);
			}
			vector<vector<int>> ANS(H + 2, vector<int>(W + 2, 0));	
			ANS[1][1] = curANS;
			for(int i = 1; i <= H; i++){
				for(int j = 1; j <= W; j++){
					if(j == 1){
						if(i == 1) continue;
						ANS[i][j] = ANS[i-1][j];

						ANS[i][j] -= getR(i-1, j-M);
						ANS[i][j] -= getL(i-1, j+M);
						ANS[i][j] += getL(i+M, j);
						ANS[i][j] += getR(i+M, j);
#ifdef Dcase
						printf("getR(%d, %d): %d\n", i -1, j - M, getR(i-1, j-M));	
						printf("getL(%d, %d): %d\n", i - 1, j + M, getL(i-1, j+M));
						printf("getL(%d, %d): %d\n", i +M, j , getL(i+M, j));
						printf("getR(%d, %d): %d\n", i +M, j , getR(i+M, j));
#endif
						if(valid(i+M, j)){
							ANS[i][j] -= table[i+M][j];
						}
						if(valid(i - 1 - M, j)){
							ANS[i][j] += table[i - 1 - M][j];
						}
#ifdef Dans
						printf("ANS[%d][%d]: %d\n", i, j, (ANS[i][j]));
#endif
					}
					else{
						ANS[i][j] = ANS[i][j-1];
						ANS[i][j] -= getR(i, j-1-M);
						ANS[i][j] -= getL(i + M, j-1);
						ANS[i][j] += getL(i, j+M);
						ANS[i][j] += getR(i + M, j);
#ifdef Dcase
						printf("getR(%d, %d): %d\n", i , j - 1- M, getR(i, j-1-M));	
						printf("getL(%d, %d): %d\n", i +M, j -1, getL(i+M, j-1));
						printf("getL(%d, %d): %d\n", i, j + M, getL(i, j + M));
						printf("getR(%d, %d): %d\n", i +M, j , getR(i+M, j));
#endif
						if(valid(i, j + M)){
							ANS[i][j] -= table[i][j + M];
						}
						if(valid(i, j - 1 - M)){
							ANS[i][j] += table[i][j - 1 - M];
						}
					}
#ifdef Dans
					printf("ANS[%d][%d]: %d\n", i, j, (ANS[i][j]));
#endif
				}
			}
#ifdef Dans
			cout << "M = " << M << endl;
			cout << "ANS -------------\n";
			for(int i = 0; i <= H + 1; i++){
				for(int j = 0; j <= W + 1; j++){
					cout << setw(3) << ANS[i][j];
				}
				cout << endl;
			}
#endif
			curANS = ANS[1][1];
			pii myANS(1, 1);
			REP1(j, W){
				REP1(i, H){
					if(ANS[i][j] > curANS){
						curANS = ANS[i][j];
						myANS.F = i, myANS.S = j;
					}
				}
			}
			printf("%d (%d,%d)\n", curANS, myANS.F, myANS.S); 
		}
	}
	return 0;
}
