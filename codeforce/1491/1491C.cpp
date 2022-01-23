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
// #define TESTSEQ
int T, N;
int seq[5005];
int curr[5005];
int main(){
    yccc;
    cout.tie(0);
    cin.exceptions(ios::badbit | ios::failbit);
    cin >> T;
    int L, R;
    while(T--){
        long long ans = 0;
        cin >> N;
        memset(seq, 0, sizeof(seq));
        memset(curr, 0, sizeof(curr));
        int L = INF;
        REP(i, N){
            cin >> seq[i];
            L = seq[i] == 1 ? L : min(L, i);
        }
        #ifdef TESTSEQ
            cout << "seq: ";
            REP(i, N)
            {
            cout << seq[i] << " ";
            }
            cout << endl;
            cout << "curr: ";
            REP(i, N){
                cout << curr[i] << " ";
            }
            cout << endl;
        #endif
        for(int index = L; index < N; index++){

            int tmpeko = curr[index];

            if (tmpeko < seq[index] - 1)
            {
                ans += (seq[index] - tmpeko - 1);
                tmpeko += (seq[index] - tmpeko - 1);
            }
            // below if doesn't matter because 
            // if it is less than it will cause the next index's
            //  previous if won't work since it already go to strength 1
            if(tmpeko > seq[index] - 1) 
                curr[index + 1] += (tmpeko - seq[index] + 1);
            for (int addi = index + 2; addi <= min(N-1, (index + seq[index])); addi++){
                curr[addi]++;
            }
            #ifdef TESTSEQ
            cout << "seq: ";
            REP(i, N)
            {
                cout << seq[i] << " ";
                }
                cout << endl;
                cout << "curr: ";
                REP(i, N){
                    cout << curr[i] << " ";
                }
                cout << endl;
            #endif
        }
        cout << ans << endl;
    }
    return 0;
}

/*
Have an array curr which holds all the jumps made on an index.

For an index i:

if the jumps made so far (curr[i]) were not enough to get it to 1, then add to the solution the remaining Si-1-curr[i] jumps (each of these jumps is a new pass because i is the first non-1 trampoline).

after the if is executed, temp is the number of jumps on index i

temp — (Si — 1) = the number of jumps on index i — the number of jumps necessary to get to strength 1 = all the jumps that jumped to i + 1. So we add all of these jumps to curr[i + 1]

add 1 jump to curr[j] for j in range [i + 2, i + Si]. These jumps are performed in order to get the trampoline i to strength 1
*/