// AC Mar/13/2021 15:55UTC+8
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
int T, N, k;
// map<char, int> M;
int M[27];
int need[27];
char originstr[100005];
char copystr[100005];
char ansstr[100005];
int char_to_int(char a){
    return a - 'a';
}
void init(){
    // M.clear();
    memset(M, 0, sizeof(M));
    memset(need, 0, sizeof(need));
    memset(originstr, 0, sizeof(originstr));
    memset(ansstr, 0, sizeof(ansstr));
    memset(copystr, 0, sizeof(copystr));

}
bool presolved(){

    for (int i = 0; i < 26; i++){
        if(need[i] > 0){
            return false;
        }
    }
    return true;
}
bool solved(int changing_index){
    int accum = 0;
    for (int i = 0; i < 26; i++){
        accum += need[i];
    }
    if(accum <= N - changing_index - 1){
        return true;
    }
    return false;
}
// #define TEST_NEED
void printNEED(){
        REP(i, 26)
            cout << char('a' + i) << ": " <<  need[i] << (i == 25 || i == 15 ? '\n' : ' ');
}
void indecrease(char ch, bool increase){
    int index = char_to_int(ch);
    if(increase){
        need[index]++;
        if(need[index] >= k)
            need[index] = 0;
    }else{
        need[index]--;
        if(need[index] < 0){
            need[index] = k - 1;
        }
    }
}
int main(){
    cin >> T;
    while(T--){
        init();
        cin >> N >> k;
        cin >> originstr;
        if(N % k != 0){
            cout << "-1\n";
            continue;
        }
        strcpy(copystr, originstr);
        REP(i, N){
            M[char_to_int(originstr[i])]++;
            if(M[char_to_int(originstr[i])] >= k){
                M[char_to_int(originstr[i])] -= k;
            }
        }
        REP(i, 26){
            need[i] = (k - M[i]) % k;
        }
        #ifdef TEST_NEED
        printNEED();
        #endif
        if(presolved()){
            cout << originstr << endl;
            continue;
        }
        int changing_index = N - 1;
        while(originstr[changing_index] == 'z'){
            changing_index--;
            indecrease('z', true);
        }
        do{
            indecrease(originstr[changing_index], true);
            originstr[changing_index]++;
            indecrease(originstr[changing_index], false);
            if(solved(changing_index))
                break;
            else{
                while(originstr[changing_index] == 'z' && changing_index >= 0){
                    indecrease('z', true);
                    changing_index--;
                    #ifdef TEST_NEED
                    cout << "ci: " << changing_index << endl;
                    cout << originstr << endl;
                    #endif
                }
            }
        } while (changing_index >= 0);
        #ifdef TEST_NEED
        #endif
        if(changing_index < 0){
            REP(i, N){
                cout << 'z';
            }
            cout << endl;
        }else{
            int index = char_to_int('z');
            for (int i = N - 1; i > changing_index; i--)
            {
                while(need[index] == 0 && index >= 0){
                    index--;
                }
                if(index < 0)
                    originstr[i] = 'a';
                else{
                    originstr[i] = 'a' + index;
                    need[index]--;

                }
            // cout <<  index << " & " <<  i << ": " <<  originstr << endl;
            }
            cout << originstr << endl;
        }
    }
    return 0;
}