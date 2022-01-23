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
int prefixZeroA[300005];
int prefixOneA[300005];
// int prefixZeroB[300005];
// int prefixOneB[300005];

void init(){
    memset(prefixZeroA, 0, sizeof(prefixZeroA));
    memset(prefixOneA, 0, sizeof(prefixOneA));
    // memset(prefixZeroB, 0, sizeof(prefixZeroB));
    // memset(prefixOneB, 0, sizeof(prefixOneB));
}
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        // init();
        string A, B;
        cin >> A >> B;
        if(A == B){
            // cout << "same\n";
            cout << "YES\n";
            continue;
        }
        REP(i, N){
            if(A[i] == '0')
                prefixZeroA[i] = prefixZeroA[i - 1] + 1;
            else
                prefixZeroA[i] = prefixZeroA[i - 1];
            if(A[i] == '1')
                prefixOneA[i] = prefixOneA[i - 1] + 1;
            else
                prefixOneA[i] = prefixOneA[i - 1];
            // if(B[i] == '0')
            //     prefixZeroB[i] = prefixZeroB[i - 1] + 1;
            // else
            //     prefixZeroB[i] = prefixZeroB[i - 1];
            // if(B[i] == '0')
            //     prefixOneB[i] = prefixOneB[i - 1] + 1;
            // else
            //     prefixOneB[i] = prefixOneB[i - 1];
        }
        int diff = 0;
        REP(i, N){
            if(A[i] != B[i])
                diff++;
        }
        if(diff & 1){
            cout << "NO\n";
            continue;
        }
        int index = N - 1;
        while(A[index] == B[index])
        {
            index--;
        }
        while(index >= 0){
            // at first diff
            if(prefixZeroA[index] != prefixOneA[index]){
                cout << "NO\n";
                break;
            }
            while(index >= 0 && A[index] != B[index]){
                index--;
            }
            if(index <0){
                cout << "YES\n";
                break;
            }
            if(prefixOneA[index] != prefixZeroA[index]){
                cout << "NO\n";
                break;
            }
            while(index >= 0 && A[index] == B[index]){
                index--;
            }
            if(index < 0){
                cout << "YES\n";
                break;
            }
        }
        
    }
    return 0;
}