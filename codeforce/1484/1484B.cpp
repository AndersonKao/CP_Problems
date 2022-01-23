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
int seq[100005];
int diff[100005];
void init(){
    REP(i, N + 2){
        seq[i] = 0;
        diff[i] = 0;
    }
    // memset(seq, 0, sizeof(seq));
    // memset(diff, 0, sizeof(diff));
}
// #define OERROR
int main(){
    yccc;
    cin >> T;
    while(T--){
        cout.flush();
        cin >> N;
        #ifdef OERROR
        cout << "N: " << N << endl;
        #endif
        init();
        int M, C, s;
        bool same = true;
        REP(i, N){
            cin >> seq[i];
            if(i > 0 && seq[i] != seq[i-1])
                same = false;
            if(i > 0){
                diff[i-1] = seq[i] - seq[i - 1];
            }
        }
        #ifdef OERROR
        REP(i, N-1)
        cout << diff[i] << ' ';
        cout << endl;
        #endif
        if(N == 2){
            cout << 0 << endl;
            #ifdef OERROR
            cout << "onely 2\n";
            #endif
            continue;
        }
        bool oddevensame = false;
        // REP(i, N){
        //     if (i + 2 < N && seq[i] != seq[i+2]){
        //         oddevensame = false;
        //         break;
        //     }
        // }
        if(oddevensame || same || N == 1){
            cout << 0 << endl;
            #ifdef OERROR
            cout << "same or only 1\n";
            cout << oddevensame << " " << same << " " << (N == 1) << endl;
        #endif
            continue;
        }
        bool havezero, havenozero;
        havezero = havenozero = false;
        REP(i, N-1){
            if(diff[i] != 0){
                havenozero = true;
                break;
            }
        }
        REP(i, N-1){
            if(diff[i] == 0){
                havezero = true;
                break;
            }
        }
        if(havezero && havenozero){
            cout << -1 << endl;
            #ifdef OERROR
            cout << "zero nozero\n";
            #endif
            continue;
        }
        REP(i, N - 1 ){
            if(diff[i] >= 0){
                C = diff[i];
                break;
            }
        }
        bool diffsame = true;
        REP(i, N-1){
            if(diff[i]>=0 && diff[i] != C){
                diffsame = false;
                break;
            }
        }
        if(!diffsame){
            cout << -1 << endl;
            #ifdef OERROR
            cout << "positive not same\n";
            #endif
            continue;
        }
        #ifdef OERROR
        cout << "C: " << C << endl;
        #endif
        bool solved = false;
        REP(i, N){
            if(diff[i] < 0){
                #ifdef OERROR
                cout << "ans i = " << i << endl;
                #endif
                int anspre = seq[i] + C - seq[i + 1];
                if(anspre <= C || seq[0] >= anspre){
                    cout << -1 << endl;
                }else{
                    cout << anspre << " " << C << endl;
                }
                break;
            }
        }

    }
    return 0;
}