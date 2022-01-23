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
unsigned long long n, k;
class lamp{
public:
    unsigned long long in, out;
    lamp(): in(0), out(0){}
    lamp(unsigned long long a = 0, unsigned long long b = 0){
        in = a;
        out = b;
    }
};
vec<lamp> V;
bool operator<(const lamp & lval, const lamp & rval){
    return lval.out > rval.out;
}

bool cmp(const lamp & lval, const lamp & rval){
    return lval.in < rval.in;
}
using i64 = unsigned long long;
#define maxn 300006

priority_queue<lamp, vec<lamp>, less<vec<lamp>::value_type>> Q;

i64 fact[maxn], tcaf[maxn];

bool testing = true;
#define MOD 998244353
 
i64 deg(i64 x, i64 d) {
    if (d < 0) d += MOD - 1;
    i64 y = 1;
    while (d) {
        if (d & 1) (y *= x) %= MOD;
        d /= 2;
        (x *= x) %= MOD;
    }
    return y;
}
void init(int n){
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % MOD;
    for (int i = n; i >= 0; --i)
        tcaf[i] = deg(fact[i], -1);
}
 
i64 cnk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * tcaf[k] % MOD * tcaf[n - k] % MOD;
}
 
int main(){
    yccc;
    if(testing){
        freopen("in.txt", "r", stdin);
    }
    memset(fact, 0, sizeof(fact));
    memset(tcaf, 0, sizeof(tcaf));
    cin >> n >> k;
    init(n + 10);
    unsigned long long a, b;
    
    REP(i, n){
        cin >> a >> b;
        V.eb(a, b);
    }

    sort(V.begin(), V.end(), cmp);
    unsigned long long index = 0;
    unsigned long long ans = 0;
    unsigned long long cur, runi;
    while(index < n){
        while(Q.size() && Q.top().out < V[index].in){
            Q.pop();
        }
        cur = Q.size(); // segment that already in it;
        
        for (runi = index; runi < n && V[runi].in == V[index].in; runi++){
            Q.push(V[runi]);
        }
        // cout << "cur: " << cur << " add: " << i - index << endl;
        index = runi;
        if (Q.size() >= k)
        {
            ans += (cnk(Q.size(), k));
            ans %= MOD;
            if(cur >= k){
                ans -= (cnk(cur, k));
                ans %= MOD;
            }
        }
    }
    cout << ans % MOD << endl;
    return 0;
}