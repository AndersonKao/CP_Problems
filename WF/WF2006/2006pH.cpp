#include <bits/stdc++.h>
using namespace std;


template <typename T>
using vec = vector<T>;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define ef emplace_front
#define debug(x) cout << #x << ":= " << x << endl;
#define al(x) x.begin(), x.end()
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int UNFLIP = 0;
const int FLIPPED = 1;
vec<vec<vec<int>>> getRealDirec(2, vec<vec<int>>(4));
struct block
{
    int flipped = false;
    int up = UP;
    int val;
    block() : val(-1){};
    block(int v) : val(v){};
    block(const block &b) : flipped(b.flipped), up(b.up), val(b.val){};

    void turndown(){
        flipped = !flipped;
        if(up == UP){
            up = DOWN;
        }
        else if(up == DOWN){
            up = UP;
        }
    }
    void turnup(){
        turndown();
    }
    void turnright()
    {
        flipped = !flipped;
        if(up == RIGHT){
            up = LEFT;
        }
        else if(up == LEFT){
            up = RIGHT;
        }
    }
    void turnleft(){
        turnright();
    };

    friend ostream &operator<<(ostream &os, const block &b);
};
ostream &operator<<(ostream &os, const block &b)
{
    return (os << "id: "<< b.val << (b.flipped ? " flipped" : " unflip") << " " << b.up);
}
void shift(vec<int>& V){
    int u = V[UP];
    V[UP] = V[LEFT];
    V[LEFT] = V[DOWN];
    V[DOWN] = V[RIGHT];
    V[RIGHT] = u;
}
void computeRealDirec(){
        // return the direction on original paper base on the folded state and folded direction;
    for (int flipped = 0; flipped < 2; flipped++){
        for (int direc= 0; direc< 4; direc++){
            vec<int> V(4);
            iota(al(V), 0);
            if(flipped){
                swap(V[RIGHT], V[LEFT]);
            }
            int round = 0;
            if(direc == RIGHT)
                round = 1;
            else if(direc == DOWN)
                round = 2;
            else if(direc == LEFT)
                round = 3;
            REP(i, round){
                shift(V);
            }
            getRealDirec[flipped][direc] = V;
        }
    }
}


int Clen, Rlen;
vec<vec<list<block>>> G;
vec<list<int>> Real2Line[2]; // 0 for row-major, 1 for col-major.
vec<int> Line2Real[2];       // 0 for row-major, 1 for col-major.
int N, K;

vec<vec<list<block>>> moveit(int C, int direc){
    int type = direc / 2; // 01 UpDown, 23 LeftRight -> 0 UpDown, 1 Left Right
    int type2 = direc & 1; // 0 for Up Left, 1 for Down Right 
    vec<list<int>> &R2L = Real2Line[type];
    vec<int> &L2R = Line2Real[type];
    int nClen = Clen, nRlen = Rlen;
    int Real = L2R[C];

    if (type)
        nClen = max(Clen - (Real + 1), Real + 1);
    else
        nRlen = max(Rlen - (Real + 1), Real + 1);
    vec<vec<list<block>>> newG(nRlen, vec<list<block>>(nClen));
    int cbase = 0;
    int rbase = 0;
    if(type == 0)
        rbase = Real + 1;
    else
        cbase = Real + 1;
    #ifdef Dmoveit
    debug(Real);
    debug(nRlen);
    debug(nClen);
    debug(rbase);
    debug(cbase);
    #endif
    if (direc == UP)
    {
        for (int ci = 0; ci < nClen; ci++){
            for (int ri = 0; ri < rbase; ri++){
                #ifdef Dup
                debug(nRlen - (Real - ri));
                #endif
                list<block> &lst = newG[nRlen - (rbase - ri)][ci];
                lst = G[ri][ci];
            }
            for (int ri = rbase; ri < Rlen; ri++){
                for(block& b: G[ri][ci]){
                    b.turnup();
                }
                list<block> &lst = newG[nRlen - (ri- Real)][ci];
                lst.insert(lst.begin(), G[ri][ci].rbegin(), G[ri][ci].rend());
            }
        }
    }
    else if(direc == DOWN){
        for (int ci = 0; ci < nClen; ci++){
            for (int ri = rbase; ri < Rlen; ri++){
                newG[ri - rbase][ci] = G[ri][ci];
            }
            for (int ri = Real; ri >= 0; ri--){
                for(block& b: G[ri][ci]){
                    b.turndown();
                }
                list<block> &lst = newG[Real - ri][ci];
                lst.insert(lst.begin(), G[ri][ci].rbegin(), G[ri][ci].rend());
            }
        }
    }
    else if(direc == LEFT){
        for (int ri = 0; ri < nRlen; ri++){
            for (int ci = 0; ci < cbase; ci++){
                newG[ri][nClen - (cbase- ci)] = G[ri][ci];
            }
            for (int ci = cbase; ci < Clen; ci++){
                for(block& b: G[ri][ci]){
                    b.turnleft();
                }
                list<block> &lst = newG[ri][nClen - (ci - Real)];
                lst.insert(lst.begin(), G[ri][ci].rbegin(), G[ri][ci].rend());
            }
        }
    }
    else if (direc == RIGHT)
    {
        for (int ri = 0; ri < nRlen; ri++){
            for (int ci = cbase; ci < Clen; ci++){
                newG[ri][ci - cbase] = G[ri][ ci];
                #ifdef Dright
                cout << "copyingr right\n";
                for (block &b : G[ri][ci])
                {
                    cout << b << endl;
                }
                #endif
            }
            for (int ci = Real; ci >= 0; ci--){
                #ifdef Dright
                cout << "turning right:\n";
                #endif
                for (block &b : G[ri][ci])
                {
                    b.turnright();
                    #ifdef Dright
                    cout << b << endl;
                    #endif
                }
                list<block> &lst = newG[ri][Real - ci];
                #ifdef Dright
                cout << "accepting:\n";
                for (block &b : lst)
                    cout << b << endl;
                #endif
                lst.insert(lst.begin(), G[ri][ci].rbegin(), G[ri][ci].rend());
            }
        }

    }
    for (int c = 0; c < R2L.size(); c++){
        for(int& Lid: R2L[c]){
            int dis = abs(c - Real);
            if (type2 == 1)
            {
                L2R[Lid] = (dis - 1);
            }
            else
            {
                if(type == 1)
                    L2R[Lid] = (nClen - dis - 1);
                else
                    L2R[Lid] = (nRlen - dis - 1);
            }
        }
    }
    R2L.clear();
    if(type == 1)
        R2L.resize(nClen);
    else
        R2L.resize(nRlen);
    #ifdef DL2R
    cout << type << "'s L2R :\n";
    for (int i = 0; i < N; i++)
    {
        cout << i << ": " << L2R[i] << endl;
    }
    #endif
    for (int i = 0; i < N; i++)
    {
        int &c = L2R[i];
        if(c < 0 || c >= R2L.size())
            continue;
        R2L[c].eb(i);
    }
    Clen = nClen, Rlen = nRlen;
    return newG;
}
void pG(){
    int r = 0;
    int c = 0;
    cout << "Printing G:\n";
    for (vec<list<block>> &e : G)
    {
        c = 0;
        for (list<block> &lst : e)
        {
            debug(r);
            debug(c);
            for (block &b : lst)
            {
                cout << b<< endl;
            }
            c++;
        }
        r++;
    }
}
int blockNum;
inline int getNeighbor(int x, int direc)
{
    int res = -1;
    int Len = N + 1;
    if (direc == UP)
        res = x - Len;
    else if(direc == DOWN)
        res = x + Len;
    else if(direc == RIGHT){
        if(x % Len != 0)
            res = x + 1;
    }
    else if(direc == LEFT){
        if(x % Len != 1){
            res = x - 1;
        }
    }
    if(res <= 0 || res > blockNum){
        return -1;
    }
    return res;
}

int main()
{
    computeRealDirec();
    int caseN = 1;
    while (cin >> N >> K)
    {
        if(N == 0 && K == 0)
            break;
        Clen = Rlen = N + 1;
        blockNum= (N + 1) * (N + 1);
        G.clear();
        G.resize(Rlen, vec<list<block>>(Clen));
        REP(i, Rlen){
            REP(j, Clen){
                G[i][j].ef(block(i * Clen + j + 1));
            }
        }

        REP(i, 2){
            Real2Line[i].resize(N);
            Line2Real[i].clear();
            Line2Real[i].resize(N);
        }
        REP(j, 2){
            REP(i, N){
                Line2Real[j][i] = i;
            }
            REP(i, N){
                Real2Line[j][i].ef(i);
            }
        }
        #ifdef Dg
        pG();
        #endif

        REP(i, K){
            int C;
            char ch;
            cin >> C >> ch;
            int Direc = -1;
            #ifdef  Dop
            debug(C);
            debug(ch);
            #endif
            if (ch == 'R')
                Direc = RIGHT;
            else if(ch == 'L')
                Direc = LEFT;
            else if(ch == 'U')
                Direc = UP;
            else if(ch == 'D')
                Direc = DOWN;
            G = moveit(C - 1, Direc);
            #ifdef Dg
            pG();
            #endif
        }
        #ifdef Dg
        debug(G.size());
        debug(G[0].size());
        pG();
        #endif
        int ans = 0;

        list<block> &lst = G[0][0];
        for (int di = 0; di < 4; di++)
        {
            #ifdef Dunpack
            debug(di);
            cout << "----------------\n";
            #endif
            vec<bool> visited(blockNum + 1, false);
            list<block>::iterator it = lst.begin();
            while(it != lst.end()){
                int RealDirec = getRealDirec[it->flipped][it->up][di];
                int target = getNeighbor(it->val, RealDirec);
                #ifdef Dunpack
                cout << *it << endl;
                debug(RealDirec);
                debug(target);
                #endif
                visited[it->val] = true;
                if (target == -1 || visited[target])
                {
                    it++;
                    ans++;
                }
                else{
                    while(it != lst.end() && it->val != target){
                        visited[it->val] = true;
                        it++;
                    }
                }
            }
            ans--;
            #ifdef Dans
            debug(ans);
            #endif
        }

            cout << "Case " << caseN++ << ": " << ans << " pockets\n";
    }

    return 0;
}