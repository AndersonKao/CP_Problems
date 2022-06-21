// AC 2022-06-20 13:11:38
// WA
// range是開區間
// WA
// 又忘記解二元的時候如果只有單根，計算要另外寫
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " :> " << x << endl;
template <typename T>
using vec = vector<T>;
const double eps = 1e-6;
vec<char> Jvec, Tvec;
inline int fcmp(const double&a, const double&b){
    if(abs(a-b) < eps){
        return 0;
    }
    return 2 * (a - b > 0) - 1;
}
inline double length(double x, double a){
    double term = sqrt(4 * a * a * x * x + 1.0);
    return (log(2*a*x + term) / (4*a)) + (x * term) / 2;
}

void process(vec<pair<double, int>>& mV,const vec<pair<double, int>> &V){
    int Cover = 0;
    for (const pair<double, int> &e : V)
    {
        if(e.S == 1){
            Cover++;
            if(Cover == 1)
                mV.eb(e.first, 1);
        }
        else if(e.S == 2){
            Cover--;
            if(Cover== 0)
                mV.eb(e.first, 2);
        }
    }
}

int main(){

    int J, T;
    double width;
    int caseN = 1;
    const int deN = -1;
    sleep(1);
    while (cin >> J >> T >> width)
    {
        if(!J && !T)
            break;
        // Assume cat can reach bridge and back to same building.
        double Jy = (J-1) * 3.0 + 1.0, Ty = (T-1) * 3.0 + 1.0;
        /*
        Jvec.resize(J);
        Tvec.resize(T);
        */
        vec<pair<double, int>> Cat, Bird;

        char pet;
        if(caseN == deN)
            cout << J << " " << T << " " << width << endl;
        REP(i, J)
        {
            //cin >> Jvec[i];
            cin >> pet;
            if(caseN == deN)
                cout << pet << " ";
            if (pet == 'C')
            {
                Cat.eb(i * 3.0 + 1.0 - 3.0, 1);
                Cat.eb(i * 3.0 + 1.0 + 0.5, 2);
            }
            else if (pet == 'B')
            {
                Bird.eb(i * 3.0 + 1.0 - 0.5, 1);
                Bird.eb(i * 3.0 + 1.0 + 3.0, 2);
            }
        }
        if (caseN == deN)
            cout << endl;
        REP(i, T)
        {
            //            cin >> Tvec[i];
            cin >> pet;
            if(caseN == deN)
                cout << pet << " ";
            if (pet == 'C')
            {
                Cat.eb(i * 3.0 + 1.0 - 3.0, 1);
                Cat.eb(i * 3.0 + 1.0 + 0.5, 2);
            }
            else if (pet == 'B')
            {
                Bird.eb(i * 3.0 + 1.0 - 0.5, 1);
                Bird.eb(i * 3.0 + 1.0 + 3.0, 2);
            }
        }
        if (caseN == deN)
            cout << endl;
        vec<pair<double, int>> mCat, mBird;
        sort(al(Cat));
        sort(al(Bird));
        process(mCat, Cat);
        process(mBird, Bird);
        #ifdef merging
        cout << "mCat:\n";
        for_each(al(mCat), [](pair<double, int> &e)
                 { cout << e.S << " " << e.F<< endl; });
        cout << "mBird:\n";
        for_each(al(mBird), [](pair<double, int> &e)
                 { cout << e.S << " " << e.F << endl; });
        #endif
        int catCover = 0, birdCover = 0;

        vec<pair<double, int>>::iterator itc = mCat.begin(), itb = mBird.begin();
        double st;
        vec<pair<double, double>> block;
        block.eb(0.0, 1.0);
        while (itc != mCat.end() || itb != mBird.end())
        {
            int prior = -2;
            if (itc == mCat.end())
                prior = 1;
            else if(itb == mBird.end())
                prior = -1;
            else
                prior = fcmp(itc->first, itb->first);
            if (prior == 0) {
                if(itc->S == 1 && itb->S == 2){
                    block.eb(itc->F, itc->F);
                    catCover++;
                    birdCover--;
                }
                else if(itc->S == 2 && itb->S == 1){
                    block.eb(itc->F, itc->F);
                    catCover--;
                    birdCover++;
                }
                else if (itc->S == 1) {
                    st = itc->F;
                    catCover++;
                    birdCover++;
                }
                else if (itc->S == 2) {
                    catCover--;
                    birdCover--;
                    block.eb(st, itc->F);
                }
                itc++, itb++;
            }
            else if (prior == 1) {
                if (itb->S == 1) {
                    birdCover++;
                    if (catCover == 1 && birdCover == 1) {
                        st = itb->F;
                    }
                }
                else if (itb->S == 2) {
                    birdCover--;
                    if (catCover == 1 && birdCover == 0)
                    {
                        block.eb(st, itb->F);
                    }
                }
                itb++;
            }
            else if (prior == -1) {
                if (itc->S == 1) {
                    catCover++;
                    if(catCover == 1 && birdCover == 1){
                        st = itc->F;
                    }
                }
                else if(itc->S == 2) {
                    catCover--;
                    if(catCover == 0 && birdCover == 1){
                        block.eb(st, itc->F);
                    }
                }
                itc++;
            }
        }
        #ifdef Dblock
        cout << "block:---------------\n";
        for_each(al(block), [](pair<double, double> &e)
                 { cout << e.F << ", " << e.S << endl; });
        #endif
        double y3 = block.back().S;
        for (int i = 1; i < (int)block.size(); i++)
        {
            if(fcmp(block[i-1].S, block[i].F) <= 0){
                y3 = min(y3, block[i - 1].S);
                break;
            }
        }
        
        y3 += 1.0;
        if(fcmp(y3, min(Jy, Ty) - 2.0) > 0) // ? >= or >
        {
            if(caseN != 1)
                cout << endl;
            cout << "Case " << caseN++ << ": impossible" << endl;
            continue;
        }
        double h1 = Jy - Ty, h2 = Jy - y3, x2 = width;
        double ans = numeric_limits<double>::min();
        if (J == T) {
            double m = width / 2;
            double h2 = Jy - y3;
            double a = h2 / (m * m);
            ans = length(m, a) * 2;
        }
        else {
            double e = sqrt(h2 * h2 - h1 * h2);
            double m1 = x2 * (h2 + e) / h1;
            double m2 = x2 * (h2 - e) / h1;
            #ifdef Ddebug
            debug(Jy);
            debug(Ty);
            debug(y3);
            debug(h1);
            debug(h2);
            debug(x2);
            debug(e);
            debug(m1);
            debug(m2);
            #endif
            if (fcmp(m1, 0.0) > 0 && fcmp(m1, width) < 0)
            {
                double a = h2 / (m1 * m1);
                ans = length(x2 - m1, a) + length(m1, a);
            }
            if(fcmp(m2, 0.0) > 0 && fcmp(m2, width) < 0){
                double a = h2 / (m2 * m2);
                ans = max(ans, length(x2 - m2, a) + length(m2, a));
            }
        }
        /*
        if(!sol) // ? >= or >
        {
            if(caseN != 1)
                cout << endl;
            cout << "Case " << caseN++ << ": impossible" << endl;
            #ifdef Ddebug
            cout << "no sol\n";
            #endif
            continue;
        }
        */

        if(caseN != 1)
            cout << endl;
        cout << "Case " << caseN++ << ": " << fixed << setprecision(3)<< ans << endl;
    
    }

    return 0;
}