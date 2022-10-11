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
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int main(){
	int N, M;
	cin >> N >> M;	
	vec<vec<int>> table(N+2, vec<int>(N+2, -1));
	vec<pair<int, int>> dir;
	for(int i = 0; i <= 399; i++){
		for(int j = 0; j <= 399; j++){
			if(i * i + j * j == M){
				dir.eb(i, j);
				dir.eb(-i, -j);
				dir.eb(i, -j);
				dir.eb(-i, j);
			}
		}
	}
	queue<p<int>> mq;
	mq.emplace(1, 1);
	table[1][1] = 0;
	while(mq.size()){
		p<int> cur = mq.front();
		mq.pop();
		for(p<int>& e: dir){
			int nr = cur.F + e.F, nc = cur.S + e.S;
			if(nr >= 1 && nr <= N && nc >= 1 && nc <= N){
				if(table[nr][nc] == -1){
					table[nr][nc] = table[cur.F][cur.S] + 1;
					mq.emplace(nr, nc);
				}
			}
		}
	}
	REP1(i, N){
		REP1(j, N){
			cout << table[i][j] << (j == N ? "\n" : " ");
		}
	}
	return 0;
}

