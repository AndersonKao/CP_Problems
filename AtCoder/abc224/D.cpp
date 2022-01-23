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
bool ans = false;
int anstep = 10000000;
bool G[10][10] = {false};
set<string> visited;
string str;
void solved(int s){
    
    REP1(i, 8){
        if(seq[i] != i){
            return ;
        }
    }
    anstep = anstep > s ? s : anstep;
    ans = true;
}

queue<pair<tuple<int, int, int, int, int, int, int, int, int>, int>> Q;
void BFS(int empty){
    while(!Q.empty()){
        for(int i = 1; i <= 9; i++){
            seq[i] = get<1>(Q.front().first);
            if(seq[i] == 0)
                empty = i;
        }
        
        REP1(i, 9){
            printf("%d ", seq[i]);
        }
        printf("\n");
        int step = Q.front().second;
        solved(step);
        if(ans)
            return;
        for(int i = 1; i < 10; i++){
            if(G[empty][i]){
                if(S.find(str) != S.end())
                    continue;
                swap(str[empty], str[i]);
                swap(seq[empty], seq[i]);
            }
        }

    }
}


int main(){
    scanf("%d", &N);
    int a, b;
    REP(i, N){

        scanf("%d %d", &a, &b);
        G[a][b] = true;
        G[b][a] = true;
    }
    int data;
    str.resize(10);
    REP1(i, 8){
        scanf("%d", &data);
        str[data] = itoc(data);
    }
    REP1(i, 9){
        if(seq[i] == 0)
        {
            BFS(i);
            break;
        }
    }
    if(ans)
        printf("%d\n", anstep);
    else
        printf("-1\n");

    return 0;
}