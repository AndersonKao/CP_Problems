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
void solve();
class Node{
public:
    int my_index;
    int parent;
    int LChild, RChild;
    Node(){
        my_index = LChild = RChild = 0;
    }
    void reset(){
        my_index = LChild = RChild = 0;
        parent = 0;
    }
};
vector<int> Ans;
Node seq[105];

void addRight(int root, int child){
    // cout << "add " << child << " to " << root << "'s Right.\n";
   
    seq[root].RChild = child;
    seq[child].parent = root;
}
void addLeft(int root, int child){
    // cout << "add " << child << " to " << root << "'s Left.\n";
    seq[root].LChild = child;
    seq[child].parent = root;
}
void askQuestion(int a, int b, int c){
    cout << a << " " << b << " " << c << "\n";
}
void resetto(int &root, int &Asking, int x, int y){
    root = x;
    Asking = y;
}
void printAns(int root){
    if(seq[root].LChild != 0){
        printAns(seq[root].LChild);
    }
    Ans.emplace_back(root);
    if(seq[root].RChild != 0){
        printAns(seq[root].RChild);
    }
}
int main(){
    cin >> T;
    cin >> N;
    int Q;
    cin >> Q;
    while(T--){
        Ans.clear();
        REP(i, 100){
            seq[i].reset();
        } 
        solve();
        for(auto it: Ans){
            cout << it << " ";
        }
        cout << endl;
        int Outcome;
        cin >> Outcome;
        if(Outcome != 1){
            // cout << "Wrong!!!\n";
            break;
        }
        // REP1(i, N){
        //     cout << i << ": L's " << seq[i].LChild << " R's " << seq[i].RChild << endl;
        // }
    }
    cout.flush();
    // cerr << "debug message" << endl;
    return 0;
}

void solve(){
    // cout << "1 2 3\n";
    askQuestion(1, 2, 3);
    int mediam;
    cin >> mediam;
    int root = mediam;
    switch (mediam)
    {
    case 1:
        /* code */
        addLeft(mediam, 2);
        addRight(mediam, 3);
        break;
    case 2:
        addLeft(mediam, 1);
        addRight(mediam, 3);
        break;
    case 3:
        addLeft(mediam, 1);
        addRight(mediam, 2);
        break;
    default:
        break;
    }
    int curAnsking = 4;
    int curNode = root;
    int L_mediam, R_mediam;
    while (curAnsking <= N)
    {
        // cout << "curNode: " << curNode << " nowask: " << curAnsking << endl;
        if(seq[curNode].LChild != 0 && seq[curNode].RChild == 0){
            askQuestion(curNode, seq[curNode].LChild, curAnsking);
            cin >> mediam;
            if(mediam == curNode){
                addRight(curNode, curAnsking);
            }else if(mediam == seq[curNode].LChild){
                if(seq[seq[curNode].LChild].LChild != 0){
                    curNode = seq[curNode].LChild;
                    continue;
                }
                addLeft(seq[curNode].LChild, curAnsking);
            }else if(mediam == curAnsking){
                if(seq[seq[curNode].LChild].RChild != 0){
                    curNode = seq[curNode].LChild;
                    continue;
                }
                addRight(seq[curNode].LChild, curAnsking);
            }else{
                cout << "ERROR\n";
            }
            // curNode = root;
            resetto(curNode, curAnsking, root, curAnsking + 1);
            continue;
        }else if(seq[curNode].LChild == 0 && seq[curNode].RChild != 0){
            askQuestion(curNode, seq[curNode].RChild, curAnsking);
            cin >> mediam;
            if(mediam == curNode){
                addLeft(curNode, curAnsking);
            }else if(mediam == seq[curNode].RChild){
                if(seq[seq[curNode].RChild].RChild != 0){
                    curNode = seq[curNode].RChild;
                    continue;
                }
                addRight(seq[curNode].RChild, curAnsking);
            }else if(mediam == curAnsking){
                if(seq[seq[curNode].RChild].LChild != 0){
                    curNode = seq[curNode].RChild;
                    continue;
                }
                addLeft(seq[curNode].RChild, curAnsking);
            }else{
                cout << "ERROR\n";
            }
            resetto(curNode, curAnsking, root, curAnsking + 1);
            continue;
        }else if(seq[curNode].LChild == 0 && seq[curNode].RChild == 0){
            if(curNode < curAnsking){
                addRight(curNode, curAnsking);
            }else{
                addLeft(curNode, curAnsking);
            }
            resetto(curNode, curAnsking, root, curAnsking + 1);
            continue;

        }

        askQuestion(curNode, seq[curNode].LChild, curAnsking);
        cin >> L_mediam;
        askQuestion(curNode, seq[curNode].RChild, curAnsking);
        cin >> R_mediam;
        if(L_mediam == curNode){
            if(R_mediam == seq[curNode].RChild){
                if(seq[seq[curNode].RChild].RChild == 0){
                    addRight(seq[curNode].RChild, curAnsking);
                    resetto(curNode, curAnsking, root, curAnsking + 1);
                    // seq[seq[curNode].RChild].RChild = curAnsking;
                }else{
                    curNode = seq[curNode].RChild;
                }
            }else if(R_mediam == curAnsking){
                if(seq[seq[curNode].RChild].LChild == 0){
                    addLeft(seq[curNode].RChild, curAnsking);
                    resetto(curNode, curAnsking, root, curAnsking + 1);
                    // seq[seq[curNode].RChild].LChild = curAnsking;
                }else{
                    curNode = seq[curNode].RChild;
                }
            }else{
                cout << "Error occur\n";
            }
        }else if(L_mediam == seq[curNode].LChild){
            if(seq[seq[curNode].LChild].LChild == 0){
                addLeft(seq[curNode].LChild, curAnsking);
                resetto(curNode, curAnsking, root, curAnsking + 1);
                // seq[seq[curNode].LChild].LChild = curAnsking;
            }else{
                curNode = seq[curNode].LChild;
            }
        }
        else if(L_mediam == curAnsking){
            if(seq[seq[curNode].LChild].RChild == 0){
                addRight(seq[curNode].LChild, curAnsking);
                resetto(curNode, curAnsking, root, curAnsking + 1);
                // seq[seq[curNode].LChild].RChild = curAnsking;
            }else{
                curNode = seq[curNode].LChild;
            }
        }else{
            cout << "Error occur\n";
        }
    }
    // cout << curAnsking << " " << N << endl;
    printAns(root);
}

/*
2 10 600
1 2 3
1
1 2 4
1
1 3 4
4
1 2 5
1
1 3 5
3
1 2 6
1
1 3 6
3
3 4 6
3
3 5 6
5
1 2 7
7
1 3 7
1
1 2 8
2
1 3 8
1
1 2 9
1
1 3 9
3
3 4 9
3
3 5 9
5
5 6 9
6
1 2 10
1
1 3 10
3
3 4 10
3
3 5 10
5
5 6 10
6
8 2 7 1 4 3 5 6 10

2 10 100
1 2 3
3
3 1 4
3
3 2 4
2
3 1 5
3
3 2 5
5
3 1 6
3
3 2 6
2
2 5 6
2
2 4 6
4
3 1 7
3
3 2 7
7
2 5 7
7
2 4 7
2
3 1 8
3
3 2 8
2
2 5 8
2
2 4 8
4
4 6 8
6
3 1 9
3
3 2 9
9
2 5 9
9
2 4 9
2
5 7 9
7
3 1 10
3
3 2 10
2
2 5 10
2
2 4 10
4
4 6 10
6
6 8 10
8

*/