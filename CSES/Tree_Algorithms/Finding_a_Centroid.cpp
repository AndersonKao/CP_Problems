#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
vector<int> G[200000];
int N;
int centroid;
int centroid_subtree_sz;
int tree_centroid(int u, int pa)
{
    int sz = 1; // tree size of u.
    int maxsub = 0; // max subtree size of u

    for(int v:G[u])
    {
        if (v==pa)continue;
        int sub = tree_centroid(v, u);
        maxsub = max(maxsub, sub);
        sz += sub;
    }
    maxsub = max(maxsub, N-sz);

    if (maxsub <= N/2)
    {
        centroid = u;
        centroid_subtree_sz = maxsub;
    }
    return sz;
}

int main(){
	cin >> N;
	REP(i, N-1){
		int a, b;
		cin >> a >> b;
		a--,b--;
		G[a].eb(b);
		G[b].eb(a);
	}
	tree_centroid(0, -1);
	cout << centroid + 1 << endl;
	return 0;
}

