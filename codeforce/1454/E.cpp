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
int T, N;
#define MAXN 200005
vector<int> G[MAXN];
ll indeg[MAXN];
ll cnt[MAXN];
bool visited[MAXN];
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        for (int i = 0; i <= N; i++){
            G[i].clear();
        }
        memset(visited, 0, sizeof(visited));
        memset(cnt, 0, sizeof(cnt));
        memset(indeg, 0, sizeof(indeg));
        int a, b;
        REP(i, N){
            cin >> a >> b;
            G[a].eb(b);
            G[b].eb(a);
            indeg[a]++;
            indeg[b]++;
        }
        queue<int> Q;
        REP1(i, N){
            if(indeg[i] == 1){
                Q.push(i);
                // cnt[i] = 1;
                visited[i] = true;
                indeg[i]--;
            }
            cnt[i] = 1;
        }
        int u, v;
        while (Q.size())
        {
            u = Q.front();
            Q.pop();
            for (int i = 0; i < G[u].size(); i++)
            {
                v = G[u][i];
                if(visited[v])
                    continue;
                cnt[v] += cnt[u];
                indeg[v]--;
                if(indeg[v] == 1){
                    Q.emplace(v);
                    visited[v] = true;
                }
            }
        }
        ll ANS = 0;
        for (int i = 1; i <= N; i++){
            if(indeg[i] == 2){
                // cout << i << ": " << cnt[i] << endl;
                ANS += (cnt[i] - 1) * cnt[i] / 2;
                // cnt[i]++;
                ANS += (cnt[i]) * (N - cnt[i]);
            }else
            {
                // cout << i << ": " << cnt[i] << endl;
            }
            
        }
        cout << ANS << endl;
    }
    return 0;
}