#include <bits/stdc++.h>
using namespace std;
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
    // 內 積 運 算 子
    T operator^(const Point b) const { return x * b.y - y * b.x; }
    // 外 積 運 算 子
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

template <typename T, typename Real = double>
struct Line
{
    Point<T> st, ed;
    Point<T> vec() const { return ed - st; }
    T ori(const Point<T> p) const { return (ed - st) ^ (p - st); }
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
    if (CH.size() == 2 && CH[0] == CH[1]) CH.pop_back()
    return CH;
}


int main(){

    return 0;
}