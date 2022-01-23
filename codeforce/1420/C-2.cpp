// AC Sep/28/2020 21:30UTC+8
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
int seq[300005];
int N, T, Q;
long long ans;
void remove(int x){
    if(x == 0 || x == N + 1)
        return;
    if(seq[x] > seq[x - 1] && seq[x] > seq[x + 1])
        ans -= seq[x];
    else if(seq[x] < seq[x - 1] && seq[x] < seq[x + 1])
        ans += seq[x];
    
}
void insert(int x){
    if(x == 0 || x == N + 1)
        return;
    if(seq[x] > seq[x - 1] && seq[x] > seq[x + 1])
        ans += seq[x];
    else if(seq[x] < seq[x - 1] && seq[x] < seq[x + 1])
        ans -= seq[x];
    
}
int main(){
    yccc;
    cin >> T;
    while (T--)
    {
        /* code */
        cin >> N >> Q;
        REP1(i, N){
            cin >> seq[i];
        }
        seq[0] = seq[N + 1] = -1;
        ans = 0;
        REP1(i, N){
            if(seq[i] > seq[i-1] && seq[i] > seq[i + 1]){
                ans += seq[i];
            }else if(seq[i] < seq[i-1] && seq[i] < seq[i + 1]){
                ans -= seq[i];
            }
        }
        cout << ans << endl;
        int a, b;

        while(Q--){
            cin >> a >> b;
            if(a == b){
                cout << ans << endl;
                continue;
            }
            remove(a - 1);
            remove(a);
            remove(a + 1);
            if((b - 1) != a && b-1 != a + 1){
                remove(b - 1);
            }
            if(b != a + 1)
                remove(b);
            remove(b + 1);
            
            swap(seq[a], seq[b]);

            insert(a - 1);
            insert(a);
            insert(a + 1);
            if(b - 1 != a && b-1 != a + 1){
                insert(b - 1);
            }
            if(b != a + 1)
                insert(b);
            insert(b + 1);
            cout << ans << endl;
        }
    }
    
    return 0;
}