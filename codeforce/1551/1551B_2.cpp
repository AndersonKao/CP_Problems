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
int T, N, C;
int seq[200005];
int used[200005];
map<int, int> M;
map<int, int> M2;
void init(){

}
int main(){
    cin >> T;
    int cnt = 0;
    while(T--){
        cin >> N >> C;
        M.clear();
        M2.clear();
        vector<pair<int, int>> V;
        for (int i = 0; i < N; i++)
        {
            cin >> seq[i];
            M[seq[i]]++;
            used[i] = 0;
        }
        for(auto it: M){
            V.emplace_back(it.second, it.first);
        }
        sort(V.rbegin(), V.rend());
            M.clear();
        int index = 0;
        for(auto it: V){
            M2[it.second] = index;
            M[index++] = it.first;
            cout << it.second << " :-> " << index - 1 << endl;
        
        }
        while (true)
        {
            cnt = 0;
            for (auto it2 = M.begin(); it2 != M.end();)
            {
                if(used[it2->first] >= C || it2->second == 0){
                    int tod = it2->first;
                    it2++;
                    M.erase(tod);
                    continue;
                }
                cout << "checking: " << it2->first << endl;
                it2->second--;
                cnt++;
                used[it2->first]++;
                if(cnt == C)
                    break;
                it2++;
                
            }
            cout << "endcheck\n";
            if(cnt != C)
                break;
        }
        for (int i = 0; i < N; i++){
            int real = M2[seq[i]];
            if(used[real] == 0){
                printf("0");
            }else{
                cout << used[real];
                used[real]--;
            }
            printf((i == N - 1 ? "\n" : " "));
        }
    }
    return 0;
}