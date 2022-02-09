#include <bits/stdc++.h>
using namespace std;
#define MAXD 1e20
#define MIND 0.0

/*
#define DEBUGHULL
#define DEBUGANTI
#define DEBUGMIN
*/
//#define DEBUGMAX

const int INSIDE = -1;
const int BOUNDARY = 0;
const int OUTSIDE = 1;

inline int prev(int i, int n) { return i == 0 ? n - 1 : i - 1; }
inline int next(int i, int n) { return i == n - 1 ? 0 : i + 1; }

template <class T> inline int sgn(const T& x){
    return (T(0) < x) - (x < T(0));
}

template <typename T, typename Real = double>
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
    // 內 積 運 算 子
    T operator^(const Point b) const { return x * b.y - y * b.x; }
    // 外 積 運 算 子
    bool operator==(const Point b) const
    {
        return x == b.x and y == b.y;
    }
    bool operator!=(const Point b) const
    {
        return x != b.x or y != b.y;
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

template <typename T, typename Real = double>
struct Line
{
    Point<T> st, ed;
    Point<T> vec() const { return ed - st; }
    T ori(const Point<T> p) const { return (ed - st) ^ (p - st); }
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
    template<class F> 
    Line(const Point<F> x, const Point<F> y) {
        st = Point<T>(x);
        ed = Point<T>(y);
    }
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

    bool isPointOnSegProperly(const Point<T> p) const
    {
        return ori(p) == 0 and ((st - p) & (ed - p)) < 0;
    }
    Real disP2Line(const Point<T> p) const
    {
        return Line<double>(projection(p), Point<double>(p)).vec().norm();
    }

    Point<Real> getIntersection(const Line<Real> l)
    {
        Line<Real> h = *this;
        return l((l.st ^ h.vec()) / (h.vec() ^ l.vec())); // use operator()
    }

    Point<Real> projection(const Point<T> p) const
    {
        return operator()(((p - st) & vec()) / (Real)(vec().norm()));
    }
};
template <class F>
using Polygon = vector<Point<F>>;

template <class F>
Polygon<F> getConvexHull(Polygon <F> points) {
    sort(points.begin(), points.end());
    Polygon<F> CH;
    CH.reserve(points.size() + 1); // for what ??
    // ? reason
//    CH.emplace_back(points[0]);
//   CH.emplace_back(points[1]); 
// ! ^^^ no need for this because we have `while (size >= 2...)`
    for (int round = 0; round < 2; round++){
        int start = CH.size();
        for (Point<int> &pt: points) {
            while (CH.size() - start >= 2 && Line<F>(CH[CH.size() - 2], CH[CH.size() - 1]).ori(pt) <= 0) // ? Line is different than senpai's .
            {
                CH.pop_back();
            }
            CH.emplace_back(pt);
        }
        CH.pop_back();
        
        reverse(points.begin(), points.end());
    }
    // ? shoule we need this edge case ? from senpai.
    //if (CH.size() == 2 && CH[0] == CH[1]) CH.pop_back()
    return CH;
}


double getAreabyLine(Polygon<int>& hull, Line<double>& L){
    Point<double> Lmost(L.st), Rmost(L.ed);
    double Lmostdis, Rmostdis, height;
    Lmostdis = Rmostdis = height = 0.0;
    Point<double> refer(L.st);
    Point<double> proj;
    double curheight, curdis;
    Point<double> d_pt;
    for(Point<int> pt: hull){
        d_pt = Point<double>(pt);
        proj = L.projection(d_pt);
        curdis = Line<double>(refer, proj).vec().norm();
        if(Line<double>(refer, d_pt).ori(proj) > 0){
            if(Lmostdis < curdis){
                Lmost = proj;
                Lmostdis = curdis;
            }
        }else{
            if(Rmostdis  < curdis){
                Rmost = proj;
                Rmostdis = curdis;
            }
        }
        curheight = L.disP2Line(d_pt);
        height = height > curheight ? height : curheight;
    }
    double LRdis = Line<double>((Lmost), (Rmost)).vec().norm();
    double ans = height * LRdis;
    // ? constant really large
    // NOTE Elliminated 
#ifdef DEBUGMAX
    cout << "height " << height << endl;
    cout << "Lmost: " << Lmost << " dis = " << Lmostdis << endl;
    cout << "Rmost: " << Rmost << " dis = " << Rmostdis << endl;
    cout << "Area by Line Ans = " << ans << endl;
#endif
    return ans;
}


double getMaxArea(Polygon<int>& hull, Line<double>& LB, Line<double&> RB, int thepoint){
    Point<double> d_thept = Point<double>(hull[thepoint]);
    double maxA = 0.0;

    double RRad = (RB.st.y - RB.ed.y) / (RB.st.x - RB.ed.x);
    double LRad = (LB.st.y - LB.ed.y) / (LB.st.x - LB.ed.x);
#ifdef DEBUGMAX
    cout << "the point of Max = " << d_thept << endl;
    cout << "the point of LB.st = " << LB.st << endl;
    cout << "the point of RB.ed = " << RB.ed << endl;
    cout << "LRad = " << LRad << ", RRad = " << RRad << endl;
#endif

    LRad = atan(LRad);
    RRad = 2 * M_PI + atan(RRad);

    
    //if(LRad > RRad)
     //   swap(LRad, RRad);
    double cubicRad;
    double cubicRad2;
    double curARad;
    double curARad2;

    while(RRad - LRad >= 0.0001){
        cubicRad = (LRad * 2 + RRad) / 3;
        cubicRad2 = (LRad + RRad * 2) / 3;
#ifdef DEBUGMAX
        cout << "LRad = " << LRad << ", RRad = " << RRad << endl;
#endif
        Line<double> Base(d_thept, Point<double>(d_thept.x + cos(cubicRad), d_thept.y + sin(cubicRad)));
        curARad = getAreabyLine(hull, Base);
        Base = Line<double>(Point<double>(hull[thepoint]), Point<double>(hull[thepoint].x + cos(cubicRad2), hull[thepoint].y + sin(cubicRad2)));
        curARad2 = getAreabyLine(hull, Base);

        if(curARad2 > curARad){
            LRad = cubicRad;
        }else
            RRad = cubicRad2;
    }
#ifdef DEBUGMAX
    cout << "The Area get = " << max(curARad, curARad2) << endl;
#endif
    return max(curARad, curARad2);
}

void solve(int n){
    Polygon<int> P;
    int x, y;
    for (int i = 0; i < n; i++){
        cin >> x >> y;
        P.emplace_back(x, y);
    }
    Polygon<int> hull = getConvexHull(P);
    double maxA = MIND, minA = MAXD, tmp;
#ifdef DEBUGHULL
    cout << "hull size = " << hull.size() << endl;
    for (Point<int> p : hull){
        std::cout << p << endl;
    }
#endif
    Line<double> LBound(hull.back(), hull[0]), RBound(hull[0], hull[1]);
    for (int i = 0; i < hull.size(); i++)
    {
        RBound = Line<double>(hull[i], hull[next(i, hull.size())]);
        // <----- renew min ----->
        tmp = getAreabyLine(hull, (LBound));
        minA = minA < tmp ? minA : tmp;
        tmp = getAreabyLine(hull, (RBound));
        minA = minA < tmp ? minA : tmp;

        // <----- renew max ----->
        tmp = getMaxArea(hull, LBound, RBound, i);
#ifdef DEBUGMAX
        if(maxA < tmp)
            cout << "renew to " << tmp << endl;
#endif
        maxA = maxA > tmp ? maxA : tmp;
        LBound = RBound;
    }

    cout << "Minimum area = " << sqrt(minA) << endl;
    cout << "Maximum area = " << sqrt(maxA) << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    cout << fixed << setprecision(3);
    int cnt = 1;
    while(cin >> n){
        if(n == 0)
            break;
        cout << "Gift " << cnt++ << endl;
        solve(n);
        cout << endl;
    }

    return 0;
}