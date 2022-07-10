#include <bits/stdc++.h>
using namespace std;
#define X real()
#define Y imag()
#define eb emplace_back
template <typename T>
using point = complex<T>;
template <typename T>
using vec = vector<T>;
const double PI = 3.1415926535897;
const double eps = 1e-6;
int N, base;
int fcmp(double a, double b){
    if(abs(a-b) < eps){
        return 0;
    }
    return (a > b) * 2 - 1;
}
int main(){
    int caseN = 1;
    while (cin >> N >> base)
    {
        if(N == 0 && base == 0)
            break;
        vec<point<int>> pts;
        pts.eb(0, 0);
        double hPI = PI / 2.0;
        for (int i = 0; i < N; i++)
        {
            int x, y;
            cin >> x >> y;
            pts.eb(x, y);
        }
        if(base == 0){
            cout << "Case " << caseN++ << ": ";
            cout << "Acceptable as proposed\n\n";
            continue;
        }
        pair<double, double> posAns = {0, 2 * PI};
        pair<double, double> negAns = {0, 2* PI};
    
        for (int i = 0; i < N; i++)
        {
            int dx = pts[i + 1].X - pts[i].X;
            int dy = pts[i + 1].Y - pts[i].Y;
            double theta = atan2(dy, dx);
      //      cout << theta << endl;
            pair<double, double> Posrange, negrange;
            if (theta >= 0.0 && theta <= (hPI)){
            //    cout << "0\n";
                Posrange = {0, theta + PI / 2.0};
                negrange = {0, hPI - theta};
            }
            else if(theta > hPI && theta <= (PI + eps)){
            //    cout << "1\n";
                Posrange = {theta - hPI, theta - hPI + PI};
                negrange = {hPI + PI - theta, hPI + PI - theta + PI};
            }
            else if(theta < 0.0 && theta >= -hPI){
           //     cout << "2\n";
                Posrange = {0, hPI + theta};
                negrange = {0, -theta + hPI};
            }
            else if(theta < -hPI && theta >= -(PI + eps)){
          //      cout << "3\n";
                Posrange = {hPI + PI + theta, hPI + 2 * PI + theta};
                negrange = {-theta - hPI, -theta - hPI + PI};
            }
            #ifdef Drange
            cout << "Posrange: " << Posrange.first << ", " << Posrange.second << endl;
            cout << "Negrange: " << negrange.first << ", " << negrange.second << endl;
            #endif
            posAns = {max(posAns.first, Posrange.first), min(posAns.second, Posrange.second)};
            negAns = {max(negAns.first, negrange.first), min(negAns.second, negrange.second)};
        }
        bool pos, neg;
        pos = neg = true;
        if (fcmp(posAns.first, posAns.second) == 1)
            pos = false;
        if (fcmp(negAns.first , negAns.second) == 1)
            neg = false;
        cout << "Case " << caseN++ << ": ";
        posAns.first = posAns.first / PI * 180.0;
        posAns.second = posAns.second/ PI * 180.0;
        negAns.first = negAns.first / PI * 180.0;
        negAns.second = negAns.second/ PI * 180.0;
        cout << fixed << setprecision(2);
        if (fcmp(posAns.first, 0.0)== 0 || fcmp(negAns.first, 0.0) == 0)
        {
            cout << "Acceptable as proposed";
        }
        else{
            if(pos && neg){
                if(fcmp(posAns.first, negAns.first) <= 0){
                    cout << "Acceptable after clockwise rotation of " << posAns.first << " degrees";
                }
                else{
                    cout << "Acceptable after counterclockwise rotation of " << negAns.first << " degrees";
                }
            }
            else if(pos){
                cout << "Acceptable after clockwise rotation of " << posAns.first << " degrees";
            }
            else if(neg){
                    cout << "Acceptable after counterclockwise rotation of " << negAns.first << " degrees";
            }
            else{
                cout << "Unacceptable";
            }
        }
        cout << "\n\n";
    }
    return 0;
}