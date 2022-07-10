// AC 2022-07-08 23:04:02
// WA
// Don't make N=2 as an edge case
// Make it into normal procedure and do checking
// don't be scared of inf pressure, it's just case region = 2;
/*
4
10 4 4 4 
1 4 4 
*/
/*
3
3 5 5 
3 5
*/
#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define REP(i, n) for (int i = 0; i < (int)n; i++)
using pdd = pair < double, double>;
#define debug(x) cout << #x << ":= " << x << endl;
const double eps = 1e-8;
int fcmp(const double &a, const double &b)
{
    if(abs(a- b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
double baseh;
inline double wP(double h)
{
    return 1 + 0.097 * (baseh - h);
}
inline double soleq(double a, double b, double c){
    return ((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
}
int main()
{
    int N;
    int caseN = 1;
    const double k = 0.097;
    while (cin >> N)
    {
        if(N == 0)
            break;
        vec<double> V(N);
        vec<double> h(N);
        vec<double> Sv(N);
        vec<pdd> P(N);
        for (double &e : V)
            cin >> e;
        baseh = V[0];
        Sv[N - 1] = V[N - 1];
        for (int i = Sv.size() - 2; i >= 0; i--)
        {
            Sv[i] = Sv[i + 1] + V[i];
        }
        for (int i = 1; i < N; i++)
            cin >> h[i];
        int stopid = -1;
        int region = -1;
        P[0].F = P[0].S = 1.0;
//        P[1].F = 1.0;
        /*
        if(N > 2)
            P[1].S = (Sv[1] - h[1]) * P[0].F / (Sv[1] - h[2]);
        else{
            //cout << "only two\n";
            stopid = 1;
            region = 1;
        }
        */
        for (int i = 1; i < N; i++)
        {
            if(i == 1)
                P[i].F = 1.0;
            else
                P[i].F = (Sv[i - 1] - h[i]) * P[i - 1].S / (Sv[i - 1] - h[i] * 2.0);
            #ifdef Ddoing
            debug(i);
            debug(wP(h[i]));
            #endif
            if (fcmp(wP(h[i]), P[i].F) < 0)
            {
                stopid = i;
                region = 2;
                break;
            }
            if(i + 1 < N){
                P[i].S = (Sv[i] - h[i]) * P[i].F / (Sv[i] - h[i + 1]);
                #ifdef Ddoing
                debug(wP(h[i+1]));
                #endif
                if(fcmp(wP(h[i+1]), P[i].S) < 0){
                    stopid = i;
                    region = 1;
                    break;
                }
            }
            else{
                // final tank
                stopid = N-1;
                region = 1;
            }
        }
        /*
        if(fcmp(wP(h[1]), P[1].S) < 0){
            stopid = 1;
            region = 1;
        }
        */
        #ifdef Dpre
        cout << "Presure:\n";
        for (int i = 0; i < N; i++)
        {
            cout << i << ": (" << P[i].F << ", " << P[i].S << ")\n";
        }
        #endif
        #ifdef Ddoing
        debug(stopid);
        #endif
        // stopid 跟 maybe stopid-1另外處理
        vec<double> ANS(N, 0.0);
        ANS[0] = V[0];
        int limit = stopid - 1;
        if (region == 1)
            limit++;
        for (int i = 1; i < limit; i++)
        {
            #ifdef Ddoing
            cout << "doing " << i << endl;
            #endif
            double Sp = V[i] - h[i + 1];
            double O = V[i], Pp = P[i+1].F;
            #ifdef Dsoleq
            debug(Sp);
            debug(O);
            debug(Pp);
            #endif
            double a = k;
            double b = k* (-O - V[0]) - 1.0;
            double c = (O + k* O * V[0] - Pp * Sp);
            ANS[i] = soleq(a, b, c);
        }
        if(region == 1){
            #ifdef Ddoing
            cout << "end in 1.\n";
            #endif
            double Sp = Sv[stopid] - h[stopid];
            double O = Sv[stopid], Pp = P[stopid].F;
            double a = k;
            double b = k* (-O - V[0]) - 1.0;
            double c = (O + k* O * V[0] - Pp * Sp);
            #ifdef Dsoleq
            debug(Sp);
            debug(O);
            debug(Pp);
            debug(a);
            debug(b);
            debug(c);
            #endif
            ANS[stopid] = soleq(a, b, c);
        }
        else if(region == 2){
            #ifdef Ddoing
            cout << "end in 2.\n";
            #endif
            int i = stopid - 1;
            double Sp = Sv[i] - h[stopid];
            double O = Sv[i] - h[stopid], Pp = P[i].S;
            #ifdef Dsoleq
            debug(Sp);
            debug(O);
            debug(Pp);
            #endif
            /*
            double a = k;
            double b = k* (-O - V[0]) - 1.0;
            double c = (O + k* O * V[0] - Pp * Sp);
            */
            ANS[i] = h[stopid];
//            ANS[stopid] = soleq(a, b, c);
            ANS[stopid] = O - Sp * Pp / (1 + k * (V[0] - h[stopid]));
        }
        else{
            cout << "what the fuck\n";
        }
//        cout << "ANSss\n";
        #ifdef Dans
        for (int i = 0; i < ANS.size(); i++)
        {
            cout << i << ": " << ANS[i] << endl;
        }
        #endif
            double finalans = accumulate(al(ANS), 0.0);
            cout << fixed << setprecision(3);
            cout << "Case " << caseN++ << ": " << finalans << endl;
            cout << endl;
            //            cout.unsetf(ios_base::floatfield);
            //            cout.precision(7);
    }
    return 0;
}