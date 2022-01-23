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
int arr[1005];
int main(){
    cin >> T;
    int C;
    for(int case_i = 1; case_i <= T; case_i++){
        cin >> N;
        cin >> C;
        cout << "Case #" << case_i << ": ";
        
        int max_Ans = ((1 + N) * N) / 2;
        if(C >= max_Ans || C < N - 1){
            cout << "IMPOSSIBLE\n";
            continue;
        }
        memset(arr, 0, sizeof(arr));
        int index_odd = N, index_even = 1;
        for (int i = 1; i <= N; i++){
            // if(i & 1){
            //     arr[i] = index_odd00
            // }
            arr[i] = i;
            // arr[((i & 1 == 1) ? index_odd-- : index_even++)] = i;
        }
        // REP1(i, N){
        //     cout << arr[i] << " ";
        // }
        // cout << endl;
        C = C - (N - 1);
        bool round = false;
        int L_bound = 1, R_bound = N;
        for (int i = 1; i <= N; i++){
            int bene = N - i ;
            // if(C == 0)
            // cout << "bene: " << bene << endl;
            // REP1(i, N)
            // {
            //     cout << arr[i] << " ";
            // }
            // cout << endl
            // << L_bound << " " << R_bound << endl;
            
            //     break;
            if(C < bene){
                // int index = L_bound;
                if(round){
                    R_bound--;
                }else{
                    L_bound++;
                }
                continue;
            }
            C -= bene;
            int index = R_bound;
            for (int j = L_bound; j <= (L_bound + R_bound)/2; j++){
                swap(arr[j], arr[index--]);
            }
            if(!round){
                R_bound--;
            }else{
                L_bound++;
            }
            round = !round;
            
            // continue;
            // L_bound--;
        }
            REP1(i, N)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
    }
    return 0;
}

/*
1 2 3 4 5 6 7 
need 6
7 6 5 4 3 2 1
same
need 4
same
need 3
N,C = 4, 9
6 = 3 + 2 + 1
2
---->

need 6
1 2 3 4
need 3
4 3 2 1
need 1
2 3 4 1
need 1
3 2 4 1 
what if
1 4 2 3 get 4
1 2 4 3 get 6
1 2 3 4 get 8




same 
need 1

suppose N,C = 4, 8
need 5
1 2 3 4
need 2
4 3 2 1
need o
2 3 4 1
2
3 4 5 2 1
1 2 5 4 3 get 5
1 2 5 4 3 get 6
1 2 3 4 5 get 9
1 2 3 4 5 get 10

4 3 2 1 5 6 
1 2 3 4 5 6  get 4


need 8
1 4 5 6 3 2
need 2
1 2 3 6 5 4


*/