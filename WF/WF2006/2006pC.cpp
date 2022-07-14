#include <bits/stdc++.h>
using namespace std;


#define REP(i, n) for (int i = 0; i < (int)n; i++)
template <typename T>
using vec = vector<T>;
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;

struct Point
{
    double x, y, z;
    Point():x(0.0), y(0.0), z(0.0){}
    Point(double x, double y, double z):x(x), y(y), z(z){}
    Point operator-(const Point& pt){
        return Point(x - pt.x, y - pt.y, z - pt.z);
    }
    friend ostream &operator<<(ostream &os, Point &a);
};
ostream &operator<<(ostream &os, Point &a){
    return (os << "("<<a.x << ", " << a.y << ", " << a.z << ")");
}
int J, R;
int Len;
double eps = 1e-9;
inline int fcmp(double a, double b){
    if(fabs(a- b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
void pG(vec<vec<double>> &polynomials){
    cout << "polynomials now -----------------:\n";
    for (int i = 0; i < Len; i++)
    {
        cout <<setw(3) << i << ": ";
        for (int j = 0; j <= R; j++)
        {
            cout << setw(5) << polynomials[j][i] << " ";
        }
        cout << endl;
    }
}
bool eliminate(int k, int r, vec<vec<double>> &polynomials)
{
    vec<double> rate(Len, 0.0);
    double base = polynomials[k][r];
    if(fcmp(base, 0.0) == 0){
        int found = -1;
        for (int i = r + 1; i < Len; i++){
            if(fcmp(polynomials[k][i], 0.0) != 0){
                found = i;
                break;
            }
        }
        if(found == -1){
            return false;
        }
        for (int i = k; i <= R; i++){
            swap(polynomials[i][r], polynomials[i][found]);
        }
        base = polynomials[k][r];
    }
    for (int i = r+1; i < Len; i++){
        rate[i] = polynomials[k][i] / base;
        polynomials[k][i] = 0.0;
    }
    /*
    for (int i = 0; i < Len; i++){
        cout << setw(4) << rate[i] << " ";
    }
    cout << endl;
    */
    for (int i = k + 1; i <= R; i++)
    {
        for (int j = r + 1; j < Len; j++)
        {
            polynomials[i][j] -= polynomials[i][r] * rate[j];
        }
    }
    return true;
}
// 0 for no solution, 1 for one solution, 2 for inf solution
int gauss(vec<vec<double>>&polynomials, int target){
    int curr = 0;
//    pG(polynomials);
    REP(k, R)
    {
        if(eliminate(k,curr, polynomials))
            curr++;
//        pG(polynomials);
    }
    for (int i = curr; i < Len; i++) {
        if(fcmp(polynomials[R][i], 0.0) !=0){
            return 0;
        }
    }
    if(curr == target)
        return 1;
    return 2;
}
int main()
{
    int caseN = 1;
    while (cin >> J >> R)
    {
        if(J == 0 && R == 0)
            break;
        vec<Point> pts(J);
        Len = 3 * J;
        vec<vec<double>> polynomials(R + 1, vec<double>(3 * J, 0.0)); // i for x, i + J for y, i +2 * J for z.
        
        REP(i, J)
        {
            cin >> pts[i].x >> pts[i].y >> pts[i].z;
        }
        int target = 0;
        for (int i = 0; i < J; i++)
        {
            if(fcmp(pts[i].z, 0.0) != 0){
                polynomials[R][i] = 1.0;
                target+= 3;
            }
        }
        REP(i, R)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            Point Vector = pts[u] - pts[v];
//            cout << u << ", " << v << endl;
//            cout << Vector << endl;
            if (fcmp(pts[u].z, 0.0) != 0)
            {
                polynomials[i][u] = Vector.z;
                polynomials[i][u + 1 * J] = Vector.y;
                polynomials[i][u + 2 * J] = Vector.x;
            }
            if (fcmp(pts[v].z, 0.0) != 0){
                polynomials[i][v] = -Vector.z;
                polynomials[i][v + 1 * J] = -Vector.y;
                polynomials[i][v + 2 * J] = -Vector.x;
            }
        }
        int ans = gauss(polynomials, target);
        cout << "Sculpture " << caseN++ << ": ";
        cout << (ans ? (ans == 1 ? "STABLE" : "UNSTABLE") : "NON-STATIC");
        cout << endl;
    }
    return 0;
}