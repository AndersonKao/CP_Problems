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
// #define TEST
int main(){
    #ifdef TEST
    freopen("in.txt", "r", stdin);
    #endif
    int T;
    cin >> T;
    string str;
    while(T--){
        int len, k;
        cin >> len >> k;
        cin >> str;
        int ans = 0;
        int counter = 0;
        int lone, rone;
        lone = rone = -1;
        for(int i = 0; i < len; i++){
            if(str[i] == '1'){
                lone = i;
                break;
            }
        }
        for (int i = len - 1; i >= 0; i--){
            if(str[i] == '1'){
                rone = i;
                break;
            }
        }
        // cout << "get: " << lone << " " << rone << endl;
        if(lone == -1 && rone == -1){
            // cout << "case1:\n";
            ans += (len / (k + 1));
            // debug(ans);
            if((len % (k + 1)) != 0)
                ans++;
            // debug(ans);
            if(ans == 0)
                ans++;
            // debug(ans);
        }else if (lone == rone){
            ans += (lone / (k + 1));
            ans += ((len - rone - 1) / (k + 1));
        }else{
            // cout << "case3\n";
            ans += (lone / (k + 1));
            // debug(ans);
            ans += ((len - rone - 1) / (k + 1));
            // debug(ans);
            int cnt = 0;
            for (int i = lone + 1; i <= rone; i++){
                if (str[i] == '0'){
                    cnt++;
                }else if(cnt >= (2 * k + 1)){
                    ans += (cnt / (k + 1));
                    if(cnt % (k + 1) != k){
                        ans--;
                    }
                    cnt = 0;
                }else{
                    cnt = 0;
                }
            }
            // debug(ans);
        }
#ifdef TEST
        cout << "final: " <<  str << endl;
        #endif
        cout << ans << endl;
        }
    return 0;
}