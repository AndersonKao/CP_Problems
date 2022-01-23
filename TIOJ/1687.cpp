// AC 2020-09-14 14:51:34
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;
 
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
 
const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;
 
ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
 
template<typename T1, typename T2>
ofstream operator<<(ofstream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }
int N, Q, A, B, s, t, k, lgN;
#define MAXN 100005
// #define TEST
vector<int> G[MAXN];
int D[MAXN];
int P[MAXN][20];
bool visited[MAXN];
void DFS(int u, int p){
    P[u][0] = p;
    for(auto v: G[u]){
        if(visited[v])
            continue;
        visited[v] = true;
        D[v] = D[u] + 1;
        DFS(v, u);
    }
}
int LCA(int u, int v){
    if(D[u] > D[v])
        swap(u, v);
    int s = D[v] - D[u];
    for (int i = 0; i <= lgN; i++){
        if(s & (1 << i)){
            v = P[v][i];
        }
    }
    if(u == v)
        return u;
    for (int i = lgN; i >= 0; --i){
        if(P[v][i] != P[u][i]){
            v = P[v][i];
            u = P[u][i];
        }
    }
    return P[v][0];
}
void computeP(){

    for(int i = 0; i < lgN; i++){
        REP1(x, N){
            if(P[x][i] == -1){
                P[x][i + 1] = -1;
            }else{
                P[x][i + 1] = P[P[x][i]][i];
            }
        }
    }
}
int main(){
    #ifdef TEST
    freopen("in.txt", "r", stdin);
    #endif
    memset(visited, 0, sizeof(visited));
    cin >> N >> Q;
    lgN = log(N) / log(2);

    REP(i, N-1){
        cin >> A >> B;
        G[A].eb(B);
        G[B].eb(A);
    }
    visited[1] = true;
    D[1] = 0;
    DFS(1, -1);
    #ifdef TEST
    REP1(i, N){
        cout << P[i][0] << " depth: " << D[i] << endl;
    }
    #endif
    computeP();

    REP(i, Q){
        cin >> s >> t >> k;
        int lca = LCA(s, t);
        if(k > (D[s] + D[t] - D[lca] * 2)){
            cout << "-1\n";
            continue;
        }
        int ans, dis;
        if(k == D[s] - D[lca]){
            cout << lca << endl;
            continue;
        }else if(k < D[s] - D[lca]){
            ans = s;
            dis = k;
        }else{
            ans = t;
            dis = D[t] + D[s] - 2 * D[lca] - k;
        }
        for (int i = 0; i <= lgN; i++){
            if(dis & (1 << i)){
                ans = P[ans][i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}