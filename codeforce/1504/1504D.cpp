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
int matrix[105][105];
bool isnearing(int color, int x, int y){
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            if(x + dx < 0 || x + dx >= N || y + dy < 0 || y + dy >= N)
                continue;
            if(matrix[y+dy][x+dx] == color)
                return false;
        }
    }
    return true;
}
void increase(int &x, int &y){
    x = x + 2;
    if(x >= N){
        x = x - N;
        y += 1;
    }
}
int main(){
    cin >> N;
    T = N * N;
    memset(matrix, 0, sizeof(matrix));
    
    while(T--){
        // cin >> N;
        int blocked;
        cin >> blocked;
        int index[3][2];
        // 0 for x ,1 for y;
        index[0][0] = 0; // g
        index[0][1] = 0;  
        index[1][0] = 1;  // r
        index[1][1] = 0;
        index[2][0] = 0; // b
        index[2][1] = 1;
        int color = (blocked + 1) % 3;
        if(isnearing(color, index[color][0], index[color][1]))
        {
            while(matrix[index[color][90]])
        }            // color = (color + 1) % 3;

    }
    return 0;
}