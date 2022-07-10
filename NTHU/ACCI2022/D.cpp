#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
#define eb emplace_back
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;

// V times DFS O(EV)
vector<int> V[101];
// V[i]記錄了左半邊可以配到右邊的那些點
int match[101]; // A<=B
// match[i] 記錄了右半邊配對到左半邊的哪個點
bool used[101];
vec<bool> isedpt, isstpt;
vector<int> V2[101];
vec<vec<int>> reach;
int n;
bool dfs(int v, vec<int>*V)
{
    for(int e:V[v])
    {
        if( used[e] ) continue;
        used[e] = true;
        if( match[e] == -1 || dfs( match[e], V) )
        {
            match[e] = v;
            return true;               
        }
    }
    return false;
}
int konig(vec<int>*V)
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=1;i<=n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i,V) )
            ans++;
    }

    return ans;
}
int dfs2(int u){
    for(int v: V[u]){
        if(match[v] == u)
            return dfs2(v);
    } 
    //if(match[u] == -1)
//    cout << u << endl;
    return u;
}
void findendpoint()
{
    for (int i = 1; i <= n; i++)
    {
        isedpt[dfs2(i)] = true;
        if(match[i] == -1)
            isstpt[i] = true;
    }
}
const int maxL = 500;
void sht()
{
    REP1(i, n){
        reach[i][i] = 0;
    }
    REP1(k, n){
        REP1(i, n){
            REP1(j, n){
                if(reach[i][j] > reach[i][k] + reach[k][j]){
                    reach[i][j] = reach[i][k] + reach[k][j];
                }
            }
        }
    }
}
int main(){
    int m;
    while(cin >> n >> m){
        if(n == 0 && m == 0)
            break;
        isedpt.clear();
        isstpt.clear();
        isedpt.resize(n + 1, 0);
        isstpt.resize(n + 1, 0);
        reach.clear();
        reach.resize(n + 1, vec<int>(n + 1, maxL));
        REP(i, 101)
        {
            V[i].clear();
            V2[i].clear();
        }
        REP(i, m)
        {
            int u, v;
            cin >> u >> v;
            V[u].eb(v);
            reach[u][v] = 1;
        }
        int nmatch = konig(V);
        findendpoint();
        /*
        REP1(i, n)
        {
            cout << i << ": " << isstpt[i] << ", " << isedpt[i] << endl;
        }
        */

        sht();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++){
                if(i == j)
                    continue;
                if (isedpt[i] && isstpt[j] && reach[i][j] != maxL){
//                    isedpt[i] = isstpt[j] = false;
//                  ++;
                    V2[i].eb(j);
                }
            }
        }
        int ct = konig(V2);

        cout << n - nmatch - ct << endl;
    }

    return 0;
}