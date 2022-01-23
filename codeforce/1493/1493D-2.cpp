// AC Mar/13/2021 20:10UTC+8
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
int seq[200005];
map<int, int> M[200005];
long long ans = 1;
set<int> appear;
int got[200005];
// #define TEST_POWER
void renewANS(int x){
    if(got[x] < N){
        return;
    }
    // cout << "renewing ans with " << x << endl;
    int minPow = INT_MAX;
    REP(i, N){
        minPow = min(minPow, M[i][x]);
    }
    got[x] = 0;
    // long sub;
    map<int, int>::iterator it;
    REP(i, N){
        it = M[i].find(x);
        it->second -= minPow;
        if(it->second != 0){
            got[x]++;
        }
    }
    ans *= POW(x, minPow);
    ans %= MOD;
}
int main(){
    cin >> N;
    cin >> T;
    memset(got, 0, sizeof(got));
    REP(i, N){
        cin >> seq[i];
        long long c = seq[i];
        long long x = 2;
        while( x*x <= c )
        {
            if(c%x==0)//found a prime factor
            {
                long long Pow = 0;
                while( c%x==0 )
                {
                    c/=x;
                    Pow++;
                }
                // PF[i].push_back( make_pair(x,Pow) );
                M[i][x] = Pow;
                appear.emplace(x);
                got[x]++;
            }
            x++;
        }
        if( c>1 ){
            // PF.push_back( make_pair(c,1) );
            got[c]++;
            M[i][c] = 1;
            appear.emplace(c);
        }
    }
    #ifdef TEST_POWER
    REP(i, N){
        for(auto it: M[i]){
            cout << it.F << "^" << it.S << " ";
        }
        cout << endl;
    }
    #endif
    for(auto it: appear){

        // cout << got[it] << " number have this " << it << endl;
        renewANS(it);
    }
    // cout << ans << endl;
    int index, multi;
    REP(i, T){
        cin >> index >> multi;
        index--;
        long long c = multi;
        long long x = 2;
        while(x * x <= c){
            if(c % x == 0){
                long long Pow = 0;
                while(c % x == 0){
                    c /= x;
                    Pow++;
                }
                if(M[index][x] == 0){
                    // cout << "index " << index << " don't have " << x << " !!\n";
                    got[x]++;
                }
                M[index][x] += Pow;
                renewANS(x);
            }
            x++;
        }
        if(c > 1){
            if(M[index][c] == 0){
                got[c]++;
            }
            M[index][c] += 1;
            renewANS(c);
        }
        cout << ans << endl;
    }
    return 0;

}