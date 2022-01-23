//  AC Sep/27/2020 23:00UTC+8
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
int N;
bool possible(int x){
     vector<int> b;
     bool f = true;
     int pos_a = 0, pos_b = N - (x + 1);
     for (int i = 0; i < 2 * x + 1; ++i)
     {
         if (i % 2 == 0)
         {
             b.emplace_back(seq[pos_b]);
             ++pos_b;
         }
         else
         {
             b.emplace_back(seq[pos_a]);
             ++pos_a;
         }
    }
    for (int i = 1; i < 2 * x + 1; i += 2) {
        if (b[i] >= b[i - 1] || b[i] >= b[i + 1])
            f = false;
    }
    return f;
}
int main(){
    cin >> N; 
    REP(i, N){
        cin >> seq[i];
    }
    sort(seq, seq + N);
    // REP(i, N){
    //     debug(seq[i]);
    // }
    int l = 0, r = N / 2 + 2;
    int mid;
    while(r - l > 1){
        
        mid = (l + r) / 2;
        if( 2* mid + 1 > N){
            r= mid;
            continue;
        }
        if(possible(mid)){
            // if(mid == l)
            //     break;
            l = mid;
        }else{
            r = mid;
        }
        // debug(l);
        // debug(r);
    }

    cout << l << endl;
    if(l == 0){
        REP(i, N){
            cout << seq[i] << (i == N - 1 ? '\n' : ' ');
        }
        return 0;
    }
    int l_index = 0, h_index = N - (l + 1);
    for(int i  = 0; i < 2 * l + 1; i++){
        if(i & 1){
            cout << seq[l_index];
            l_index++;
        }else{
            cout << seq[h_index];
            h_index++;
        }
        cout << " ";
    }
    for (int i = l_index; i < N - (l + 1); i++){
        cout << seq[i] << " ";
    }
    cout << endl;
    return 0;
}