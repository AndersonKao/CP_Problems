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

bool hasans[305] = {false};
double answers[305];
double dp[305];
double recur(int K){
    if(hasans[K])
        return dp[K];
    double ans = 0.0f;
    for(int i = 2; i <= K; i++){
        ans += recur(N-i+1);
    }
    ans /= (double)(N-K);

}

int main(){
    scanf("%d", &N);
    dp[1] = 1.0f;
    dp[2] = 0.5f;
    for(int i = 3; i <= N-1; i++){
        dp[i] = 0.0f;
        for(int j = i - 1; j >= 2; j--){
            dp[i] += dp[j];
        }
        dp[i] += 1.0f; // seat at N;
        dp[i] /= (double)(i);
    }
    dp[N] = 0.0f;
    for(int i = N-1; i >= 1; i--)
        dp[N] += dp[i];
    dp[N] /= (N-1);
    /*
    for(int i = 1; i <= N; i++)
        printf("%.10lf\n", dp[i]);
    */
    printf("%.10lf", dp[N]);

    

    return 0;
}