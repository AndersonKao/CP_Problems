// AC 2022-07-06 00:05:51
// PE fuck
/*              
 1. 每個case空一行or not
 2. 數字間隔最後要or not
 3. 數字間隔兩格還是一格(not))
 1 2 3
 0 0 0
 0 0 1
 0 1 0
 0 1 1
 1 0 0 
 1 0 1 O // so lucky
 1 1 0 
 1 1 1 X
 */
// WA
// 比較的規則是
// 1. 比雙方最北的飛機
// 2. 比雙方最東的飛機
// 3. 比半徑大小
// WA
// 如果control的數量是0的話，只要枚舉所有飛機當最遠然後試試看能不能湊出合法的圓(包括兩點連線為直徑)
// 題目的sample在誤導人
// WA
// 如果發現枚舉所有飛機當最遠後，還是找不到合適的circle，需要多check 以兩點連線為直徑的circle
// check this : https://www.desmos.com/calculator/bd2ugkqxsu
// RE 
// forget to remove impossible pair plane that gives inf/-inf center or radius
// RE
// ncontrols might be 0
#include <bits/stdc++.h>
using namespace std;
// ref AC code:http://codepad.org/egzqUjT4
// from yuan : 
/*
1. 若一樣的話就比 第二北的
2. 好像還有一個條件是
選 比較 小的圓
這ㄍ個比較有問題
3. 依樣 再開始 比較每個點的字典序
*/
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
template <typename T>
using vec = vector<T>;
const double eps = 1e-5;
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
#define debug(x) cout << #x << ": " << x << endl;
using pdi = pair<double, int>;
vec<Point<double>> pts;
vec<int> ncontrols;
vec<pair<Point<double>, Point<double>>> boundary;

pair<Point<double>, double> SetCenter(int ci, int pi){
    Point<double> &pt1 = boundary[ci].F, &pt2 = boundary[ci].S, &pt3 = pts[pi];
    Line<double> L1((pt1 + pt2) / 2.0, (pt1 + pt2) / 2.0 + (pt2 - pt1).prep());
    Line<double> L2((pt1 + pt3) / 2.0, (pt1 + pt3) / 2.0 + (pt3 - pt1).prep());
    Point<double> c = L1.getIntersection(L2);
    /*
    debug((c - pt1).norm());
    debug((c - pt2).norm());
    debug((c - pt3).norm());
    */
    return {c, (c - pt1).norm()};
}

auto planecmp = [](pdi &a, pdi &b)
{
    int f = fcmp(pts[a.S].y, pts[b.S].y);
    if (f != 0)
        return (f > 0);
    else
    {
        f = fcmp(pts[a.S].x, pts[b.S].x);
        return (f > 0);
    }
};

int main()
{
    int NP, NC;
    int caseN = 1;
    cout << fixed << setprecision(2);
    while (cin >> NP >> NC)
    {
        if(NP == 0 && NC == 0)
            break;
        pts.resize(NP);
        ncontrols.resize(NC);
        boundary.resize(NC);
        vec<int> coverby(NP, 0);

        REP(i, NP)
        {
            cin >> pts[i];
        }
        REP(i, NC){
            cin >> ncontrols[i];
            cin >> boundary[i].F >> boundary[i].S;
        }
//        sort(al(pts));
        bool solvable = true;
        REP(i, NC)
        {
            Point<double> useo;
            double user2;
            vec<pair<double, int>> usVs;
            int desirej = -1;
            #ifdef Dij
            cout << "Processing C: ---" << i << endl;
            #endif
            useo = (boundary[i].F + boundary[i].S) / 2.0;
            user2 = (boundary[i].F - useo).norm();
            REP(j, NP) {
                double dis2 = (pts[j] - useo).norm();
                if (fcmp(dis2, user2) <= 0) // should this be <= or <, <= i.e. at least 1plane will be cover, < may or may not be covered
                {
                    usVs.eb(dis2, j);
                }
            }
            sort(al(usVs), [](pair<double, int> &a, pair<double, int> &b)
                    {  int f = fcmp(a.first, b.first);
                    if(f != 0)
                        return (f < 0);
                    return planecmp(a, b);
                });
            if (ncontrols[i] == 0){
                if(usVs.size() == 0){
                    continue;
                }
                else{
                    bool found = true;
                    REP(j, NP){
                        Point<double> o;
                        double r2;
                        tie(o, r2) = SetCenter(i, j);
                        found = true;
                        REP(k, NP)
                        {
                            double dis2 = (o - pts[k]).norm();
                            if (fcmp(dis2, r2) < 0){
                                found = false;
                                break;
                            }
                        }
                        if(found)
                            break;
                    }
                    if(found)
                        continue;
                    else{
                        solvable = false;
                        break;
                    }
                }
            }
            bool hasset = false;
            if((int)usVs.size() < ncontrols[i]){
                hasset = false;
                usVs.clear();
            }
            else{
                if(usVs.size() == ncontrols[i])
                    hasset = true;
                else{
                    if (fcmp(usVs[ncontrols[i]].first, user2) < 0){
                        hasset = false;
                        usVs.clear();
                    }
                    else{
                        usVs.resize(ncontrols[i]);
                        hasset = true;
                    }
                }
            }
            REP(j, NP)
            {
                Point<double> o;
                double r2;
                tie(o, r2) = SetCenter(i, j);
                if(isinf(o.x) || isinf(o.y) || isinf(r2))
                    continue;
                #ifdef Dij
                cout << "Pick Plane j = " << j << " " << pts[j] << endl;
                #endif
                #ifdef Dcr
                debug(r2);
                cout << "o: " << o << endl;
                #endif
                vec<pair<double, int>> Vs;
                REP(k, NP)
                {
                    double dis2 = (o - pts[k]).norm();
                    if (fcmp(dis2, r2) <= 0)
                        Vs.eb(dis2, k);
                }
                #ifdef Dsort
                cout << "unsorted planes: \n";
                for (pair<double, int> a : Vs)
                    cout << "("<<  a.S << ", " << a.F << ") ";
                cout << endl;
                #endif
                sort(al(Vs), [](pair<double, int> &a, pair<double, int> &b)
                     {  int f = fcmp(a.first, b.first);
                        if(f != 0)
                            return (f < 0);
                        return planecmp(a, b);
                    });
                #ifdef Dsort
                cout << "sorted planes: \n";
                for (pair<double, int> a : Vs)
                    cout << "("<<  a.S << ", " << a.F << ") ";
                cout << endl;
                #endif
                if((int)Vs.size() < ncontrols[i])
                    continue;
                Vs.resize(ncontrols[i]);
                if(fcmp(Vs.back().F, r2) < 0)
                    continue;
                #ifdef Dpick
                sort(al(Vs), planecmp);
                cout << "picked planes: \n";
                for (pair<double, int> a : Vs)
                {
                    cout << "("<<  a.S << ", " << a.F << ") ";
                }
                cout << "\n";
                #endif
                if(hasset == false){
                    #ifdef Dans
                    cout << "assign\n";
                    #endif
                    useo = o;
                    user2 = r2;
                    usVs = Vs;
                    hasset = true;
                    desirej = j;
                }
                else{
                    bool change = false;
                    int it1 = 0, it2 = 0;
                    if (planecmp(Vs[it2], usVs[it1])){
                        change = true;
                    }
                    else if(planecmp(usVs[it1], Vs[it2])){
                        change = false;
                    }
                    else if(fcmp(r2, user2) < 0){
                        change = true;
                    }
                        /*
                        while (it1 < (int)usVs.size() && it2 < (int)Vs.size())
                        {
                        #ifdef Dans
                        cout << "compare: " << pts[Vs[it2].second] << " and " << pts[usVs[it1].S] << endl;
                        #endif 
                        if (planecmp(Vs[it2], usVs[it1]))
                        {
                            change = true;
                            #ifdef Dans
                            cout << "change\n";
                            #endif
                            break;
                        }
                        else if(planecmp(usVs[it1], Vs[it2])){
                            #ifdef Dans
                            cout << "get out\n";
                            #endif
                            break;
                        }
                        it1++, it2++;
                        }
                        */
                    if(change){
                        useo = o;
                        user2 = r2;
                        usVs = Vs;
                        desirej = j;
                    }
                }
            }
            if(hasset == false){
                solvable = false;
                break;
            }
            #ifdef Dsolk
            debug(desirej);
            #endif
            for (pdi &e : usVs)
            {
                #ifdef Dsol
                cout << e.S << ", ";
                #endif
                coverby[e.S]++;
            }
            #ifdef Dsol
            cout << endl;
            #endif
        }
        vec<int> ANS(NC + 1, 0);
        REP(i, NP){
            ANS[coverby[i]]++;
        }
        cout << "Trial " << caseN++ << ":";
        if(solvable == false)
            cout << "  Impossible";
        else{
            for (int i = 0; i < (int)ANS.size(); i++){
                cout << "  "  << ANS[i];
            }
        }
        cout << "\n\n";

    }
    return 0;
}