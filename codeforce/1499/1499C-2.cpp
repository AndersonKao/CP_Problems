// AC Apr/03/2021 15:33UTC+8
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
long long cost[100005];
void init(){
    memset(cost, 0, sizeof(cost));
}
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        REP(i, N){
            cin >> cost[i];
        }
        int minodd_index = 1;
        int mineven_index = 0;
        long long sumEven, sumOdd;
        sumEven = cost[0];
        sumOdd = cost[1];
        int cntEven, cntOdd;
        cntEven = cntOdd = 1;
        long long ans = (cost[0] + cost[1]) * N;
        // even base: consider possible answer end in even index;
        for (int index = 2; index < N; index++){
            if((index & 1) == 1) // odd
            {
                minodd_index = (cost[index] < cost[minodd_index] ? index : minodd_index);
                ans = min(ans, cost[minodd_index] * (N - cntOdd) + sumOdd + cost[mineven_index] * (N - cntEven) + sumEven);
                cntOdd++;
                sumOdd += cost[index];
            }
            else // even
            {

                mineven_index = (cost[index] < cost[mineven_index] ? index : mineven_index);
                ans = min(ans, cost[minodd_index] * (N - cntOdd) + sumOdd + cost[mineven_index] * (N - cntEven) + sumEven);
                cntEven++;
                sumEven += cost[index];
            }
        }
        cout << ans << endl;
    }
    return 0;
}