#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << x.first << ", " << x.second << endl;
template<typename T>
using vec = vector<T>;
using ll = long long;
using pii = pair<int, int>;
int h1, w1, h2, w2;
vector<vector<int>> t1, t2;
vector<bool> Rs,Cs;
bool sol = false;
void DFS2(int c){
	if(c == w1){
		int rc = 0, cc = 0;
		for(int i = 0; i < h1; i++)
			if(Rs[i])
				rc++;
		for(int j = 0; j < w1; j++)
			if(Cs[j])
				cc++;
		if(rc != t2.size() || cc != t2[0].size())
			return;
		int i2 = 0, j2 = 0;
		for(int i = 0; i < h1; i++){
			if(Rs[i] == false){
				continue;
			}
			j2 = 0;
			for(int j = 0; j < w1; j++){
				if(Cs[j] == false){
					continue;
				}
				if(t1[i][j] != t2[i2][j2]){
					return;	
				}
				j2++;
			}
			i2++;
		}
		sol = true;
		return;
	}

	Cs[c] = false;
	DFS2(c+1);
	if(sol) return;
	Cs[c] = true;
	DFS2(c+1);
}
void DFS(int r){
	if(r == h1){
		DFS2(0);
		return;
	}
	Rs[r] = false;
	DFS(r+1);
	if(sol)
		return;
	Rs[r] = true;
	DFS(r+1);
}
int main(){
	cin >> h1 >> w1;
	t1.resize(h1, vec<int>(w1));
	Rs.resize(h1, true);
	Cs.resize(w1, true);
	REP(i, h1){
		REP(j, w1){
			cin >> t1[i][j];
		}
	}
	cin >> h2 >> w2;
	t2.resize(h2, vec<int>(w2));
	REP(i, h2){
		REP(j, w2){
			cin >> t2[i][j];
		}
	}
	DFS(0);
	cout << (sol ? "Yes" : "No") << endl;


	return 0;
}
