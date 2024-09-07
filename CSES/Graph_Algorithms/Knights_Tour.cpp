#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
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

vector<pii> direc(8);
vector<vector<int>> deg(12,vector<int>(12, 0));
vector<vector<int>> ans(12,vector<int>(12, 0));

const int n = 8;
inline bool valid(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool DFS(int cnt, int x, int y){
	ans[x][y] = cnt;
//	cout << x << " ," << y << endl;

	if(cnt == n*n){
//		cout << "fin!!\n";
		return true;
	}


	vec<pair<int, int>> S;
//	bool impossible = false;
//	bool haszero = false;
	for(int i = 0; i < 8; i++){
		int a = x + direc[i].F; int b = y + direc[i].S;
		if(ans[a][b] == 0){
//			if(haszero && deg[a][b] == 0) impossible = true;
//			if(deg[a][b] == 0) haszero = true;
			S.eb(deg[a][b], i);
		}
	}

//	if(impossible == false){
		sort(al(S));

		for(int k = 0; k < S.size(); k++){
//			if(haszero && val.first > 0) break;
			for(int i = 0; i < 8; i++){
				int a = x + direc[i].F; int b = y + direc[i].S;
				deg[a][b]--;
			}
			if(DFS(cnt+1, x + direc[S[k].second].F, y + direc[S[k].second].S))
				return true;
			for(int i = 0; i < 8; i++){
				int a = x + direc[i].F; int b = y + direc[i].S;
				deg[a][b]++;
			}
		}
//	}

	ans[x][y] = 0;
	return false;
}

int main(){

	direc[0] = make_pair(1, 2);
	direc[1] = make_pair(1, -2);
	direc[2] = make_pair(-1, 2);
	direc[3] = make_pair(-1, -2);
	direc[4] = make_pair(2, 1);
	direc[5] = make_pair(2, -1);
	direc[6] = make_pair(-2, 1);
	direc[7] = make_pair(-2, -1);
//	random_shuffle(al(direc));

	int x, y;
	cin >> y >> x;
	for(int i = 0; i <= 11; i++){
		for(int j = 0; j <= 11; j++){
			if(valid(i-1, j-1)){
				for(int k = 0; k < 8; k++){
					if(valid(i-1 + direc[k].F, j-1+direc[k].S))
						deg[i][j]++; 
				}
				ans[i][j] = 0;
			}
			else
				ans[i][j] = -1;
		}
	}
	bool solved = DFS(1, x + 1, y + 1);
	if(!solved) cout << "shit\n";
	for(int i = 2; i <= n+1; i++){
		for(int j = 2; j <= n+1; j++){
			cout << ans[i][j] << (j == n+1 ? '\n' : ' ');
		}
	}
	return 0;
}

