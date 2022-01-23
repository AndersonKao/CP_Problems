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
// int seq1[2000005]
void init(){

}
char ansUp[200005], ansDw[200005];
int main(){
    cin >> T;
        while (T--)
        {
            memset(ansDw, 0, N * sizeof(char));
            
            string str;
            cin >> N;
            ansUp[N] = ansDw[N] = '\0';
            for (int i = 0; i < N; i++){
                ansUp[i] = (((i & 1) == 0) ? '(' : ')');
            }
            cin >> str;
            // cout << str;
            // cout << ansUp << endl;
            for (int i = 0; i < N; i++){
                if(str[i] == '1')
                    ansDw[i] = ansUp[i];
                else{
                    if(ansUp[i] == '('){
                        ansDw[i] = ')';
                    }else{
                        ansDw[i] = '(';
                    }
                }
            }
            // cout << "here\n";
            stack<int> St;
           
            for (int i = 0; i < N; i++)
            {
                if(ansDw[i] == '('){
                    St.push(1);
                }
                else{
                    if(St.empty()){
                        cout << "NO\n";
                        break;
                    }
                    St.pop();
                }
                if(i == N-1){
                    if(St.empty()){
                        cout << "YES\n";
                        cout << ansUp << '\n'
                            << ansDw << '\n';
                    }else{
                        cout << "NO\n";
                    }
                }
            }
            cout.flush();
        }
    return 0;

}
/*

00
2
10
2
01
2
11
4
0000
4
1000
4
0100
4
1100
4
0010
4
1010
4
0110
4
1110
4
0001
4
1001
4
0101
4
1101
4
0011
4
1011
4
0111
4
1111
6
000000
6
100000
6
010000
6
110000
6
001000
6
101000
6
011000
6
111000
6
000100
6
100100
6
010100
6
110100
6
001100
6
101100
6
011100
6
111100
6
000010
6
100010
6
010010
6
110010
6
001010
6
101010
6
011010
6
111010
6
000110
6
100110
6
010110
6
110110
6
001110
6
101110
*/