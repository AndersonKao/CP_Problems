// AC 2020-09-16 16:16:41
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
#define MAXN 10005
// #define TEST
int N, E;

int main(){
    #ifdef TEST
        freopen("in.txt", "r", stdin);
    #endif
    while(cin >> N >> E){

        if(!N && !E){
            break;
        }
        
        vector<int> G[MAXN];
        int indeg[MAXN];
        int outdeg[MAXN];
        int minimax[MAXN] = {0};
        bool visited[MAXN] = {false};
        int a, b;
        REP(i, E){
            cin >> a >> b;
            G[b].eb(a);
            indeg[a]++;
            outdeg[b]++;
        }
        minimax[N] = 1;
        visited[N] = true;
        queue<int> Q;
        Q.emplace(N);
        while(Q.size()){

            int v = Q.front();
            Q.pop();
            if(minimax[v] == 0){
                minimax[v] = 1;
            }
            #ifdef TEST
                cout << "visited: " << v << endl;
            #endif
            for(auto u: G[v]){
                if(visited[u])
                    continue;
                if(minimax[v] == 1)
                    minimax[u] = 2;
                indeg[u]--;
                if(!indeg[u]){
                    visited[u] = true;
                    Q.emplace(u);
                }
            }
            #ifdef TEST
                REP1(i, N){
                    cout << i << ": ";
                    debug(minimax[i]);
                }
                cout << endl;
                // REP1(i, N){
                //     cout << i << ": ";
                //     debug(visited[i]);
                // }
                // cout << endl;
            #endif
        }
        string gamer1, gamer2;
        cin >> gamer1;
        if(gamer1 == "Mimi")
            gamer2 = "Moumou";
        else
            gamer2 = "Mimi";
        if(minimax[1] == 1){
            cout << gamer1 << endl;
        }else
            cout << gamer2 << endl;
    }
    return 0;
}