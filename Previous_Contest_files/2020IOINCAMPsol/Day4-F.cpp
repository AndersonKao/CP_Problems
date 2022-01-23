// AC
#include <iostream>
#include <iomanip>
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
};

double dot[3][2];
Point<double> dots[3];
int main()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> dot[i][j];
        }
    }
    dots[0] = Point<double>(dot[0][0] - dot[1][0], dot[0][1] - dot[1][1]);
    dots[1] = Point<double>(dot[2][0] - dot[1][0], dot[2][1] - dot[1][1]);
    if (((dots[0].operator^(dots[1])) < 0.00000001) && ((dots[0].operator^(dots[1])) > -0.00000001))
        cout << "Yes\n";
    else
        cout << "No\n";
    // cout << fixed << setprecision(30) << (dots[0].operator^(dots[1]));
    return 0;
}