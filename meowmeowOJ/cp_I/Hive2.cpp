// brute-force and pruning approach
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define ep emplace
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int inf = 0x3f3f3f3f;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int R, C;
p<int> Ast, Aed, Bst, Bed;
int mat[12][7];
int vis[12][7];
int dir[2][6][2] = {
	{
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, 0},
		{1, 1}
	},
	{
		{-1, -1},
		{-1, 0},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0}
	}
};
istream& operator>>(istream& is, p<int> &e){
	return (is >> e.F >> e.S);
}
ostream& operator<<(ostream& os, p<int> &e){
	return (os << " (" << e.F << ", " << e.S << ") ");
}
p<int> operator+(p<int>& a, p<int> &b){
	return p<int>(a.F + b.F, a.S + b.S);
}
using node = tuple<int, int, int>; // dis, r, c
int dijkstra(){
	// dijkstra for Bst to Bed.
	priority_queue<node, vec<node>, greater<node>> pq;
	vec<vec<int>> sdis(R+1, vec<int>(C+1, inf));
	sdis[Bst.F][Bst.S] = mat[Bst.F][Bst.S];
	pq.ep(sdis[Bst.F][Bst.S], Bst.F, Bst.S);
	int r, c, dis;
	while(pq.size()){
		tie(dis, r, c) = pq.top();
		pq.pop();
		if(dis != sdis[r][c])
			continue;
		int did = r & 1;
		for(int i = 0; i < 6; i++){
			int nr = r + dir[did][i][0], nc = c + dir[did][i][1];
			if(vis[nr][nc]) continue;
			if(sdis[nr][nc] > dis + mat[nr][nc]){
				pq.ep((sdis[nr][nc] = dis + mat[nr][nc]), nr, nc);
			}
		}
	}
	return sdis[Bed.F][Bed.S];
}
bool hasnei(int r, int c, int pr, int pc){
	int did = r & 1;	
	for(int i = 0; i < 6; i++){
		int nr = r + dir[did][i][0], nc = c + dir[did][i][1];
		if(nr <= 0 || nr > R || nc <= 0 || nc > C || (nr == pr && nc == pc))
			continue;
		if(vis[nr][nc]) return true;
	}
	return false;
}
bool isB(int r, int c){
	return (r == Bst.F && c == Bst.S)|| (r == Bed.F && c == Bed.S);
}
int reachans = 0;
int Aans = inf;
void dfs(int r, int c, int cost){
	vis[r][c] = 1;
	cost += mat[r][c];
//	cout << "visiting " << r << " , " << c << "\n";
	if(r == Aed.F && c == Aed.S){
		cost += dijkstra();
		vis[r][c] = 0;
		Aans = min(Aans, cost);
		reachans++;
		return;
	}
	int did = r & 1;	
	for(int i = 0; i < 6; i++){
		int nr = r + dir[did][i][0], nc = c + dir[did][i][1];
//		cout << "try " << nr << " " << nc << "\n";
		if(vis[nr][nc] || isB(nr, nc)){
//			cout << "vis or isB\n";
			continue;
		}
		else if(hasnei(nr, nc, r, c)){
//			cout << "hasnei\n";
			continue;
		}
		dfs(nr, nc, cost);	
	}
	vis[r][c] = 0;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		Aans = inf, reachans = 0;
		cin >> R >> C;	
		cin >> Ast >> Aed >> Bst >> Bed;

		REP1(i, R){
			REP1(j, C){
				cin >> mat[i][j];
			}
		}
		REP1(i, R)
			REP1(j, C)
				vis[i][j] = 0;
		for(int i = 0; i < 12; i++){
			vis[i][0] = vis[i][C+1] = 1;
		}
		for(int i = 0; i < 7; i++){
			vis[0][i] = vis[R+1][i] = 1;
		}
		dfs(Ast.F, Ast.S, 0);	
		debug(reachans);
		cout << (Aans == inf ? -1 : Aans) << "\n";
	}
	return 0;
}

