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
const int maxn = 300;
const int inf = 0x3f3f3f3f;
int H, W, N, h, w;
struct mydata{
	int L = inf, R = -1, U = inf, D = -1;	
};
mydata pos[301];
int mat[300][300];

int main(){
	yccc;		
	cin >> H >> W >> N >> h>> w;

	for(int i = 0; i < H ;i++){
		for(int j = 0; j < W; j++){
			int x;
			cin >> x;
			pos[x].L = min(pos[x].L, j);
			pos[x].R = max(pos[x].R, j);
			pos[x].U = min(pos[x].U, i);
			pos[x].D = max(pos[x].D, i);
		}
	}

	for(int i = 0; i + h <= H; i++){
		for(int j = 0; j + w <= W; j++){
			int cnt = 0;
			for(int x = 1; x <= N; x++){
				if(pos[x].L == inf)
					continue;
				if(pos[x].L < j || pos[x].R >= j + w || pos[x].U < i || pos[x].D >= i + h){
					cnt++;
				}
			}
			cout << cnt << (j + w == W ? "\n" : " ");
		}
	}

	return 0;
}

