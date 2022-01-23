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
int N;
int colhit[100005];
struct vtype
{

    /* data */
    bool in[5], out[5];
    bool turn3_1, turn3_2;
    vtype(){
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        turn3_1 = turn3_2 = false;
    }
};

vtype types[100005][2]; // zero for row, 1 for col
vector<pii> ANS;
vector<int> todo[4];
int main(){
    cin >> N;
    memset(colhit, 0, sizeof(colhit));
    for (int i = 1; i <= N; i++){
        cin >> colhit[i];
        types[i][1].in[colhit[i]] = true;
        if(colhit[i])
            todo[colhit[i]].push(i);
        if(i == N){
            if(colhit[i] == 2 || colhit[i] == 3){
                cout << "-1\n";
                return 0;
            }
        }

    }
    for(auto todocol: todo[3]){
        int findZero;
        int turn1, turn2;
        for (int i = 1; i <= N; i++){
            if(!types[i][0].turn3_1){
                types[i][0].turn3_1 = true;
                turn1 = i;
                break;
            }
        }
        for (int i = todocol + 1; i <= N; i++){
            if(!types[i][1].out[2] && !types[i][1].turn3_2){
                types[i][1].turn3_2 = true;

            }
        }
    }

        return 0;
}