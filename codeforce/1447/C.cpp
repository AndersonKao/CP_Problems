// AC Nov/15/2020 23:47UTC+8

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
long long dataad;
prior<pair<long long, int>> Q;
int main(){
    int T;
    cin >> T;
    int N;
    long long W;
    while(T--){
        // memset(seq, 0, sizeof(seq));
        vector<int> Ans;
        while(Q.size())
            Q.pop();
        cin >> N;

        cin >> W;
        int index = 0;
        long long limit = ((W % 2) == 1 ? W / 2 + 1 : W / 2);
        REP(i, N){
            cin >> dataad;
            if(dataad >= limit && dataad <= W){
                index = i + 1;
            }
            Q.emplace(dataad, i);
        }
        if(index != 0){
            cout << "1\n" << index << "\n";
            continue;
        }
        while(Q.size() && Q.top().first > W){
            Q.pop();
        }
        if(Q.empty()){
            cout << "-1\n";
            continue;
        }
        long long cnt = 0;
        while(Q.size() && cnt < limit){
            cnt += Q.top().first;
            Ans.eb(Q.top().second);
            Q.pop();
        }
        if(cnt < limit || cnt > W){
            cout << "-1\n";
            continue;
        }
        sort(Ans.begin(), Ans.end());
        cout << Ans.size() << endl;
        for(auto u: Ans){
            cout << u + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}