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
string S_str, E_str; // start string, end string;
bool is_Odd(string & str){
    char ch = str[str.length() - 1];
    if(ch == '1' || ch == '3' || ch == '5' || ch == '7' || ch == '9')
        return true;
    else
        return false;
}
void shift(string & str){
    if(str == "0")
        return;
    if(str == "1")
    {
        str = "0";
        return;
    }
    string new_str = "";
    unsigned Len = str.length();
    unsigned i = 0;
    while(str[i] == '1')
        i++;
    for (; i < Len;i++){
        switch (str[i])
        {
        case '0':
            new_str += "0";
            break;
        case '1':
            new_str += "0";
            break;
        case '2':
            new_str += "1";
            break;
        case '3':
            new_str += "1";
            break;
        case '4':
            new_str += "2";
            break;
        case '5':
            new_str += "2";
            break;
        case '6':
            new_str += "3";
            break;
        case '7':
            new_str += "3";
            break;
        case '8':
            new_str += "4";
            break;
        case '9':
            new_str += "4";
            break;
        
        default:
            break;
        }
        char ch = str[i-1];
        if(ch == '1' || ch == '3' || ch == '5' || ch == '7' || ch == '9')
            new_str[new_str.length() - 1] += 5;
    }
    str = new_str;
}
long long ans_FChange;
long long ans_FSame;
int main(){
    while (cin >> S_str >> E_str)
    {
        cout << S_str << " " << E_str << endl;
        ans_FSame = 0;
        ans_FChange = 1;
        if(S_str == "0" && E_str == "0")
            break;
        else if(S_str == E_str)
        {
            cout << "0\n";
            continue;
        }
        // while(S_str != "0"){
        //     cout << "case: ";
        //     cout << S_str << endl;
        //     shift(S_str);
        // }
        // cout << S_str << endl;
        bool S_odd, E_odd;
        
        while(S_str != "0" && E_str != "0"){
            S_odd = is_Odd(S_str);
            E_odd = is_Odd(E_str);

        }



    }
    return 0;
}