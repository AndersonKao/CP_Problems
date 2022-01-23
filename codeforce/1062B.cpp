// AC Feb/28/2021 01:15UTC+8
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
map<int, int> PF;
int hob (int num)
{
    if (!num)
        return 0;

    int ret = 0;

    while (num >>= 1)
        ret++;

    return ret;
}
int main(){
    cin >> N;
    if(N == 1){
        cout << 1 << " " << 0 << endl;
        return 0;
    }
    int x = 2;
    int cnt;
    int Ni = N;
    while(x*x <= N){
        cnt = 0;
        if(Ni % x == 0){
            while(Ni % x == 0){
                Ni /= x;
                cnt++;
            }
            PF[x] = cnt;
        }
        x++;
    }
    int ans1 = 1;
    if(Ni != 1){
        PF[Ni] = 1;
    }
    int max_p = 0;
    int proc;
    int min_p = INT_MAX;
    for(auto ele: PF){
        ans1 *= ele.first;
        max_p = max(max_p, ele.second);
        min_p = min(min_p, ele.second);
        // cout << ele.first << " " << ele.second << endl;
    }
    int ans2 = 0;
    ans2 = hob(max_p);
    // cout << max_p << endl;
    if(max_p == pow(2, ans2)){
        if(max_p != min_p)
            ans2++;
        cout << ans1 << " " << ans2 << endl;
    }else
    {
        cout << ans1 << " " << ans2 + 2 << endl;
        
    }
    
    return 0;
}