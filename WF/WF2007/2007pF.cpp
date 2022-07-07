// AC 2022-07-07 20:16:34
#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define eb emplace_back
#define al(x) x.begin(), x.end()
template <typename T>
using vec = vector<T>;
using pii = pair<int, int>;
const int NORMAL = -1;
// HOLE = 0 ~ W-1;
// FILLED = W
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
using ll = long long;
const ll MAXSTEP = numeric_limits<ll>::max();
int N, M, W;
ll ans;
bool solved;
vec<pii> base;
vec<vec<int>> table;
vec<vec<vec<bool>>> iswall;
struct VectorHash {
    size_t operator()(const std::vector<pii>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (const pii& i : v) {
            seed ^= hasher(i.F) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= hasher(i.S) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};
unordered_set<vec<pii>, VectorHash> visited;

auto leftcmp = [](pair<pii, int> &a, pair<pii, int> &b)
{
    if(a.F.S != b.F.S)
    {
        return (a.F.S < b.F.S);
    }
    return (a.F.F < b.F.F);
};
auto rightcmp = [](pair<pii, int> &a, pair<pii, int> &b)
{
    if(a.F.S != b.F.S)
    {
        return (a.F.S > b.F.S);
    }
    return (a.F.F < b.F.F);
};
auto upcmp = [](pair<pii, int> &a, pair<pii, int> &b)
{
    if(a.F.F != b.F.F)
    {
        return (a.F.F < b.F.F);
    }
    return (a.F.S < b.F.S);
};
auto downcmp = [](pair<pii, int> &a, pair<pii, int> &b)
{
    if(a.F.F != b.F.F)
    {
        return (a.F.F > b.F.F);
    }
    return (a.F.S < b.F.S);
};
bool check(vec<pii>& cur){
    for(pii&e: cur){
        if(e.F != -1)
            return false;
    }
    return true;
}
void pit(vec<pii>& V){
    vec<vec<char>> Si(N, vec<char>(N, ' '));
    int i = 0;
    for (pii &e : V)
    {
  //      cout << "(" << e.F << ", " << e.S << "), ";
        if(e.F == -1)
            continue;
        Si[e.F][e.S] = ('0' + i++);
    }
    REP(i, N){
        REP(j, N){
            cout << Si[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void simulate()
{
    queue<tuple<vec<pii>, int, int>> Q;
    visited.emplace(base);
    Q.emplace(base,0, 0);
    while(Q.empty() == false) {
        int step;
        vec<pii> cur;
        int filled;
        tie(cur, step, filled) = Q.front();
        Q.pop();
        #ifdef Dsimu
        cout << "pickup: \n";
        pit(cur);
        #endif
        if (filled == ((1 << M) - 1))
        {
            ans = step;
            break;
        }
        vec<pair<pii, int>> tomove;
        vec<pii> next(cur.size());
        vec<vec<bool>> occupy(N, vec<bool>(N, false));
        bool moveit = false;
        int newfilled;
        for (int i = 0; i < cur.size(); i++)
        {
            tomove.eb(cur[i], i);
        }
        // going left
        for (int j = 0; j < 4; j++){
            pii direc;
            switch (j)
            {
            case UP:
                sort(al(tomove), upcmp);
                direc = {-1, 0};
                break;
            case DOWN:
                sort(al(tomove), downcmp);
                direc = {1, 0};
                break;
            case RIGHT:
                sort(al(tomove), rightcmp);
                direc = {0, 1};
                break;
            case LEFT:
                sort(al(tomove), leftcmp);
                direc = {0, -1};
                break;

            default:
                break;
            }
            moveit = true;
            newfilled = filled;
            fill(al(occupy), vec<bool>(N, false));
            for (pair<pii, int> &e : tomove)
            {
                int i;
                pii pos;
                tie(pos, i) = e;
                if (pos.F == -1)
                {
                    next[i].F = next[i].S = -1;
                    continue;
                }
                next[i] = cur[i];
                pii nt = {next[i].F + direc.F, next[i].S + direc.S};
                while (nt.F >= 0 && nt.F < N  &&nt.S >= 0 && nt.S < N && occupy[nt.F][nt.S] == false && iswall[next[i].F][next[i].S][j] != true)
                {
//                    cout << next[i].F << ", " << next[i].S << "turn " << i << " is " << iswall[next[i].F][next[i].S][i] << endl;
                    next[i] = nt;
                    nt = {next[i].F + direc.F, next[i].S + direc.S};

                    if (table[next[i].F][next[i].S] != -1)
                    {
                        int k = table[next[i].F][next[i].S];
                        if (((newfilled) & (1 << k)) == 0){
                            if(k == i){
                                newfilled |= (1 << k);
                                next[i].F = next[i].S = -1;
                            }
                            else{
                                moveit = false;
                            }
                            break;
                        }
                    }
                }
                if(next[i].F != -1)
                    occupy[next[i].F][next[i].S] = true;
                if (moveit == false)
                    break;
            }
            if(moveit && visited.count(next) == 0){
                #ifdef Dmove
                cout << "putin: \n";
                pit(next);
                #endif
                Q.emplace(next, step + 1, newfilled);
                visited.emplace(next);
            }
        }
    }
   

}

int main()
{
    int caseN = 1;
    while (cin >> N >> M >> W)
    {
        if(N == 0)
            break;
        ans = -1;
        base.resize(M);
        table.clear();
        table.resize(N, vec<int>(N, NORMAL));
        iswall.clear();
        iswall.resize(N, vec<vec<bool>>(N, vec<bool>(4, false)));
        visited.clear();
        for (pii &e : base)
        {
            cin >> e.F >> e.S;
        }
        for (int i = 0; i < M; i++){
            int r, c;
            cin >> r >> c;
            table[r][c] = i;
        }
        for (int i = 0; i < W; i++){
            int fr, fc, tr, tc;
            cin >> fr >> fc >> tr >> tc;
            if(fr == tr){
                int maxc = max(fc, tc), minc = min(fc, tc);
                iswall[fr][maxc][LEFT] = true;
                iswall[fr][minc][RIGHT] = true;
            }
            else{
                int maxr = max(fr, tr), minr = min(fr, tr);
                iswall[maxr][fc][UP] = true;
                iswall[minr][fc][DOWN] = true;
            }
        }
        simulate();
        cout << "Case " << caseN++ << ": ";
        if (ans == -1)
        {
            cout << "impossible\n";
        }
        else
            cout << ans << " moves\n";
        cout << "\n";
    }

    return 0;
}