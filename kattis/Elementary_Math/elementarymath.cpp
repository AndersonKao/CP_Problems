#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <set>
#include <cstring>
#include <map>
#include <queue>
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
 
int n, a, b;
vec<pii> add_ele;
set<ll> used_int_set;
map<ll, int> used_int_arr;
int opera[2505][3];
// sorry I think this problem can't use flow on bipartite graph

bool used[101];
int End;
vec<int> V[20000];
vector<tuple<int, int>> E;
void addEdge(int x, int y,int c)
{
    V[x].emplace_back( E.size() );
    E.emplace_back(y,c);
    V[y].emplace_back( E.size() );
    E.emplace_back(x,0);
}
int dfs(int v, int f)
{
    if( v==End ) return f;
    used[v] = true;
    int e,w;
    for( int eid : V[v] )
    {
        tie(e,w) = E[eid];
        if( used[e] || w==0 ) continue;
        
        w = dfs(e, min(w,f));
        if( w>0 )
        {
            // 更新流量
            get<1>(E[eid  ]) -= w;
            get<1>(E[eid^1]) += w;
            return w;
        }
    }
    return 0;// Fail!
}
int ffa(int s,int e)
{
    int ans = 0, f;
    End = e;
    while(true)
    {
        memset(used, 0, sizeof(used));
        f = dfs(s, INF);
        if( f<=0 ) break;
        ans += f;
    }
    return ans;
}
void pre_compute_ANSset(){
    for (int i = 0; i < n; i++){
        
    }
}
#define TEST
int main(){
    #ifdef TEST
        freopen("in.txt", "r", stdin);
    #endif
    cin >> n;
    REP1(i, n){
        cin >> a >> b;
        add_ele.eb(a, b);
        opera[i][0] = E.size();
        if (used_int_set.find(a * b) == used_int_set.end()){
            addEdge(i, used_int_arr.size() + n + 1, 1);
            used_int_set.emplace(a * b);
            used_int_arr.emplace(a * b, used_int_arr.size() + n + 1);
        }else{
            addEdge(i, used_int_arr[a * b], 1);
        }
        opera[i][1] = E.size();
        if (used_int_set.find(a + b) == used_int_set.end()){
            addEdge(i, used_int_arr.size() + n + 1, 1);
            used_int_set.find(a + b);
            used_int_arr.emplace(a + b, used_int_arr.size() + n + 1);
        }else{
            addEdge(i, used_int_arr[a + b], 1);
        }
        opera[i][2] = E.size();
        if (used_int_set.find(a - b) == used_int_set.end()){
            addEdge(i, used_int_arr.size() + n + 1, 1);
            used_int_set.emplace(a - b);
            used_int_arr.emplace(a - b, used_int_arr.size() + n + 1);
        }else{
            addEdge(i, used_int_arr[a - b], 1);
        }
        addEdge(0, i, 1);
    }
    #ifdef TEST
        for(auto j: add_ele){
            cout << j.first << " " << j.second << endl;
        }
    #endif
    End = used_int_arr.size() + n + 1;
    for (int i = n + 1; i <= used_int_arr.size() + n; i++){
        addEdge(i, End, 1);
    }
    int ANS = ffa(0, End);
    if(ANS != n){
        cout << "impossible\n";
    }else{
        int result;
        for (int i = 0; i < n; i++){
            cout << add_ele[i].F << " ";
            for(auto j: V[i]){
                if(get<1>(E[j]) == 0){
                    cout << "got the E:" << j << endl;
                    cout << "to: " << get<0>(E[j]) << " w: " << get<1>(E[j]) << endl;
                    if(j == opera[i][0]){
                        cout << "*";
                        result = add_ele[i].F * add_ele[i].S;
                        break;
                    }
                    else if(j == opera[i][1]){
                        cout << "+";
                        result = add_ele[i].F + add_ele[i].S;
                        break;
                    }
                    else if(j == opera[i][2]){
                        cout << "-";
                        
                        result = add_ele[i].F - add_ele[i].S;
                        break;
                    }
                }
            }
            cout << " " << add_ele[i].S << " = " << result << "\n";
        }
    }
    return 0;
}