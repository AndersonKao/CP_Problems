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
class Node{
public:
    int value;
    Node *next;
    Node *prev;
    Node(int a) : value(a) { next = prev = nullptr; }
};
    int a, b;
Node* construct(int N){
    Node *head = new Node(1);
    Node *prev = head;
    for (int i = 2; i <= N; i++){
        Node *newnod = new Node(i);
        newnod->prev = prev;
        prev->next = newnod;
        prev = newnod;
    }
    prev->next = head;
    head->prev = prev;
    return head;
}
struct dNode{
public:
    int x;
    int y;
    dNode *next;
    dNode *prev;
    dNode(int x1, int x2){
        x = x1,
        y = x2;
    }
};

int main(){
    cin >> N;
    int K;
    cin >> K;
    Node *head = construct(N);
    int M = N;
    Node *iter = head;
    dNode *head_1;
    dNode *iter_1;
    iter_1 = head_1 = nullptr;
    while (M > 0)
    {
        // cout << M << endl;
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        Node *tode = iter;
        iter = iter->next;
        // if(tode->value < 10000)
        // cout << "delete: " << tode->value << endl;
        if(M&1){
            // cout << "new dNode\n";
            a = tode->value;
            if(head_1 == nullptr){
                head_1 = new dNode(a, b);
                iter_1 = head_1;
            }
            else{
                dNode *newNode = new dNode(a, b);
                iter_1->next = newNode;
                newNode->prev = iter_1;
                iter_1 = newNode;
            }
        }else{
            b = tode->value;
        }
        // cout << "deleting\n";
        if(iter == tode)
        {
            delete tode;
            break;
        }
        delete tode;
        M--;
       
        for (int i = 0; i < K; i++)
        {
            iter = iter->next;
        }
        // cout << "fefe\n";
    }
    iter_1->next = head_1;
    head_1->prev = iter_1;
    M = N / 2;
    // for (int i = 0; i <= M; i++){
        // cout << i << ": ";
        // cout << iter_1->next->x << " " << iter_1->next->y << endl;
        // iter_1 = iter_1->next;
    // }
    iter_1 = head_1;
    while(M > 1){
        iter_1->prev->next = iter_1->next;
        iter_1->next->prev = iter_1->prev;
        dNode *tode = iter_1;
        iter_1 = iter_1->next;
        delete tode;
        for (int i = 0; i < K; i++)
        {
            iter_1 = iter_1->next;
        }
        M--;
    }
    // cout << iter->next->next->value << endl;
    if(iter_1->x < iter_1->y)
        cout << iter_1->x << " " << iter_1->y << endl;
    else
        cout << iter_1->y << " " << iter_1->x << endl;
    // if(x < y){
    //     cout << x << " " << y << endl;
    // }
    // else
    //     cout << y << " " << x << endl;
    return 0;
}