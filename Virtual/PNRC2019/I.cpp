#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);
const int maxn = 500;
vec<int> rG[maxn];
vec<int> G[maxn];
vec<int> vis;
vec<int> types;
void genG(int u, int type)
{
    vis[u] = true;
    types[u] = type;
    for(int v : rG[u]){
        if(vis[v])
            continue;
        genG(v, (type ^ 1));
    }
}

int match[maxn];
bool used[maxn];
bool dfs(int v){
    for(int e: G[v]){
        if( used[e] )
            continue;
        used[e] = true;
        if(match[e] == -1 || dfs(match[e])){
            match[e] = v;
            return true;
        }
    }
    return false;
}

int konig(int n){
    memset(match, - 1, sizeof(match));

    int ans = 0;
    for(int i = 0;i < n;i ++){
        memset(used, 0, sizeof(used));
        if(dfs(i))
            ans++;
    }
    return ans;
}

int main()
{
    yccc;
    int n;
    cin >> n;
    vec<string> strs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> strs[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            int diff = 0;
            int di = -1, dj = -1;
            for (int k = 0; k < strs[i].length(); k++)
            {
                if(strs[i][k] != strs[j][k]){
                    diff++;
                    if(diff == 1){
                        di = k;
                    }
                    else if(diff == 2){
                        dj = k;
                    }
                }
            }
            if(diff == 2 && strs[i][di] == strs[j][dj] && strs[i][dj] == strs[j][di]){
                rG[i].eb(j);
                rG[j].eb(i);
            }
        }
    }
    types.resize(n, -1);
    vis.resize(n, false);
    for (int u = 0; u < n; u++){
        if(vis[u] == false)
            genG(u, 0);
    }

    int Anum = 0, Bnum = 0;
    vec<int> id(n);

    for (int u = 0; u < n; u++){
        if(types[u] == 0){
            id[u] = Anum++;
        }
        else{
            id[u] = Bnum++;
        }
    }
    for(int u = 0; u < n ;u++){
        if(types[u] == 0){
            for(int v: rG[u]){
                G[id[u]].eb(id[v]);
            }
        }
    }

    int match = konig(Anum);

    cout << n - match << endl;
}
