#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
const double eps = 1e-6;
inline int fcmp(const double &a, const double &b){
    if(fabs(a - b) < eps)
        return 0;
    return ((a - b > 0.0) * 2) - 1;
}

template <typename T>
struct Point
{
    T x, y;
    Point() : x(0), y(0) {}
    Point(const T x, const T y) : x(x), y(y) {}
    template <class F>
    explicit operator Point<F>() const
    {
        return Point<F>((F)x, (F)y);
    }

    Point operator+(const Point b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point b) const
    {
        return Point(x - b.x, y - b.y);
    }
    template <class F>
    Point<F> operator*(const F fac)
    {
        return Point<F>(x * fac, y * fac);
    }
    template <class F>
    Point<F> operator/(const F fac)
    {
        return Point<F>(x / fac, y / fac);
    }

    T operator&(const Point b) const { return x * b.x + y * b.y; }
    // dot operator
    T operator^(const Point b) const { return x * b.y - y * b.x; }
    // cross operator
    bool operator==(const Point b) const
    {
        return x == b.x and y == b.y;
    }
    bool operator<(const Point b) const
    {
        return x == b.x ? y < b.y : x < b.x;
    } // 字 典 序

    Point operator-() const { return Point(-x, -y); }
    T norm() const { return *this & *this; }    // 歐 式 長 度 平 方
    Point prep() const { return Point(-y, x); } // 左 旋 直 角 法 向 量
    template <class F>
    friend istream &operator>>(istream &is, Point<F> &pt);
    template<class F>
    friend ostream &operator<<(ostream &os, const Point<F> &pt);
};
template <class F>
ostream &operator<<(ostream &os, const Point<F> &pt)
{
    return os << pt.x << " " << pt.y;
}
template <class F>
istream &operator>>(istream &is, Point<F> &pt)
{
    return is >> pt.x >> pt.y;
}
template <class F>
bool collinearity(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
//    return (p1 - p3) ^ (p2 - p3) == 0;
    return fcmp((p1 - p3) ^ (p2 - p3), 0.0) == 0;
}
// check co-line first. properly
template<class F>
inline bool btw(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    return fcmp((p1 - p3) & (p2 - p3), 0.0) <= 0;
}

// is p3 on (p1, p2)?
template<class F>
inline bool pointOnSegment(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    return collinearity(p1, p2, p3) && btw(p1, p2, p3);
}

template <typename T, typename Real = double>
struct Line
{
    Point<T> st, ed;
    Point<T> vec() const { return ed - st; }
    T ori(const Point<T> p) const { return (ed - st) ^ (p - st); }
    int orint(const Point<T> p) const{
        T a = this->ori(p);
        return (fcmp(a, 0.0), 0); // 1 on posi-side // -1 nega-side
        // a little bit useless?
    }
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
    Line() : st(0.0, 0.0), ed(0.0, 0.0) {}
    template <class F>
    operator Line<F>() const
    {
        return Line<F>((Point<F>)st, (Point<F>)ed);
    }

    // sort by arg, the left is smaller for parallel lines
    bool operator<(Line B) const
    {
        Point<T> a = vec(), b = B.vec();
        auto sgn = [](const Point<T> t) { return (t.y == 0 ? t.x : t.y) < 0; };
        if (sgn(a) != sgn(b))
            return sgn(a) < sgn(b);
        if (abs(a ^ b) == 0)
            return B.ori(st) > 0;
        return (a ^ b) > 0;
    }

    // Regard a line as a function
    template <typename F>
    Point<F> operator()(const F x) const // A + AB * x = the point position.
    {
        return Point<F>(st) + vec() * x;
    }

    bool isSegProperIntersection(const Line l) const
    {
        return l.ori(st) * l.ori(ed) < 0 and ori(l.st) * ori(l.ed) < 0;
    }
    bool isSegIntersection(const Line l)const{
        Line<Real> h = *this;
        // hst = 1, hed = 2, lst = 3, led = 4
        double hlst = h.ori(l.st);
        double hled = h.ori(l.ed);
        double lhst = l.ori(h.st);
        double lhed = l.ori(h.ed);
        if(fcmp(hlst, 0.0) == 0 && fcmp(hled,0.0) == 0)
            return h.isPointOnSeg(l.st) || h.isPointOnSeg(l.ed) || l.isPointOnSeg(h.st) || l.isPointOnSeg(h.ed);

        return fcmp(hlst * hled, 0.0) <= 0 && fcmp(lhst * lhed, 0.0) <= 0;
    }
    
    bool isPointOnSegProperly(const Point<T> p) const
    {
        return fcmp(ori(p), 0.0) == 0 and fcmp(((st - p) & (ed - p)), 0.0) < 0;
    }
    bool isPointOnSeg(const Point<T>p) const{
        return fcmp(ori(p), 0.0) == 0 and fcmp((st - p) & (ed - p), 0.0) <= 0;
    }
    Real disP2Line(const Point<T> p) const
    {
        return Line<double>(projection(p), Point<double>(p)).vec().norm();
    }

    // notice if you should check Segment intersect or not;
    // be careful divided by 0
    Point<Real> getIntersection(Line<Real> l)
    {
        Line<Real> h = *this;
//        return l(((l.st - h.st)^ h.vec()) / (h.vec() ^ l.vec())); // use operator()
        Real hlst = -h.ori(l.st);
        Real hled = h.ori(l.ed);
        return ((l.st * hled) + (l.ed * hlst)) / (hlst + hled);

        // 需要確認+-號的合理性
        // Area of triangle(l.st, h.st, h.ed) divided by Area of Quadrilateral(h.st, l.st, h.ed, l.ed)
    }

    Point<Real> projection(const Point<T> p) const
    {
        return operator()(((p - st) & vec()) / (Real)(vec().norm()));
    }
    template <class F>
    friend ostream &operator<<(ostream &os, const Line<F> &l);
};
template <class F>
ostream &operator<<(ostream &os, const Line<F> &l)
{
    return os << "(" << l.st.x << ", " << l.st.y << ") to (" << l.ed.x << ", " << l.ed.y << ")";
}
template <class F>
using Polygon = vector<Point<F>>;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define F first
#define S second
template <typename T>
using vec = vector<T>;
using LineB = pair<Line<double>, bool>;
#define debug(x) cout << #x << " >= " << x << endl;
void getclosest(const vec<LineB>&puzzle, vec<Line<double>>& pclosest){
    REP(i, puzzle.size()){
        const Point<double> &st = puzzle[i].F.st;
        const Point<double> &ed = puzzle[i].F.ed;
        double stdis = numeric_limits<double>::max();
        double eddis = numeric_limits<double>::max();
        REP(j, puzzle.size())
        {
            if(j == i)
                continue;
            double dis = (st - puzzle[j].F.st).norm();
            if(stdis > dis){
                stdis = dis;
                pclosest[i].st = puzzle[j].F.st;
            }
            dis = (st - puzzle[j].F.ed).norm();
            if(stdis > dis){
                stdis = dis;
                pclosest[i].st = puzzle[j].F.ed;
            }
            dis = (ed - puzzle[j].F.st).norm();
            if(eddis > dis){
                eddis = dis;
                pclosest[i].ed = puzzle[j].F.st;
            }
            dis = (ed - puzzle[j].F.ed).norm();
            if(eddis > dis){
                eddis = dis;
                pclosest[i].ed = puzzle[j].F.ed;
            }
        }
    }
}
const double dmax = numeric_limits<double>::max();
const double dmin = numeric_limits<double>::min();
Point<double> offsets;
Point<double> panc, manc; // ancor
double scale;
Point<double> puzzleMax(dmin, dmin);
Point<double> puzzleMin(dmax, dmax);

inline Point<double> m2p(const Point<double>& pt){
    return (pt - manc) * scale + manc + offsets;
}
inline Line<double> m2pL(const Line<double>& L){
    return Line<double>(m2p(L.st), m2p(L.ed));
}
inline Point<double> p2m(const Point<double>& pt){
    return (pt - panc) / scale + panc - offsets;
}
bool check(vec<LineB>& puzzle, vec<LineB>&image){
    int n = puzzle.size(), m = image.size();
    vec<LineB> panel;
    for (int i = 0; i < m; i++) {
        Line<double> tmp = m2pL(image[i].F);
        Point<double> st, ed;
        if(image[i].S == true){
            if (fcmp(tmp.st.x, puzzleMax.x) <= 0 && fcmp(tmp.st.x, puzzleMin.x) >= 0)
            {
                st.x = ed.x = tmp.st.x;
                ed.y = min(tmp.ed.y, puzzleMax.y);
                st.y = max(tmp.st.y, puzzleMin.y);
                if(fcmp(ed.y, puzzleMin.y) > 0 && fcmp(st.y, puzzleMax.y) < 0){
                    panel.eb(Line<double>(st, ed), image[i].S);
                }
            }
        }else{
            if (fcmp(tmp.st.y, puzzleMax.y) <= 0 && fcmp(tmp.st.y, puzzleMin.y) >= 0)
            {
                st.y = ed.y = tmp.st.y;
                ed.x = min(tmp.ed.x, puzzleMax.x);
                st.x = max(tmp.st.x, puzzleMin.x);
                if(fcmp(ed.x, puzzleMin.x) > 0 && fcmp(st.x, puzzleMax.x) < 0){
                    panel.eb(Line<double>(st, ed), image[i].S);
                }
            }
        }
    }
    sort(al(panel));
    #ifdef Dpanel
    cout << "panel\n";
    cout << "with offset = " << offsets << " and scale = " << scale << endl;
    cout << "pancor = " << panc << ", mancor: " << manc << endl;
    for_each(al(panel), [](LineB &a)
             { cout << "Line " << a.F << " is " << (a.S ? "vertical " : "horizontal") << endl; });
    cout << "pppppppppaaaaaaaaaaaannnnnnnnnneeeeeeeeeeel\n";
    #endif
    if(panel.size() != puzzle.size())
        return false;
    for (int i = 0; i < puzzle.size(); i++){
        Point<double>& st1 = panel[i].F.st;
        Point<double>& st2 = puzzle[i].F.st;
        Point<double>& ed1 = panel[i].F.ed;
        Point<double>& ed2 = puzzle[i].F.ed;
        if (fcmp(st1.x, st2.x) != 0 || fcmp(st1.y, st1.y) != 0 || fcmp(ed1.x, ed2.x) != 0 || fcmp(ed1.y, ed2.y) != 0)
            return false;
    }
    return true;
}

int main()
{

    yccc;
    int n, m;
    int caseN = 1;
    while (cin >> n >> m)
    {
        if(n == 0 && m == 0)
            break;
        vec<pair<Line<double>, bool>> puzzle, image; // vertical = true
        vec<Line<double>> pclosest(n), iclosest(m);
        puzzleMax = Point<double>(dmin, dmin);
        puzzleMin= Point<double> (dmax, dmax);
        REP(i, n)
        {
            Point<double> st, ed;
            cin >> st >> ed;
            puzzleMax.x = max(puzzleMax.x, st.x);
            puzzleMax.x = max(puzzleMax.x, ed.x);
            puzzleMax.y = max(puzzleMax.y, st.y);
            puzzleMax.y = max(puzzleMax.y, ed.y);
            puzzleMin.x = min(puzzleMin.x, st.x);
            puzzleMin.x = min(puzzleMin.x, ed.x);
            puzzleMin.y = min(puzzleMin.y, st.y);
            puzzleMin.y = min(puzzleMin.y, ed.y);
            if (st.x == ed.x)
                puzzle.eb(Line<double>(min(st, ed), max(st, ed)), true);
            else
                puzzle.eb(Line<double>(min(st, ed), max(st, ed)), false);
        }
        REP(i, m){
            Point<double> st, ed;
            cin >> st >> ed;
            if(st.x == ed.x)
                image.eb(Line<double>(min(st, ed), max(st, ed)), true);
            else
                image.eb(Line<double>(min(st, ed), max(st, ed)), false);
        }
        sort(al(puzzle));
        sort(al(image));
        if(n == 1){
        cout << "Case " << caseN++ << ": " << "valid puzzle" << endl << endl;
            continue;
        }
        int pVerI = 0, iVerI = 0;
        for (pVerI = 0; pVerI < n; pVerI++){
            if(puzzle[pVerI].S == true)
                break;
        }
        for (iVerI= 0; iVerI< m; iVerI++) {
            if(image[iVerI].S == true)
                break;
        }

        #ifdef Dinput
        cout << "puzzle:\n";
        debug(pVerI);
        for_each(al(puzzle), [](LineB &a)
                 { cout << "Line " << a.F << " is " << (a.S ? "vertical " : "horizontal") << endl; });
        cout << "image:\n";
        debug(iVerI);
        for_each(al(image), [](LineB &a)
                 { cout << "Line " << a.F << " is " << (a.S ? "vertical " : "horizontal") << endl; });
        #endif
        getclosest(puzzle, pclosest);
        getclosest(image, iclosest);

        bool totalpick = false;
        bool ans = false;
        REP(pi, n)
        {
            panc = puzzle[pi].F.st;
            double pdy;
            int eI = 0;
            bool picked = false;
            for (eI = 0; eI < n; eI++)
            {
                if(pi == eI)
                    continue;
                if((puzzle[eI].S == true && panc.x == puzzle[eI].F.st.x) || (puzzle[eI].S == true && panc.y == puzzle[eI].F.st.y ))
                    continue;
                totalpick = picked = true;
                pdy = sqrt(puzzle[eI].F.disP2Line(panc));
                break;
            }
            if(!picked)
                continue;

            REP(mi, m){
                if(puzzle[pi].S != image[mi].S)
                    continue;
                manc = image[mi].F.st;
                offsets = panc - manc;

                REP(meI, m){
                    if(image[meI].S != puzzle[eI].S)
                        continue;
                    if((image[meI].S == true && manc.x == image[meI].F.st.x) || (image[meI].S == true && manc.y == image[meI].F.st.y ))
                        continue;

                    double mdy = sqrt(image[meI].F.disP2Line(manc));
                    scale = pdy / mdy;

                    ans = check(puzzle, image);
                    if(ans)
                        break;
                }
                if(ans)
                    break;
            }
            if(ans)
                break;
        }
        cout << "Case " << caseN++ << ": " << (ans ? "valid puzzle" : "impossible") << endl << endl;
    }
        return 0;
}