// AC 2022-06-16 11:55:24
// WA
// 3point used wrong dis(m1, o)
// becarful of equation correctness
// the quardratic equation may have one sol rather than two sols, in this case you may encounter dividing by zero.
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
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
/*
#define DP3
#define DP2L1
#define DP1L2
#define DL3
#define DEBUG
*/
template <typename T>
using vec = vector<T>;
const int OUTSIDE = 0, BOUNDARY = 1, INSIDE = 2;
const double eps = 1e-9;
inline int fcmp(const double &a, const double &b){
    if(fabs(a - b) < eps)
        return 0;
    return ((a - b > 0.0) * 2) - 1;
}
inline int next(int i , int n){
    return i + 1 >= n ? 0 : i + 1;
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
    return os << "(" << pt.x << ", " << pt.y << ")";
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
        return fcmp(a, 0.0); // 1 on posi-side // -1 nega-side
        // a little bit useless?
    }
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
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
template <class F>
Polygon<F> getConvexHull(Polygon <F> points) {
    sort(points.begin(), points.end());
    Polygon<F> CH;
    CH.reserve(points.size() + 1); // for what ??
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
    if (CH.size() == 2 && CH[0] == CH[1])
        CH.pop_back();
    return CH;
}
vec<Point<int>> di = {
    Point<int>(0, 1),
    Point<int>(0, -1),
    Point<int>(-1, 0),
    Point<int>(1, 0)
};

vec<pair<Line<int>, bool>> segs;
vec<Point<int>> pts;

int inside(Point<double> pt){
    int n = static_cast<int>(pts.size()), windingNumber = 0;
    REP(i, n){
        int j = next(i, n);
        if(pt == Point<double>(pts[i]) || pt == Point<double>(pts[j])){ // important to check j 
            #ifdef DINSIDE
            cout << "onB1\n";
            #endif
            return BOUNDARY;
        }
        if(pts[i].y == pts[j].y && fcmp(pts[i].y, pt.y) == 0){
            if(fcmp(pts[i].x, pt.x) <= 0 && fcmp(pts[j].x, pt.x) >= 0){
                #ifdef DINSIDE
                cout << "onB2\n";
                #endif
                return BOUNDARY;
            }
        }else{
            bool below = (fcmp(pts[i].y, pt.y) < 0);
            if(below != (fcmp(pts[j].y, pt.y)  < 0)){
                int oriten = Line<double>(Point<double>(pts[i]), Point<double>(pts[j])).orint(pt);
                if(oriten == 0){
                    #ifdef DINSIDE
                    cout << Point<double>(pts[i]) << ", " << Point<double>(pts[j]) << pt << " is going ";
                    cout << "sht. err\n";
                    #endif
                    return 0;
                }
                if (below == (oriten > 0))
                {
                    windingNumber += (below ? 1 : -1);
//                    windingNumber++;
                    #ifdef DINSIDE
                    cout << "wound by " << pts[i] << " to " << pts[j] << endl;
                    #endif
                }
            }
        }
    }
    #ifdef DINSIDE
    cout << pt << "'s windingNumber = " << windingNumber << endl;
    #endif
    return (windingNumber == 0? OUTSIDE: INSIDE);
}

bool check(Point<double> pt, double sqr){
    double radius = sqrt(sqr);
    if(inside(pt) != INSIDE){
        #ifdef DINSIDE
        cout << pt << " with " << radius << " failed outside\n";
        #endif
        return false;
    }

    int n = static_cast<int>(segs.size());
    REP(i, n)
    {
        Line<double>dL = Line<double>(segs[i].F);
        double dis = 0.0;
        if(segs[i].S == true){
            double my = min(dL.st.y, dL.ed.y);
            double by = max(dL.st.y, dL.ed.y);
            if (fcmp(pt.y, by) <= 0 && fcmp(pt.y, my) >= 0)
                dis = dL.disP2Line(pt);
            else
                dis = min((dL.st - pt).norm(), (dL.ed - pt).norm());
        }
        else{
            double mx = min(dL.st.x, dL.ed.x);
            double bx = max(dL.st.x, dL.ed.x);
            if (fcmp(pt.x, bx) <= 0 && fcmp(pt.x, mx) >= 0)
                dis = dL.disP2Line(pt);
            else
                dis = min((dL.st - pt).norm(), (dL.ed - pt).norm());
        }
#ifdef DDISTANCE
        cout << pt << " with " << radius << " with dis = " << sqrt(dis) <<  " with line: " << segs[i].F << endl;
        #endif
        if(fcmp(dis, sqr) < 0){
            return false;
        }
    }
    return true;
}

int main()
{
    int N, len;
    int caseN = 1;
    while (cin >> N)
    {
        if(!N)
            break;
        if(caseN != 1)
            cout << endl;

        segs.clear(), pts.clear();
        Point<int> cur(0, 0);

        char direc;
        REP(i, N)
        {
            cin >> len >> direc;

            int diIdx = 0;
            bool vertical = false;
            switch (direc)
            {
            case 'U':
                diIdx = 0;
                vertical = true;
                break;
            case 'D':
                diIdx = 1;
                vertical = true;
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
            Point<int> nxt = cur +  (di[diIdx])*len ;
            segs.eb(Line<int>(cur, nxt), vertical);
            pts.eb(cur);
            cur = nxt;
        }
        #ifdef DINPUT
        for(Point<int>& e: pts){
            cout << e << endl;
        }
        for(auto & e: segs){
            cout << e.first << endl;
        }
        #endif

        // all edge combination
        double ans = 0.0;
        for (int i = 0; i <(int) segs.size(); i++)
        {
            for (int j = i + 1; j <(int) segs.size(); j++)
            {
                for (int k = j + 1; k <(int) segs.size(); k++)
                {
                    int type = (int)segs[i].S + (int)segs[j].S + (int)segs[k].S;
                    if(type == 0 || type == 3)
                        continue;
                    #ifdef DL3
                    cout << "using :\n";
                    cout << segs[i].F << endl;
                    cout << segs[j].F << endl;
                    cout << segs[k].F << endl;
                    #endif
                    Point<double> c1, c2;
                    double radius;
                    if (type == 1)
                    {
                        int verti = -1;
                        int hor1 = -1, hor2 = -1;
                        if (segs[i].S == true)
                        {
                            verti= i;
                            hor1 = j, hor2 = k;
                        }
                        else if (segs[j].S == true)
                        {
                            verti= j;
                            hor1 = i, hor2 = k;
                        }
                        else if (segs[k].S == true)
                        {
                            verti= k;
                            hor1 = i, hor2 = j;
                        }
                        radius = abs(segs[hor1].F.st.y - segs[hor2].F.st.y) / 2.0;
                        double y = min(segs[hor1].F.st.y, segs[hor2].F.st.y) + radius;
                        double x1 = segs[verti].F.st.x - radius;
                        double x2 = segs[verti].F.st.x + radius;
                        c1 = Point<double>(x1, y), c2 = Point<double>(x2, y);
                    }
                    else if(type == 2){
                        int hori = -1;
                        int ver1 = -1, ver2 = -1;
                        if (segs[i].S == false)
                        {
                            hori = i;
                            ver1 = j, ver2 = k;
                        }
                        else if (segs[j].S == false)
                        {
                            hori = j;
                            ver1 = i, ver2 = k;
                        }
                        else if (segs[k].S == false)
                        {
                            hori = k;
                            ver1 = i, ver2 = j;
                        }
                        radius = abs(segs[ver1].F.st.x - segs[ver2].F.st.x) / 2.0;
                        double x = min(segs[ver1].F.st.x, segs[ver2].F.st.x) + radius;
                        double y1 = segs[hori].F.st.y - radius;
                        double y2 = segs[hori].F.st.y + radius;
                        c1 = Point<double>(x, y1), c2 = Point<double>(x, y2);
                    }
                    #ifdef DL3
                    cout << "we find " << c1 << " , or , " << c2 << endl;
                    cout << "with radius : " << radius << endl;
                    #endif
                    if (check(c1, radius * radius) || check(c2, radius * radius))
                    {
                        #ifdef DEBUG
                        if(fcmp(ans , radius) < 0)
                            cout << "L3 renew to " << radius<< endl;
                        #endif
                        ans = max(radius, ans);
                    }
                }
            }
        }
        //  two point one edge;
        #ifdef DP2L1
        cout << "P2L1----------------\n";
        #endif
        for (int i = 0; i < (int)segs.size(); i++)
        {
            for (int pi = 0; pi < (int)pts.size(); pi++){
                for (int pj = pi + 1; pj < (int)pts.size(); pj++){
                    if(segs[i].first.orint(pts[pj]) == 0 && segs[i].first.orint(pts[pi]) == 0)
                            continue;
                    if(segs[i].first.orint(pts[pi]) != segs[i].first.orint(pts[pj]))
                        continue;
                    #ifdef DP2L1
                    cout << "Let's pick Line :" << segs[i].F << " points " << pts[pi] << " ans " << pts[pj] << endl;
                    #endif
                    Point<double> p1(pts[pi]), p2(pts[pj]);
                    Point<double> p3 = Point<double>(pts[pi] + pts[pj]) / 2.0;
                    Point<double> direc = Point<double>((pts[pi]- pts[pj]).prep());
                    direc = direc / sqrt(direc.norm());
                    double a = direc.x;
                    double b = direc.y;
                    double A = 0.0;
                    double B = 0.0, C = 0.0;
                    if (segs[i].S == true) // vertical
                    {
                        A = b * b;
                        double alpha = segs[i].first.st.x;
                        B = 2 * (a * (p3.x - p1.x) + b * (p3.y - p1.y) - a * (p3.x - alpha));
                        C = (p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y) - (p3.x - alpha) * (p3.x - alpha);
                    }
                    else  // horizontal
                    {
                        A = a * a;
                        double alpha = segs[i].first.st.y;
                        B = 2 * (a * (p3.x - p1.x) + b * (p3.y - p1.y) - b * (p3.y - alpha));
                        C = (p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y) - (p3.y - alpha) * (p3.y - alpha);
                    }
                    double t1, t2;
                    if (fcmp(A, 0.0) == 0)
                    {
                        t1 = t2 = -C / B;
                    }
                    else{
                        t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
                        t2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
                    }
                    #ifdef DP2L1
                    cout << direc << endl;
                    debug(a);
                    debug(b);
                    debug(A);
                    debug(B);
                    debug(C);
                    debug(t1);
                    debug(t2);
                    #endif
                    Point<double> o1 = p3 + direc * t1;
                    Point<double> o2 = p3 + direc * t2;
                    double r1 = ((o1 - p1).norm());
                    double r2 = ((o2 - p1).norm());
                    #ifdef DP2L1
                    cout << "we find " << o1 << " or " << o2 << endl;
                    cout << "with radius : " << r1 << "  or " << r2<< endl;
                    #endif
                    if (check(o1, r1)){
                        r1 = sqrt(r1);
                        #ifdef DEBUG
                        if(fcmp(ans, r1) < 0)
                            cout << "P2L1 renew to " << r1 << endl;
                        #endif
                        ans = max(r1, ans);
                    }
                    if (check(o2, r2))
                    {
                        r2 = sqrt(r2);
                        #ifdef DEBUG
                        if(fcmp(ans, r2) < 0)
                            cout << "P2L1 renew to " << r2 << endl;
                        #endif
                        ans = max(r2, ans);
                    }
                }
            }
        }

        // P1L2
        #ifdef DP1L2
        cout << "P1L2:\n";
        #endif
        for (int i = 0; i < (int)pts.size(); i++){
            for (int li = 0; li < (int)segs.size(); li++){
                if(pts[i] == segs[li].first.st || pts[i] == segs[li].first.ed)
                    continue;
                for (int lj = li + 1; lj < (int)segs.size(); lj++){
                    if(pts[i] == segs[lj].first.st || pts[i] == segs[lj].first.ed)
                        continue;
                    #ifdef DP1L2
                    cout << "Let's pick Line " << segs[li].F << " ans Line " << segs[lj].F << " and point " << pts[i] << endl;
                    #endif
                    Point<int> &pt = pts[i];
                    Point<double> o1, o2;
                    double r1, r2;
                    if (segs[li].second == segs[lj].second)
                    {
                        int l = (segs[li].second ? abs(segs[li].first.st.x - segs[lj].first.st.x) : abs(segs[li].first.st.y - segs[lj].first.st.y));
                        #ifdef  DP1L2SHIT
                        debug(max(segs[li].first.disP2Line(pts[i]), segs[lj].first.disP2Line(pts[i])));
                        debug(l * l);
                        #endif
                        if (max(segs[li].first.disP2Line(pts[i]), segs[lj].first.disP2Line(pts[i])) > l * l)
                            continue;
                        if(segs[li].second == true){
                            double r = 0.0;
                            double x = 0.0, y1 = 0.0, y2 = 0.0;
                            x = (segs[li].F.st.x + segs[lj].F.st.x) / 2.0;
                            r = abs(segs[li].F.st.x - x);
                            double y_offset = sqrt(r * r - abs(x - pt.x) * abs(x-pt.x));
                            y1 = pt.y + y_offset;
                            y2 = pt.y - y_offset;
                            o1 = Point<double>(x, y1);
                            o2 = Point<double>(x, y2);
                            r1 = r2 = r;
                        }
                        else{
                            double r = 0.0;
                            double x1 = 0.0, x2 = 0.0, y = 0.0;
                            y = (segs[li].F.st.y + segs[lj].F.st.y) / 2.0;
                            r = abs(segs[li].F.st.y - y);
                            double x_offset = sqrt(r * r - abs(y - pt.y) * abs(y-pt.y));
                            x1 = pt.x + x_offset;
                            x2 = pt.x - x_offset;
                            o1 = Point<double>(x1, y);
                            o2 = Point<double>(x2, y);
                            r1 = r2 = r;
                        }
                        #ifdef DP1L2
                            cout << "we found " << o1 << " or " << o2 << " r = " << r1 << endl;
                        #endif
                        if (check(o1, r1 * r1)){
                            #ifdef DEBUG
                            if(fcmp(ans, r1) < 0)
                            cout << "P1 L2 renew to " << r1<< endl;
                            #endif
                            ans = max(r1, ans);
                        }
                        if (check(o2, r2 * r2))
                        {
                            #ifdef DEBUG
                            if(fcmp(ans, r2) < 0)
                            cout << "P1 L2 renew to " << r2<< endl;
                            #endif
                            ans = max(r2, ans);
                        }
                    }
                    else
                    {
                        Point<int> intr; // intersect
                        if(segs[li].S == true){
                            intr = Point<int>(segs[li].F.st.x, segs[lj].F.st.y);
                        }
                        else
                        {
                            intr = Point<int>(segs[lj].F.st.x, segs[li].F.st.y);
                        }
                        if(intr == pt)
                            continue;
                        Point<double> o1, o2;
                        double r1 = 0.0, r2 = 0.0;
                        if ((pt.x > intr.x) == (pt.y > intr.y))
                        {
                            double xoff = intr.x - pt.x;
                            double yoff = intr.y - pt.y;
                            double A = 1;
                            double B = 2 * (xoff + yoff);
                            double C = xoff * xoff + yoff * yoff;
                            double t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
                            double t2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
                            o1 = Point<double>(intr.x + t1, intr.y + t1);
                            o2 = Point<double>(intr.x + t2, intr.y + t2);
                            r1 = abs(t1*t1);
                            r2 = t2 * t2;
                        }
                        else
                        {
                            double xoff = intr.x - pt.x;
                            double yoff = intr.y - pt.y;
                            double A = 1;
                            double B = 2 * (xoff - yoff);
                            double C = xoff * xoff + yoff * yoff;
                            #ifdef DP1L2
                            debug(B);
                            debug(C);
                            #endif
                            double t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
                            double t2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
                            o1 = Point<double>(intr.x + t1, intr.y - t1);
                            o2 = Point<double>(intr.x + t2, intr.y - t2);
                            r1 = abs(t1*t1);
                            r2 = t2 * t2;
                        }
                        #ifdef DP1L2
                        cout << "we find " << o1 << " or " << o2 << endl;
                        cout << "with radius : " << r1 << "  or " << r2<< endl;
                        #endif
                        if (check(o1, r1)){
                            r1 = sqrt(r1);
                            #ifdef DEBUG
                            if(fcmp(ans, r1) < 0)
                                cout << "P1L2 renew to " << r1 << endl;
                            #endif
                            ans = max(r1, ans);
                        }
                        if (check(o2, r2))
                        {
                            r2 = sqrt(r2);
                            #ifdef DEBUG
                            if(fcmp(ans, r2) < 0)
                                cout << "P1L2 renew to " << r2 << endl;
                            #endif
                            ans = max(r2, ans);
                        }
                    }
                }
            }
        }

        // P3
        #ifdef DP3
        cout << "P3:\n";
        #endif
        for (int i = 0; i < (int)pts.size(); i++){
            for (int j = i + 1; j < (int)pts.size(); j++){
                for (int k = j + 1; k < (int)pts.size(); k++){
                    if((pts[i].x == pts[j].x && pts[j].x == pts[k].x) || (pts[i].y == pts[j].y && pts[j].y == pts[k].y)){
                        continue;
                    }
                    #ifdef DP3
                    cout << "Let's pick " << pts[i] << " , " << pts[j] << ", " << pts[k] << endl;
                    #endif
                    Point<double> m1 = (pts[i] + pts[j]) / 2.0;
                    Point<double> m2 = (pts[j] + pts[k]) / 2.0;
                    Line<double> pb1(m1, m1 + Point<double>((pts[j] - pts[i]).prep()));
                    Line<double> pb2(m2, m2 + Point<double>((pts[k] - pts[j]).prep()));
                    Point<double> o = pb1.getIntersection(pb2);
                    double r = ((Point<double>(pts[i]) - o).norm());
                    #ifdef DP3
                    cout << "we found " << o << " and r = " << r << endl;
                    #endif
                    if (check(o,r )){
                        r = sqrt(r);
                        #ifdef DEBUG
                        if(fcmp(ans ,r) < 0)
                            cout << "P3 ans renew to " << r << endl;
                        #endif
                        ans = max(ans, r);
                    }
                }
            }
        }

        cout << fixed << setprecision(2) << "Case Number " << caseN++ << " radius is: " << ans + eps << endl;

        // 

    }

    return 0;
}