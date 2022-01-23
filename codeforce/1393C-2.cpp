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
int cnt[100005];
int putten[100005];
set<pii> S;
vector<pii> V;
bool valid(int len){
    memset(cnt, 0, sizeof(cnt));
    memset(putten, 0, sizeof(putten));
    V.clear();
    REP(i, N){
        cnt[seq[i]]++;
    }
    int OneCnt = 0;
    REP1(i, N){
        if(cnt[i] == 0)
            continue;
        S.emplace(cnt[i], i);
    }
    sort(V.begin(), V.end(), greater<pii>);
    set<pii,greater<pii>>::iterator iter = S.begin();
    if((iter->first-1) * len + 1 > N)
        return 0;
    int need = 0;
    for (int i = 1; i <= N; i++){
        if (i > len){
            if(cnt[putten[i-len]]){
                putten[i] = putten[i - len];
                cnt[putten[i]]--;
            }else{
                putten[i] = iter->second;
                cnt[iter->second]--;
                if(cnt[iter->second])
            }
        }else{
            putten[i] = iter->second;
            cnt[iter->second]--;
            iter++;
            if(iter == S.end()){
                iter = S.begin();
            }
        }
    }
}
int main(){
    cin >> T;
    while(T--){
        memset(seq, 0, sizeof(seq));
        memset(cnt, 0, sizeof(cnt));
        V.clear();
        cin >> N;
        REP(i, N){
            cin >> seq[i];
            cnt[seq[i]]++;
        }
        int oneCnt = 0;
        REP1(i, N){
            if(cnt[i] == 1){
                oneCnt++;
            }else if(cnt[i] != 0){
                V.eb(cnt[i], i);
            }
        }
        sort(V.begin(), V.end());
        for(auto u: V){
            cout << u.first << " " << u.second << endl;
        }
    }
    return 0;
}