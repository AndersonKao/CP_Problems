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
const int MOD = 998244353;
 
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
int T, N, Q;
#define MAXN 100005
vector<int> G[MAXN];
ll val[MAXN];
int parent[MAXN];
ll multe[MAXN];
bool modified[MAXN];
void init(int n){
    for (int i = 0; i <= n; i++)
        G[i].clear();
}
void AddEdge(int from, int to){ 
    // edges.push_back(Edge(from, to));
    // edges.push_back(Edge(to, from)) // 反向弧
    // m = edges.size();
    G[from].push_back(to);
    G[to].push_back(from);
}
void rootTheTree(int index){
    multe[index] = val[index];
    for(auto u: G[index]){
        if(u == parent[index])
            continue;
        parent[u] = index;
        rootTheTree(u);
        multe[index] *= multe[u];
        multe[index] %= MOD;
    }
}
void printall(){
    for (int i = 1; i <= N; i++){
        cout << "pa: " << parent[i] << " ";
        cout << "modi: " << modified[i] << endl;
        cout << multe[i] << endl;
    }
}
void recalculate(int index){
    multe[index] = val[index];
    for(auto u: G[index]){
        if(u == parent[index])
            continue;
        if(modified[u])
            recalculate(u);
        multe[index] *= multe[u];
        multe[index] %= MOD;
    }
    modified[index] = false;
}
int askMul(int u){
    if(modified[u]){
        recalculate(u);
    }
    return multe[u];
}
void renewVal(int index, int v){
    val[index] = v;
    modified[index] = true;
    int iter = parent[index];
    int limit = log(N)/log(2)/2;
    multe[index] = val[index];
    for (int i = 0; i < limit; i++){
        for (auto u : G[index])
        {
            if (u == parent[index])
                continue;
            multe[index] *= multe[u];
            multe[index] %= MOD;
        }
        index = parent[index];
    }
    while(iter >= 1 && modified[iter] == false){
        // cout << iter << " is modified.\n";
        modified[iter] = true;
        iter = parent[iter];
    }
    // cout << "end in " << iter << endl;
}
int main(){
    cin >> N >> Q;
    memset(parent, 0, sizeof(parent));
    memset(modified, 0, sizeof(modified));
    memset(val, 0, sizeof(val));
    memset(multe, 0, sizeof(multe));
    for (int i = 0; i < N; i++){
        cin >> val[i+1];
    }
    int from, to;
    for (int i = 0; i < N - 1; i++){
        cin >> from >> to;
        AddEdge(from, to);
    }
    rootTheTree(1);
    int operation, u, x;
    while(Q--){
        // cout << "-----------\n";
        cin >> operation;
        if(operation == 1){
            cin >> u;
            cout << askMul(u) << endl;
        }else{
            cin >> u >> x;
            renewVal(u, x);
        }
        // printall();
    }

    return 0;
}