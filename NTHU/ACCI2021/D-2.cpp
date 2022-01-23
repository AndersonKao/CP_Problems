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

#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 500005
// lazy_tag put in sum version
struct Node{
    long long sum;
    long long lazy_tag;
    int size;
};
short dataseq[MAXN];
Node seq[MAXN * 4 + 5];
void build(int l, int r, int L, int R, int index);
void modify(int l, int r, int L, int R, int index, long long Add);
long long Query(int l, int r, int L, int R, int index);
void pull(int index);
void push(int index);

void pull(int index){
    seq[index].sum = seq[IL(index)].sum + seq[IR(index)].sum;
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}
void push(int index){
    seq[IL(index)].lazy_tag += seq[index].lazy_tag;
    seq[IL(index)].sum += seq[index].lazy_tag * seq[IL(index)].size;
    seq[IR(index)].lazy_tag += seq[index].lazy_tag;
    seq[IR(index)].sum += seq[index].lazy_tag * seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}

void build(int l, int r, int L, int R, int index){
    if(l == r){
        seq[index].sum = dataseq[l];
        seq[index].size = 1;
        seq[index].lazy_tag = 0;
        return; 
    }
    int M = (L + R) / 2;
    build(l, M, L, M, IL(index));
    build(M + 1, r, M + 1, R, IR(index));
    pull(index);
}

void modify(int l, int r, int L, int R, int index, long long Add){
    if(l == L && r == R){
        seq[index].lazy_tag += Add;
        seq[index].sum += Add * seq[index].size;
        return;
    }
    push(index);
    int M = (L + R) / 2;

    if(r <= M){
        modify(l, r, L, M, IL(index), Add);
    }else if(l > M){
        modify(l, r, M + 1, R, IR(index), Add);
    }else{
        modify(l, M, L, M, IL(index), Add);
        modify(M + 1, r, M + 1, R, IR(index), Add);
    }
    pull(index);
}

long long Query(int l, int r, int L, int R, int index){
    if(l == L && r == R){
        return seq[index].sum;
    }
    int M = (L + R) / 2;
    push(index);
    pull(index);
    if(r <= M){
        return Query(l, r, L, M, IL(index));
    }else if(l > M){
        return Query(l, r, M + 1, R, IR(index));
    }else{
        return Query(l, M, L, M, IL(index)) + 
        Query(M + 1, r, M + 1, R, IR(index));
    }

}
int main(){
     cin >> N >> Q;
    memset(parent, 0, sizeof(parent));
    memset(modified, 0, sizeof(modified));
    memset(val, 0, sizeof(val));
    memset(multe, 0, sizeof(multe));
    for (int i = 0; i < N; i++){
        cin >> val[i+1];
    }
    int from, to;
    for (int i = 0; i < N - 1; i++){
        cin >> from >> to;
        AddEdge(from, to);
    }
    rootTheTree(1);
    int operation, u, x;
    while(Q--){
        // cout << "-----------\n";
        cin >> operation;
        if(operation == 1){
            cin >> u;
            cout << askMul(u) << endl;
        }else{
            cin >> u >> x;
            renewVal(u, x);
        }
        // printall();
    }
    return 0;
}