// AC Sep/11/2020 15:26UTC+8
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
template <typename T>
using Prior = priority_queue<T>;
template <typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define REP(i, n) for (int i = 0; i < n; i++)
#define REP1(i, n) for (int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define reseq(seq) memset(seq, 0, sizeof(seq));
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v)                 \
    cout << " > " << #v << ": "; \
    for (auto i : v)             \
        cout << i << ' ';        \
    cout << endl;
#define devec2(v)                 \
    cout << " > " << #v << ":\n"; \
    for (auto i : v)              \
    {                             \
        for (auto k : i)          \
            cout << ' ' << k;     \
        cout << endl;             \
    }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4 * 1e18;
const int MOD = 1e9 + 7;

ll &pmod(ll &a, ll b)
{
    a = (a + b) % MOD;
    return a;
}
ll &pmod(ll &a, ll b, ll c)
{
    a = (a + b) % c;
    return a;
}
ll &mmod(ll &a, ll b)
{
    a = (a - b + MOD) % MOD;
    return a;
}
ll &mmod(ll &a, ll b, ll c)
{
    a = (a - b + c) % c;
    return a;
}
ll &tmod(ll &a, ll b)
{
    a = (a * b) % MOD;
    return a;
}
ll mul(ll a, ll b) { return (a * b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a * b) % c; }
ll POW(ll a, ll b)
{
    ll res = 1;
    do
    {
        if (b % 2)
            tmod(res, a);
        tmod(a, a);
    } while (b >>= 1);
    return res;
}
ll FAC(ll a)
{
    ll res = 1;
    REP1(i, a)
    tmod(res, i);
    return res;
}

template <typename T1, typename T2>
ofstream operator<<(ofstream &out, pair<T1, T2> a)
{
    cout << a.F << ' ' << a.S;
    return out;
}

int gcd(int a, int b)
{
    if (a < b)
    {
        swap(a, b);
    }
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}
// #define LOCAL
 int seq[1005];
 int c[1005];
 int b[1005];
 int ans[1005];
bool used[1005];    
int main()
{
    #ifdef LOCAL
    freopen("input2.txt", "r", stdin);
    #endif
    int T;
    cin >> T;
    REP(i, T)
    {
        memset(seq, 0, sizeof(seq));
        reseq(c);
        reseq(b);
        reseq(ans);
        reseq(used);
        int N;
        cin >> N;
        REP1(i, N)
        {
            cin >> seq[i];
        }
        #ifdef LOCAL
        // cout << "test " << i << endl;
        // REP1(i, N){
        //     debug(seq[i]);
        // }
        #endif
        c[0] = 0;
        for(int i = 1; i <= N; i++){
             int maxindex;
             int maxc = 0;
            for(int j = 1; j <= N; j++){
                if(used[j])
                    continue;
                
                int Gcd = gcd(seq[j], c[i - 1]);
                // debug(i);
                // debug(j);
                // debug(seq[j]);
                // debug(c[i - 1]);
                // debug(Gcd);

                if(maxc < Gcd){
                    maxindex = j;
                    maxc = Gcd;
                }
            }
            // debug(i);
            // debug(maxc);
            // debug(maxindex);
            used[maxindex] = true;
            c[i] = maxc;
            ans[i] = seq[maxindex];
        }
        #ifdef LOCAL
        // cout << "test C" << endl;
        // REP1(i, N){
        //     debug(c[i]);
        // }
        #endif
        REP1(i, N){
            cout << ans[i] << (i == N ? '\n' : ' ');
        }
    }
    return 0;
}