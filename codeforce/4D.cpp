// AC Sep/10/2020 14:35UTC+8
// remember to save memory by using short int to represent index number
#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
// #define LOCAL
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
struct file{
    pii sz;
    short int index;
    file(int w, int h, int index){
        sz.first = w;
        sz.second = h;
        this->index = index;
    }
};
vector<file> seq;
// int contain[5005];
vec<short int> put[5001];
short int pre[5001];
short int ans[5001];
bool cmp(file a, file b){
    if(a.sz.F != b.sz.F){
        return a.sz.F < b.sz.F;
    }
    return a.sz.S < b.sz.S;
}
bool putable(file source, file des)
{
    if(des.sz.first > source.sz.first && des.sz.second > source.sz.second)
        return true;
    return false;
}
int main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    int N;
    pii letter;
    cin >> N >> letter.first >> letter.second;
    int width, height;
    int eveNum = 0;
    for (int i = 0; i < N; i++){
        cin >> width >> height;
        if(width > letter.first && height > letter.second){
            seq.emplace_back(width, height, i + 1);
            eveNum++;
        }
    }
    if(seq.empty()){
        cout << "0\n";
        return 0;
    }
    sort(seq.begin(), seq.end(), cmp);
    #ifdef LOCAL
    for (int i = 0; i < eveNum; i++){
        cout << seq[i].sz.first << " " << seq[i].sz.second << "index: " << seq[i].index << "\n";
    }
    #endif
    for (int i = 0; i < eveNum; i++){
        for (int j = i - 1; j >= 0; j--){
            if(putable(seq[j], seq[i])){
                put[i].emplace_back(j);
            }
        }
    }
    for (int i = 0; i < eveNum; i++){
        if(put[i].empty()){
            pre[i] = -1;
            ans[i] = 1;
            continue;
        }
        for(auto j: put[i]){
            if(ans[j] + 1 > ans[i]){
                ans[i] = ans[j] + 1;
                pre[i] = j;
            }
        }
    }
    #ifdef LOCAL
    for (int i = 0; i < eveNum; i++){
        cout << ans[i] << " pre: " << pre[i] << '\n';
    }
    #endif
    int ansIndex;
    int maxUse = -1;
    for (int i = 0; i < eveNum; i++){
        if(ans[i] > maxUse){
            maxUse = ans[i];
            ansIndex = i;
        }
    }
    stack<int> st;
    cout << ans[ansIndex] << endl;
    while(pre[ansIndex] != -1){
        st.push(seq[ansIndex].index);
        ansIndex = pre[ansIndex];
    }
    st.push(seq[ansIndex].index);
    while(st.size()){
        cout << st.top();
        st.pop();
        cout << (st.empty() ? '\n' : ' ');
    }
    return 0;
}