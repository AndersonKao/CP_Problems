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
int seq[505];
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        int X;
        cin >> X;
        REP(i ,N ){
            cin >> seq[i];
        }
        bool can = true;
        bool solved = false;
        for (int i = 0; i < N-1; i++){
            if(seq[i] > seq[i + 1]){
                break;
            }
            if(i == N-2){
                solved = true;
            }
        }
        if(solved || N == 1){
            cout << 0 << endl;
            continue;
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (seq[i] > seq[j] && seq[i] <= X)
                {
                    cout << "-1\n";
                    can = false;
                    break;
                }
            }
            if (!can)
                break;
        }
        if(!can)
            continue;
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            // cout << i << ": ";
            // REP(r, N){
            //     cout << seq[r] << (r == (N - 1) ? '\n' : ' ');
            // }
            bool inver = false;
            for (int j = i + 1; j < N; j++){
                for (int k = j + 1; k < N; k++){
                    if(seq[j] > seq[k]){
                        inver = true;
                        break;
                    }
                }
                if(inver)
                    break;
            }
            if(inver && seq[i] > X){
                cnt++;
                swap(seq[i], X);
                continue;
            }
            for (int j = i + 1; j < N; j++)
            {
                if (seq[i] > seq[j] && seq[i] > X)
                {
                    cnt++;
                    swap(seq[i], X);
                    break;
                }
            }
        }
        for (int i = 0; i < N-1; i++){
            // cout << seq[i] << " ";
            if(seq[i] > seq[i + 1]){
                break;
            }
            if(i == N-2){
                solved = true;
            }
        }
        // cout << seq[N-1]<< endl;
        if(solved)
            cout << cnt << endl;
        else
        {
            cout << -1 << endl;
        }
        
    }
    return 0;
}