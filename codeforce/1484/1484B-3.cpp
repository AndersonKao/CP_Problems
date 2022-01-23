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
ll seq[100005];
ll diff[100005];
set<int> setof, seneg;
void init(){
    REP(i, N + 2){
        seq[i] = 0;
        diff[i] = 0;
    }
    setof.clear();
    seneg.clear();
    // memset(seq, 0, sizeof(seq));
    // memset(diff, 0, sizeof(diff));
}
// #defint C;ine OERROR
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
        ll M, C, s;
        bool same = true;
        REP(i, N){
            cin >> seq[i];
            if(i > 0 && seq[i] != seq[i-1])
                same = false;
            if(i > 0){
                diff[i-1] = seq[i] - seq[i - 1];
                if(diff[i-1] >= 0)
                    setof.emplace(diff[i - 1]);
                else
                    seneg.emplace(diff[i - 1]);
            }
        }
        #ifdef OERROR
        REP(i, N-1)
        cout << diff[i] << ' ';
        cout << endl;
        #endif

        if(setof.size() >= 2|| (setof.size() + seneg.size()) > 2){
            cout << -1 << endl;
            continue;
        } else if(N == 1 || (setof.size() + seneg.size() <2)){
            cout << 0 << endl;
            continue;
        } 
        // bool gotc = false;
        REP(i, N - 1 ){
            if(diff[i] >= 0){
                C = diff[i];
                // gotc = true;
                break;
            }
        }
        ll anspre;
        REP(i, N-1){
            if(diff[i] < 0){
                #ifdef OERROR
                cout << "ans i = " << i << endl;
                #endif
                anspre = seq[i] + C - seq[i + 1];
                // gotM = true;
                break;
            }
        }
        if(seq[0] >= anspre){
            cout << -1 << endl;
            continue;
        }
        bool solved = false;
        ll cur_num = seq[0];
        for (int i = 1; i < N; i++){
            cur_num = cur_num + C;
            
            if(cur_num >= anspre){
                cur_num -= anspre;
            }
            if(cur_num != seq[i]){
                cout << -1 << endl;
                solved = true;
                #ifdef OERROR
                cout << "wrong num at" << i << " cur = " << cur_num  << '\n';
                #endif
                break;
            }
        }
        if(solved)
            continue;
        else
            cout << anspre << " " << C << endl;
        // cout << anspre << " " << C << endl;
    }
        return 0;
}

/*
9
9
5 2 4 5 2 4 5 2 4
-1
10 
5 15 10 5 15 10 5 15 10 5 
-1
6
4 21 38 45 2 19
*/