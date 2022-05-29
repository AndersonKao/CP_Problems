#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define eb emplace_back
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define devec(x)      \
    for (auto &e : x) \
        cout << e << " ";
#define X real()
#define Y imag()
#define U 0
#define D 1 
#define L 2
#define R 3
template <typename T>
using vec = vector<T>;
using point = complex<int>;
vec<point> di = {
    {0, 1},
    {0, -1},
    {-1, 0},
    {1, 0}
};

struct segment{
    point st, ed;
    segment():st(0,0), ed(0,0) {}
    segment(point &st, point &ed) : st(st), ed(ed){}
    friend ostream &operator<<(ostream &os, segment& e);
};
ostream &operator<<(ostream &os, segment&e)
{
    return (os << "st: (" << e.st.X << ", " << e.st.Y << ") ed: (" << e.ed.X << ", " << e.ed.Y << ")");
}
vec<segment> segs;
vec<point> pts;
int main()
{
    int N, len;
    point cur(0, 0);
    for(point &v: di){
        cout << v.X << ", " << v.Y << endl;
    }
    while (cin >> N)
    {
        if(!N)
            break;
        segs.clear(), pts.clear();
        char direc;
        REP(i, N)
        {
            cin >> len >> direc;
            int diIdx = 0;
            switch (direc)
            {
            case 'U':
                diIdx = 0;
                break;
            case 'D':
                diIdx = 1;
                break;
            case 'L':
                diIdx = 2;
                break;
            case 'R':
                diIdx = 3;
                break;
            default:
                break;
            }
            point nxt = cur + len * (di[diIdx]);
            segs.eb(cur, nxt);
            pts.eb(cur);
            cur = nxt;
        }
        for(point& e: pts){
            cout << e.X << ", " << e.Y << endl;
        }
        for(segment& e: segs){
            cout << e << endl;
        }
        // Case1: all point


        // all edge

        // 

    }

    return 0;
}