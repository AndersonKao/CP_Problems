#include <bits/stdc++.h>
using namespace std;
#define X real() 
#define Y imag() 
#define F first
#define S second
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " := " << x << endl;
#define depii(x) cout << #x << ":(" << x.first << ", " << x.second << ")" << endl;
#define dept(x) cout << #x << ":(" << x.X<< ", " << x.Y<< ")" << endl;
#define eb emplace_back
using Point = complex<int>;
using pii = pair<int, int>;
using Line = pair<Point, Point>;
/*
struct Point{
    int x, y;
    Point():x(0), y(0){}
    Point(Point&p):x(p.x), y(p.y){}
    Point(const int x, const int y) { this->x = x, this->y = y; }
    explicit operator Point() const
    {
        return Point(x, y);
    }
    Point operator+(const Point& pt){
        return Point(x + pt.x, y + pt.y);
    }

};
*/
vec<Point> direc={
    Point(0, 1),
    Point(0, -1),
    Point(1, 0),
    Point(-1, 0)
};
inline int nxti(int i, int n){
    return (i + 1 == n ? 0 : i + 1);
}
inline int addi(int i, int a, int n){
    return i + a >= n ? i + a - n : i + a;
}
inline int prei(int i, int n){
    return (i == 0 ? n-1 : i - 1);
}
inline int d2d(char ch){
    switch (ch)
    {
    case 'N':
    case 'U':
        return 0;
        break;
    case 'S':
    case 'D':
        return 1;
        break;
    case 'E':
    case 'R':
        return 2;
        break;
    case 'W':
    case 'L':
        return 3;
        break;

    default:
        break;
    }
    return -1;
}
inline int distance(const Point& a, const Point& b){
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}
Point walkid(vec<Point>& points, int id, int len, int &fid)
{ // fid the first one's id in front of the return point.
    int accu = 0;
    int cur = id;
    int N = points.size();
    Point ans;
    while (accu < len)
    {
        int nxt = nxti(cur, N);
        int dis = distance(points[cur], points[nxt]);
//        accu += dis;
        if (accu +dis == len) {
//            fid = prei(cur, N);
            fid = nxt;
            ans = points[nxt];
            
        }
        else if(accu +dis > len){
            fid = cur;
            dis = len - accu;
            if (points[cur].X == points[nxt].X)
            {
                if(points[cur].Y < points[nxt].Y){
                    ans = points[cur] + dis* direc[0];
                }
                else {
                    ans = points[cur] + dis* direc[1];
                }
            }
            else {
                if(points[cur].X < points[nxt].X){
                    ans = points[cur] + dis* direc[2];
                }
                else {
                    ans = points[cur] + dis* direc[3];
                }
            }
        }
        accu += dis;
        cur = nxt;
    }
    return ans;
}

using ppi = pair<Point, int>;
inline bool between(const Point& A, const Point& L, const Point& R){
    if((L.X == R.X && A.X == L.X && A.Y > min(L.Y, R.Y) && A.Y < max(L.Y, R.Y))
    or (L.Y == R.Y && A.Y == L.Y && A.X > min(L.X, R.X) && A.X < max(L.X, R.X)))
        return true;
    return false;
}
inline char direction(const Point& from, const Point&to){
    if(from.X == to.X){
        if(from.Y < to.Y)
            return 'U';
        else
            return 'D';
    }
    else {
        if(from.X < to.X)
            return 'R';
        else
            return 'L';
    }
}

bool simulate(vec<Point> & points, ppi stA, ppi edA, ppi stB, ppi edB)
{
    #ifdef Dsimu
    cout << "start simulate:\n";
    debug(stA.F);
    debug(stB.F);
    #endif
    char opA, opB;
    int opLA, opLB;
    int N = points.size();
    while (stA.first != edA.first || stB.first != edB.first)
    {
        int nAi = nxti(stA.S, N);
        if (between(edA.F, stA.F, points[nAi]))
        {
            opA = direction(stA.F, edA.F);
            opLA = distance(stA.F, edA.F);
            stA = edA;
        }
        else{
            opA = direction(stA.F, points[nAi]);
            opLA = distance(stA.F, points[nAi]);
            stA.F = points[nAi];
            stA.S = nAi;
        }
        int nBi = prei(stB.S, N);
        if (between(edB.F, stB.F, points[nBi]))
        {
            opB = direction(stB.F, edB.F);
            opLB = distance(stB.F, edB.F);
            stB = edB;
        }
        else{
            opB = direction(stB.F, points[nBi]);
            opLB = distance(stB.F, points[nBi]);
            stB.F = points[nBi];
            stB.S = nBi;
        }
        if(opB != opA || opLA != opLB){
            #ifdef Dsimu
            cout << "wrong at \n";
            debug(opA);
            debug(opLA);
            debug(opB);
            debug(opLB);
            #endif
            return false;
        }
        #ifdef Dsimu
            cout << "step at \n";
            debug(opA);
            debug(opLA);
            debug(opB);
            debug(opLB);
        #endif
    }
    if(stA.first != edA.first || stB.first != edB.first){
        #ifdef Dsimu
        cout << "wrong at end\n";
        dept(stA.first);
        dept(stB.first);
        #endif
        return false;
    }
    #ifdef Dsimu
    cout << "successfully simulate\n";
    #endif
    return true;
}
vec<Point> points;
int main()
{
    int N;
    int caseN = 1;
    while (cin >> N){
        if(N == 0)
            break;
        points.clear();
        vec<Line> Lines;
        Point st(0, 0);
        points.clear();
        int perimeter = 0;
        REP(i, N)
        {
            char ch;
            int len;
            cin >> ch >> len;
            points.eb(st);
            st = st + direc[d2d(ch)] * len;
            perimeter += len;
        }
        bool ans = false;

        for (int pi = 0; pi < N; pi++){
            for (int pj = pi + 1; pj <N; pj++){
                for (int pk = pj + 1; pk < N; pk++) {
                    #ifdef Dpick
                    cout << "pi: " << pi << " pj: " << pj << " pk: " << pk << "---------" << endl;
                    #endif
                    int ncpi = -1, ncpj = -1, ncpk = -1;
                    vec<pair<Point, int>> tiling;
                    tiling.eb(points[pi], pi);
                    tiling.eb(points[pj], pj);
                    tiling.eb(points[pk], pk);
                    Point cpti = walkid(points, pi, perimeter / 2, ncpi);
                    Point cptj = walkid(points, pj, perimeter / 2, ncpj);
                    Point cptk = walkid(points, pk, perimeter / 2, ncpk);
                    #ifdef Dpick
                    dept(cpti);
                    dept(cptj);
                    dept(cptk);
                    #endif
                    tiling.eb(cpti, ncpi);
                    tiling.eb(cptj, ncpj);
                    tiling.eb(cptk, ncpk);
                    sort(al(tiling), [](pair<Point, int> &a, pair<Point, int> &b) {
                        if(a.second != b.second)
                            return a.second < b.second;
                        else {
                            int ni = nxti(a.second, points.size());
                            if (points[a.second].X == points[ni].X)
                            {
                                return (points[a.second].Y < points[ni].Y ? (a.F.Y < b.F.Y) : (a.F.Y > b.F.Y));
                            }
                            else {
                                return (points[a.second].X < points[ni].X ? (a.F.X < b.F.X) : (a.F.X > b.F.X));
                            }
                        }
                    });
                    #ifdef Dtiling
                    for(pair<Point,int>&e: tiling){
                        cout << "tiling: " << e.second;
                        dept(e.first);
                    }
                    #endif
                    // A0 B1 C2 D3 E4 F5                    
                    // AB~ED, BC~FE, CD~AF
                    // 01~43, 12~54, 23~05


                    for (int i = 0; i < 3; i++){
                        if (simulate(points, tiling[i], tiling[nxti(i, 6)], tiling[nxti(i+3, 6)], tiling[i+3]) == false)
                            break;
                        if(i == 2)
                            ans = true;
                    }
                }
            }
        }
        cout << "Polygon " << caseN++ << ": " << (ans ? "Possible" : "Impossible") << endl;
    }
        return 0;
}