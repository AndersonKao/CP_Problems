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
int seq[100005];
bool color[100005];
multiset<int> s1, s2;
multiset<int> num1, num2;
#define TEST
int main(){
    // freopen("in.txt", "r", stdin);
    yccc;
    int n, K, T;
    cin >> K;
    while(K--){
        s1.clear();
        s2.clear();
        num1.clear();
        num2.clear();
        memset(color, 0, sizeof(color));
        cin >> n >> T;
        REP(i, n){
            cin >> seq[i];
        }
        int ans = 0;
        REP(i, n){
            int s1num = num1.count(T - seq[i]);
            int s2num = num2.count(T - seq[i]);
            // debug(seq[i]);
            // debug(s1num);
            // debug(s2num);
            
            if(s1num > s2num){
                ans += s2num;
                s2.emplace(i);
                num2.emplace(seq[i]);
            }else{
                ans += s1num;
                s1.emplace(i);
                num1.emplace(seq[i]);
            }
            
        }
        for(auto i: s1){
            color[i] = 1;
        }
        // cout << ans << endl;
        REP(i, n){
            cout << color[i] << " ";
        }
        cout << endl;
    }
        return 0;
}