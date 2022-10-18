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
const int maxn = 250;
// time complexity: O(EV), V times DFS
// G[i]記錄了左半邊可以配到右邊的那些點
/* 
1    1
2    2
3    3
4    4
5
.
.
*/
// match[i] 記錄了右半邊配對到左半邊的哪個點
vec<int> G[maxn];
int match[maxn]; // A <=B
bool used[maxn];
bool dfs(int v)
{
    for(int e:G[v])
    {
        if( used[e] ) continue;
        used[e] = true;
        if( match[e] == -1 || dfs( match[e] ) )
        {
            match[e] = v;
            return true;               
        }
    }
    return false;
}
int konig(int n) // num of vertices of left side
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=0;i<n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i) )
            ans++;
    }

    return ans;
}
void addedge(int u, int v){ // left side, right side
    G[u].eb(v);
}
vec<p<int>> Red, Blue;
double fcmp(double a, double b, double eps = 1e-8){
	if(abs(a-b) < eps)
		return 0;
	return a-b;
}
double getdis(p<int>& a, p<int>&b){
	ll xd = a.F - b.F, yd = a.S - b.S;
	return sqrt(xd * xd + yd * yd);
}
int main(){
	int N, R, B;
	cin >> N >> B >> R;
	Red.resize(R);
	Blue.resize(B);
	for(p<int>&e: Blue){
		cin >> e.F >> e.S;
	}
	for(p<int>&e: Red){
		cin >> e.F >> e.S;
	}
	double l = 0.0, r = sqrt(2000.0*2000.0*2.1);
	while(fcmp(l, r) != 0.0){
//		cout << "---------\n";
		double m = (l+r)/2.0;
		for(int i = 0; i < B+R; i++){
			G[i].clear();
		}
		for(int i = 0; i < B; i++){
			for(int j = 0; j < R; j++){
				if(fcmp(getdis(Blue[i], Red[j]), m) <= 0.0){
//					cout << i << " and " << j << " connected\n";
					G[i].eb(j);
				}
			}
		}
		int indep_set = B + R - konig(B+R);
//		debug(indep_set);
//		debug(l);
//		debug(r);
		if(indep_set < N){
			r = m;
		}
		else{
			l = m;
		}
	}
	cout << fixed << setprecision(8) << r;
	return 0;
}

