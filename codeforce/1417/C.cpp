// AC Sep/28/2020 12:10UTC+8
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
vector<pii> V;
int ans[300005];
int main(){
    int T;
    int N;
    int num;
    cin >> T;
    while(T--){
        V.clear();
        memset(ans, -1, sizeof(ans));
        cin >> N;
        REP(i, N){
            cin >> num;
            V.eb(num, i + 1);
        }
        REP(i, N - 1){
            if(V[i].F != V[i + 1].F){
                ans[1] = -1;
                break;
            }
            if(i == N-2){
                ans[1] = V[0].F;
            }
        }
        sort(V.begin(), V.end());
        // for(auto t: V){
        //     cout << t.F << " " << t.S << endl;
        // }
        int index = 0;
        while(index < N){
            int maxdis = 0;
            int j = 0;
            maxdis = V[index].S;
            while(V[index + j + 1].F == V[index].F){
                maxdis = max(maxdis, V[index + j + 1].S - V[index + j].S);
                ++j;
            }
            maxdis = max(maxdis, N - V[index + j].S + 1);
            
            if(ans[maxdis] == -1){
                ans[maxdis] = V[index].F;
            }else{
                ans[maxdis] = min(ans[maxdis], V[index].F);
            }
            
            // cout << "now Index: " << index << " maxdis: " << maxdis << endl;
            // REP1(i, N){
            //     cout << ans[i] << " ";
            // }
            // cout << endl;
            index = index + j + 1;
        }

        REP1(i, N){
            if(ans[i-1] != -1){
               if(ans[i] == -1){
                   ans[i] = ans[i - 1];
               }else{
                   ans[i] = min(ans[i], ans[i - 1]);
               }
            }
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}