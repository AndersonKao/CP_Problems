// AC 2020/09/30 23:09:44

/*
    it turned out that I forgot to change the bool used[size];
    into the appropriate size, which it the max Node num, 2500 * (3 + 1) + 2;
*/
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

int n;
long long a, b;
vec<pll> add_ele;
map<ll, int> exist_ans;
long long index_to_result[10000];
int opera[2505][3]; // eleindex to the edge index

// 0:add, 1:minus, 2:multi
// sorry I think this problem can't use flow on bipartite graph
bool used[60000];
int End;
vec<int> V[60000];
vector<tuple<int, int>> E;
void addEdge(int x, int y,int c){
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
// #define TEST0
void pre_compute_ANSset(){
    long long result;
    int node_index;
    map<ll, int>::iterator iter;
    for (int i = 0; i < n; i++){
        // add part
        for (int j = 0; j < 3; j++){
            if(j == 0){        
                result = add_ele[i].first + add_ele[i].second;      
            }else if(j == 1){
                result = add_ele[i].first - add_ele[i].second;
            }else if(j == 2){
                result = add_ele[i].first * add_ele[i].second;
            }   
            #ifdef TEST0
                if(result == 0){
                    cout << "place 0 into \n";
                }
            #endif
            iter = exist_ans.find(result);
            if(iter == exist_ans.end()){
                #ifdef TEST0
                    if(result == 0)
                        cout << "0 not exist\n";
                #endif
                node_index = exist_ans.size() + n + 1;
                exist_ans.emplace(result, node_index);
                // size() + n + 1 = node index;
            }else{
                #ifdef TEST0
                    if(result == 0)
                        cout << "0 already existed " << iter->second << endl;
                #endif      
                node_index = iter->second;
            }
            opera[i + 1][j] = E.size();
            index_to_result[node_index] = result;
            addEdge(i + 1, node_index, 1);
        }
    }
}
void list_ele();
void list_graph();
// #define TEST
int main(){
    #ifdef TEST
        freopen("in2.txt", "r", stdin);
    #endif
    cin >> n;
    REP1(i, n){
        cin >> a >> b;
        add_ele.eb(a, b);
    }
    pre_compute_ANSset();
    #ifdef TEST
        for(auto j: add_ele){
            cout << j.first << " " << j.second << endl;
        }
    #endif
    End = exist_ans.size() + n + 1;
    for (int i = 1; i <= n; i++){
        addEdge(0, i, 1);
    }
    for (int i = n + 1; i <= exist_ans.size() + n; i++)
    {
        addEdge(i, End, 1);
    }
    int ANS = ffa(0, End);
    // list_graph();
    // cout << ANS << endl;
    if(ANS != n){
        cout << "impossible\n";
    }else{

        long long result;
        for (int i = 0; i < n; i++){
            // cout << add_ele[i].F << " ";
            for (int K = 0; K < 3; K++){
                int j = opera[i + 1][K];
                if(get<1>(E[j]) == 0){
            
                    // cout << "got the E:" << j << endl;
                    // cout << "to: " << get<0>(E[j]) << " w: " << get<1>(E[j]) << endl;
                    cout << add_ele[i].F << " ";
                    if(j == opera[i + 1][0]){
                        cout << "+";
                        result = add_ele[i].F + add_ele[i].S;
                        break;
                    }
                    else if(j == opera[i + 1][1]){
                        cout << "-";
                        result = add_ele[i].F - add_ele[i].S;
                        break;
                    }
                    else if(j == opera[i + 1][2]){
                        cout << "*";
                        
                        result = add_ele[i].F * add_ele[i].S;
                        break;
                    }
                }
            }
            cout << " " << add_ele[i].S << " = " << result << "\n";
        }
    }
    return 0;
}
void list_graph(){
    for (int i = 1; i <= n; i++){
        cout << "element: " << add_ele[i - 1].F << " " << add_ele[i - 1].second << endl;
        for (int j = 0; j < 3; j++){
            if(j == 0)
                cout << "+ part: ";
            else if(j == 1)
                cout << "- part: ";
            else
                cout << "* part: ";
            cout << "to node_ index: " << get<0>(E[opera[i][j]]) << " to result: " << index_to_result[get<0>(E[opera[i][j]])] << " w: " << get<1>(E[opera[i][j]]) << endl;
        }
    }
}