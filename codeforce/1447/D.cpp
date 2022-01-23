//AC Nov/16/2020 13:58UTC+8

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

string A, B;
int table[5005][5005];
void LCS(string a, string b){
    int len_a = a.length(), len_b = b.length();
    // int index;
    memset(table, 0, sizeof(table));
    for (int i = 1; i <= len_a; i++){
        if(a[i-1] == b[0]){
            table[i][1] = 2;
        }else{
            table[i][1] = table[i - 1][1] - 1;
            if(table[i][1] < 0)
                table[i][1] = 0;
        }
    }
    for (int i = 1; i <= len_b; i++){
        if(a[0] == b[i-1]){
            table[1][i] = 2;
        }else{
            table[1][i] = table[1][i-1] - 1;
            if(table[1][i] < 0)
                table[1][i] = 0;
        }
    }
    for (int i = 2; i <= len_a; i++)
    {
        for (int j = 2; j <= len_b; j++)
        {
            table[i][j] = max(table[i - 1][j], table[i][j - 1]) - 1;
            if (a[i - 1] == b[j - 1])
            {
                table[i][j] = max(table[i][j], table[i - 1][j - 1] + 2);
            }
            if (table[i][j] < 0)
                table[i][j] = 0;
        }
    }
}
int main(){
    char control;
    int n, m;
    cin >> n >> m;
    cin >> A >> B;
    int ANS = 0;
    LCS(A, B);
    int len_a = A.length();
    int len_b = B.length();
    REP1(i, len_a){
        REP1(j, len_b){
            ANS = max(ANS, table[i][j]);
        }
    }
    if(ANS < 0){
        ANS = 0;
    }
    cout << ANS << endl;
    // print_LCS(n, m);
    // cout << lcslen << endl;
    // cout << str << endl;
    // for (int i = 0; i <= len_a; i++){
    //     for (int j = 0; j <= len_b; j++){
    //         cout << table[i][j] << " ";
            
    //     }
    //     cout << endl;
    // }
        return 0;
}