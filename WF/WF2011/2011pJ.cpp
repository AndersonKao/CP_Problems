#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define depii(x) cout << "(" << x.first << ", " << x.second << ")" << endl;
#define debug(x) cout << #x << ": " << x << endl;
#define eb emplace_back
using pii = pair<int, int>;
struct py{
	int cube;
	int base;
	int type; // 0 for high, 1 for low
	py(){}
	py(int c, int b, int t):cube(c), base(b), type(t){};
	friend	ostream& operator<<(ostream& os, const py& rhs);
};
auto pycmp = [](const py& lhs, const py&rhs){
	return lhs.cube < rhs.cube;
};
ostream& operator<<(ostream& os, const py& rhs){
	os << rhs.base;
	if(rhs.type == 0){
		return (os << "H");
	}	
		return (os << "L");
}
vector<py> pyramids;

vector<vector<int>> dp;
vector<vector<int>> pa;
const int bound = 1000000;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int h = 2;
	int cube;
	do{
		cube = (h * (h+1) * (2*h+1))/ 6;
		pyramids.eb(h * (h+1) * (2*h+1) / 6, h, 0);
//		debug(cube);
		h++;
	}while(cube < 1000000);
	int b = 3;
	do{
		if(b == 3)
			cube = 10;
		else if(b == 4)
			cube = 20;
		else
			cube = pyramids[pyramids.size()-2].cube + b * b;
		pyramids.eb(cube, b, 1);
//		debug(cube);	
		b++;
	}while(cube < 1000000);
	sort(al(pyramids), pycmp);
	/*
	for(int i = 0; i < 150; i++){
		int h = i + 2;
		pyramids[i].cube = (h * (h+1) * (2*h+1)) / 6;
		pyramids[i].base= h;
		pyramids[i].type = 0;
	}
	for(int i = 150; i < 350; i++){
		int b = i - 147;	
		if(b == 3)
			pyramids[i].cube = 10;
		else if(b == 4)
			pyramids[i].cube = 20;
		else
			pyramids[i].cube = pyramids[i-2].cube + b * b;
		pyramids[i].base = b;
		if(i == 349)
			cout << pyramids[i].cube << endl;
		pyramids[i].type = 1;
	}
	*/
	dp.resize(pyramids.size(),vector<int>(1000001, -1));
	pa.resize(pyramids.size(),vector<int>(1000001, 0));
	for(int i = 0; i < (int)pyramids.size(); i++)
		dp[i][0] = 0;
	
	dp[0][pyramids[0].cube] = 1;
	pa[0][pyramids[0].cube] = 1;
	for(int i = 1; i < (int)dp.size(); i++){
		for(int j = 0; j <= 1000000; j++){
			int pj = j - pyramids[i].cube;	
			if(dp[i-1][j] != -1){
				dp[i][j] = dp[i-1][j];
				pa[i][j] = 0;
			}
			if(pj >= 0 && dp[i-1][pj] != -1){
				if(dp[i][j] == -1 || (dp[i-1][pj] + 1 <= dp[i][j])){
					dp[i][j] = dp[i-1][pj]+1;
					pa[i][j] = 1;
				}
			}
		}
	}
	/*
	for(int i = 0; i < 4; i++){
		debug(i);
		for(int j = 0; j <= 30; j++){
			debug(j);
			debug(dp[i][j]);
			debug(pa[i][j]);
		}
	}
	*/
//	cout << "stat" << endl;
	int n;
	int caseN = 1;
	while(cin >> n){
		if(n ==  0) break;
		cout << "Case " << caseN++ << ":";
		if(dp[dp.size()-1][n] == -1){
			cout << " impossible\n";
			continue;
		}
		pii cur(dp.size()-1, n);
		while(cur.F >= 0){
//			depii(cur);
			int used = pa[cur.F][cur.S];
			if(used == 1){
				cout << " " << pyramids[cur.F];
				cur = pii(cur.F-1, cur.S - pyramids[cur.F].cube);
			}
			else	
				cur = pii(cur.F-1, cur.S);
		}
		cout << endl;
	}

	return 0;
}
