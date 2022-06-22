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
#define eb emplace_back
#define debug(x) cout << #x << " >= " << x << endl;
#define al(x) x.begin(), x.end()
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
template <typename T>
using vec = vector<T>;
vec<vec<int>> G;
Line<double> L;
inline int getClosest(vec<Point<double>>& BTS, Point<double> pt, int exp){
    int ans = -1;
    int dis = numeric_limits<int>::max();
    REP(i, BTS.size())
    {
        double tost = (pt - BTS[i]).norm();
        if (fcmp(dis, tost) > 0)
        {
            if(exp != i){
                ans = i;
                dis = tost;
            }
        }
    }
    return ans;
}
int main()
{
    int B, C, R, Q;
    int caseN = 1;
    while (cin >> B >> C >> R >> Q)
    {
        if(B == 0 && C == 0 && R == 0 && Q == 0){
            break;
        }
        vec<Point<double>> BTS(B), cities(C);
        G.clear();
        G.resize(C, vec<int>(C, -1));
        REP(i, B)
        {
            cin >> BTS[i];
        }
        REP(i, C){
            cin >> cities[i];
        }
        REP(i, R){
            int u, v;
            cin >> u >> v;
            u--, v--;
            Line<double> L(cities[u],cities[v]);
            int weight = 0;
            int stB = getClosest(BTS, L.st, -1);
            int edB = getClosest(BTS, L.ed, -1);
            /*
            debug(u+1);
            debug(v + 1)
            debug(stB);
            debug(edB);
            */
            if (stB == edB)
            {
                G[u][v] = G[v][u] = 0;
                continue;
            }
            int curB = stB;
            while (curB != edB)
            {
                double t = 0.5;
                double offset = 0.25;
                REP(j, 1000)
                {
                    if(getClosest(BTS, L.st + L.vec() * t, -1) == curB){
                        t += offset;
                    }
                    else
                        t -= offset;
                    offset /= 2.0;
                }
                curB = getClosest(BTS, L.st + L.vec() * t, curB);
                weight++;
            }
            G[u][v] = G[v][u] = weight;
            //cout << u + 1 << " to " << v + 1 << " with " << weight << endl;
        }
        REP(k, C)
            G[k][k] = 0;
        REP(k, C)
        {
            REP(i, C){
                REP(j, C){
                    if(G[i][k] == -1 || G[k][j] == -1)
                        continue;
                    if(G[i][j] == -1)
                        G[i][j] = G[i][k] + G[k][j];
                    else
                        G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
        cout << "Case " << caseN++ << ":\n";
        REP(i, Q)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if(G[u][v] == -1){
                cout << "Impossible";
            }
            else
                cout << G[u][v];
            cout << endl;
        }
    }
    return 0;
}