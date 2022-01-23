
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
ofstream operator<<(ofstream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.Startime; return out; }
int T, N;
int h, m;
pii Startime;
void Addone(){
    Startime.S = Startime.S + 1;
    if(Startime.S == m){
        Startime.S = 0;
        Startime.F++;
        if(Startime.F >= h){
            Startime.F = 0;
        }
    }
}
bool isMIRRORNUM(int a){
    if(a == 0 || a == 1 || a == 2 || a == 5 || a == 8)
        return true;
    return false;
}
int takeMirror(int a){
    int ans = 0;
    int fi = a / 10, sen = a % 10;
    if(fi == 0){
        ans += 0;
    }
    else if(fi == 1){
        ans += 1;
    }
    else if(fi == 2){
        ans += 5;
    }
    else if(fi == 5){
        ans += 2;
    }
    else if(fi == 8){
        ans += 8;
    }
    if(sen == 0){
        ans += 0;
    }
    else if(sen == 1){
        ans += 10;
    }
    else if(sen == 2){
        ans += 50;
    }
    else if(sen == 5){
        ans += 20;
    }
    else if(sen == 8){
        ans += 80;
    }
    return ans;
}
bool IFMirror(){
    if(isMIRRORNUM(Startime.S/10) && isMIRRORNUM(Startime.S % 10) &&
     isMIRRORNUM(Startime.F / 10) && isMIRRORNUM(Startime.F % 10)){
        if(takeMirror(Startime.F) < m && takeMirror(Startime.S) < h)
            return true;
    }
    return false;
}
int main(){
    cin >> T;
    while(T--){
        cin >> h >> m;

        scanf("%d:%d", &Startime.F, &Startime.S);
        // cout << Startime.F << " " << Startime.S << endl;
    //
        while(!IFMirror()){
            Addone();
        }
        if(Startime.F < 10){
            cout << "0";
        }
        cout << Startime.F << ":";
        if(Startime.S < 10){
            cout << "0";
        }
        cout << Startime.S << endl;
    }
    return 0;
}