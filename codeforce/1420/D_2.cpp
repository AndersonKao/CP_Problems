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
int n, k;
class lamp{
public:
    long long in, out;
    lamp(): in(0), out(0){}
    lamp(long long a = 0, long long b = 0){
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
priority_queue<lamp, vec<lamp>, less<vec<lamp>::value_type>> Q;
long long Combseq[300005];
long long Comb(long long a, long long b){
    if(Combseq[a])
        return Combseq[a];
    long long ans = 1;
    long long c = max(a - b, b);
    
    b = min(a - b, b);
    for (long long i = a; i > c; i--){
        ans *= i;
        ans %= MOD;
    }
    for (long long i = 1; i <= b; i++){
        ans /= i;
    }
    return Combseq[a] =  ans;
}

bool testing = false;
#define MOD 998244353
int main(){
    yccc;
    if(testing){
        freopen("in.txt", "r", stdin);
    }
    memset(Combseq, 0, sizeof(Combseq));
    cin >> n >> k;
    long long a, b;
    REP(i, n){
        cin >> a >> b;
        V.eb(a, b);
    }
    sort(V.begin(), V.end(), cmp);
    long long index = 0;
    long long ans = 0;
    long long cur, i;
    while(index < n){
        while(Q.size() && Q.top().out < V[index].in){
            Q.pop();
        }
        cur = Q.size(); // segment that already in it;
        
        for (i = index; i < n && V[i].in == V[index].in; i++){
            Q.push(V[i]);
        }
        // cout << "cur: " << cur << " add: " << i - index << endl;
        index = i;
        if (Q.size() >= k)
        {
            ans += (Comb(Q.size(), k));
            ans %= MOD;
            if(cur >= k){
                ans -= (Comb(cur, k));
                ans %= MOD;
            }
        }
    }
    cout << ans << endl;
    return 0;
}