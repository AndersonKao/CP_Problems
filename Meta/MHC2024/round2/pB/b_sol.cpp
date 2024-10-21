#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int Rn = 6, Cn = 7;
char grid[10][10];
char cpgrid[10][10];
int offset[4][2] = {
	{1, -1},
	{1, 0},
	{1, 1},
	{0, 1}
};
bool valid(int x, int y){
	return x > 0 && y > 0 && x <= Rn && y <= Cn;
}
int check(int* bound){ // status: 0 --> no one has line, 1 --> C win, 2 --> F win, 3 --> both have line
	bool Cfound = false, Ffound = false;
	for(int c = 1; c <= Cn; c++){
		for(int r = 1; r <= bound[c]; r++){
			for(int k = 0; k <= 3; k++){
				bool same = true;
				for(int step = 0; step <= 3; step++){
					if(valid(r + offset[k][0]*step, c + offset[k][1] * step) == false || (r + offset[k][0]*step > bound[c + offset[k][1] * step])){
						same = false;
						break;
					}
					if(grid[r][c] != grid[r + offset[k][0]*step][c + offset[k][1] * step]){
						same = false;
						break;
					}
				}
				if(same){
					if(grid[r][c] == 'C'){
						Cfound = true;
					}
					if(grid[r][c] == 'F'){
						Ffound = true;
					}
				}
			}
		}
	}
	if(Cfound && Ffound){
		return 3;
	}
	if(!Cfound && Ffound){
		return 2;
	}
	if(Cfound && !Ffound){
		return 1;
	}
	if(!Cfound && !Ffound){
		return 0;
	}
	return false;
}
int nid(int *bound){
	int base = 1;
	int id = 0;
	for(int i = 1; i <= Cn; i++){
		id += base * bound[i];
		base *= 7;
	}
	return id;
}
void debug_print(int result, int *status){

	cout << "result: " << (result == 1 ? 'C' : 'F') << endl;
	for(int r = Rn; r >= 0; r--){
		for(int c = 1; c <= Cn; c++){
			if(r > status[c]){
				cout << ' ';
			}
			else{
				cout << grid[r][c];
			}
		}
		cout << endl;
	}

}
const int maxnode = 1000000;
int visited[maxnode];
int toend[maxnode];
bool FpC, CpF;

void dfs(int * status, char round){
	int id = nid(status);
	if(visited[id])
		return;	
	visited[id] = true;
	bool allmax = true;
	for(int i = 1; i <= 7; i++){
		if(status[i] != Rn){
			allmax = false;
			break;
		}
	}
	toend[id] = allmax;
	int nxt[9];
	memcpy(nxt, status, sizeof(int) * 9);
	for(int i = 1; i <= 7; i++){
		if(nxt[i] == Rn) continue;
		if(grid[nxt[i]+1][i] != round) continue;
		nxt[i]++;
		dfs(nxt, round == 'C' ? 'F' : 'C');
		toend[id] = toend[id] || toend[nid(nxt)];
		nxt[i]--;
	}
	int result = check(status);
	if(result != 0 && toend[id]){
		if(result == 1){
			CpF = true;
		}
		else if(result == 2){
			FpC = true;
		}
	}
}

void solve(int ca){
	char ans;
	FpC = false, CpF = false;
	memset(visited, 0, sizeof(int) * maxnode);
	memset(toend, 0, sizeof(int) * maxnode);
	for(int i = Rn; i >= 1; i--){
		for(int j = 1; j <= Cn; j++){
			cin >> grid[i][j];
		}
	}
	int status[9];	
	memset(status, 0, sizeof(int) * 9);
	dfs(status, 'C');

	//debug(FpC);
	//debug(CpF);

	if(FpC && CpF){
		ans = '?';
	}
	else if(FpC == false && CpF == false){
		ans = '0';
	}
	else if(FpC && CpF == false){
		ans = 'F';
	}
	else if(FpC == false && CpF){
		ans = 'C';
	}
	cout << "Case #" << ca << ": " << ans << endl;
}

int main(){
	//yccc;		
	int T;
	cin >> T;
	for(int ca = 1; ca <= T; ca++){
		solve(ca);
	}
	return 0;
}

