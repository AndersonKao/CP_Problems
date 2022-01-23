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
int seq[200005];
int ans[200005];
map<int, int> M;
map<int, stack<int>> M2;
int main(){
    cin >> T;
    while(T--){
        int C;
        cin >> N >> C;
        M.clear();
        M2.clear();
        for (int i = 0; i < N; i++){
            cin >> seq[i];
            M[seq[i]]++;
            M2[seq[i]].push(i);
        }
        int br = 1;
        stack<int> index;
        for(auto it: M){
            int cnt = 1;
            if(it.second >= C){
                auto it2 = M2[it.first];
                while(!it2.empty()){
                    if(cnt > C){
                        ans[it2.top()] = 0;
                    }else{
                        ans[it2.top()] = cnt++;
                    }
                    it2.pop();
                }
            }else{
                auto it2 = M2[it.first];
                while(!it2.empty()){                    ans[it2.top()] = br++;
                    index.push(it2.top());
                    if(br > C)
                        br = 1;
                    it2.pop();
                }
            }
        }
        br--;
        while(br--){
            ans[index.top()] = 0;
            index.pop();
        }
        for (int i = 0; i < N; i++){
            cout << ans[i] << (i == N - 1 ? '\n' : ' ');
        }
    }
    return 0;
}