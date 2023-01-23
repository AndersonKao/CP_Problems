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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 1000;
int n;
char table[maxn+1][maxn+1];
int bit[maxn+1][maxn+1];
int lowbit(int x){
	return (x & (~x + 1));
}
void modify(int y, int x, int val){
	int iy = y, ix = x;
	while(iy <= n){
		ix = x;
		while(ix <= n){
			bit[iy][ix] += val;
			ix += (ix & (~ix + 1));
		}
		iy += (iy & (~iy + 1));
	}
}
int query2(int y, int x){
	int ans = 0;
	int iy = y;
	while(iy > 0){
		int ix = x;
		while(ix > 0){
			ans += bit[iy][ix];
			ix -= lowbit(ix);
		}
		iy -= lowbit(iy);
	}
	return ans;
}
int query(int y, int x, int y2, int x2){
	return query2(y2, x2) - query2(y2, x-1) - query2(y-1, x2) + query2(y-1, x-1);
}
int main(){
//	yccc;
	cin >> n;
	int q; cin >> q;
	REP1(i, n){
		REP1(j, n){
			cin >> table[i][j];
			if(table[i][j] == '*')
				modify(i, j, 1);
		}
	}	
	REP(i, q){
		int op; cin >> op;
		int y, x; cin >> y >> x;
		if ( op == 1 ){
			if(table[y][x] == '.'){
				modify(y, x, 1);
			}
			else{
				modify(y, x, -1);
			}
			table[y][x] = table[y][x] == '.' ? '*' : '.';
		}
		else{
			int y2, x2;
			cin >> y2 >> x2;
			cout << query(y, x, y2, x2) << endl;
		}
	}
	return 0;
}

