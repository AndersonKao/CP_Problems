// 2021-08-22 15:45:47
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
void init(){

}
int seq[200005];
int f[200005]; // longset start at i;
int g[200005]; // longest end in i;
/*input
2
9
5 3 4 9 2 8 6 7 1
7
1 2 3 10 4 5 6
*/
int main(){
    cin >> T;
    while(T--){
        int ANS = 0;
        memset(seq, 0, sizeof(seq));
        cin >> N;
        REP(i, N){
            cin >> seq[i];
        }
        int Fa, Ga;
        Ga = 0;
        for (int i = 0; i < N; i++){
            g[i] = ++Ga;
            if(i + 1 < N && seq[i+1] <= seq[i]){
                Ga = 0;
            }
        }
        Fa = 0;
        for (int i = N - 1; i >= 0; i--){
            f[i] = ++Fa;
            if(i - 1 >= 0 && seq[i-1] >= seq[i]){
                Fa = 0;
            }
        }
        /*
        REP(i, N)
            cout << g[i] << (i == N-1 ? '\n' : ' ');
        REP(i, N)
            cout << f[i] << (i == N-1 ? '\n' : ' ');
        */
        set<pii> Sat;
        ANS = f[0];
        Sat.emplace(seq[0], g[0]);
        for (int i = 1; i < N; i++){
            /*
            printf("processing %d\n", seq[i]);
            printf("In Sat: ");
            for(auto itall: Sat){
                printf("(%d, %d) ", itall.first, itall.second);
            }
            printf("\n");
            */
            set<pii>::iterator it = Sat.lower_bound(pii(seq[i], g[i]));
            if(it != Sat.begin())
            {
                it--;
             //   printf("combining sat: %d and seq: %d\n", it->first, seq[i]);
                    ANS = (it->first < seq[i] ? max(ANS, it->second + f[i]) : ANS);
             //       printf("ANS now equal to %d\n", ANS);
                if (it->second <= g[i]){
                    set<pii>::iterator deit = Sat.lower_bound(pii(seq[i],0));
                    while(deit != Sat.end() && seq[i] <= deit->first && g[i] > deit->second){
                        set<pii>::iterator tode = deit;
                        deit++;
                        Sat.erase(tode);
                    }
                    Sat.emplace(seq[i], g[i]);
                }
            }else{
                set<pii>::iterator deit = Sat.lower_bound(pii(seq[i], 0));

                while(deit != Sat.end() && seq[i] <= deit->first && g[i] > deit->second){
                    set<pii>::iterator tode = deit;
                    deit++;
                    Sat.erase(tode);
                }
                Sat.emplace(seq[i], g[i]);
            }
        }
        printf("%d\n", ANS);
    }
    return 0;
}
