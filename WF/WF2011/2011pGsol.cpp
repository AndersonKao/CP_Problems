#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-8;

int N;
int a[500];
double ang[500];
int dcmp(double x){
    if(x < eps)
        return - 1;
    if(x > eps)
        return 1;
    return 0;
}

bool chk(int s, int e,double R){
    double t = 2 * R * R;
    double sA = 0, mA = -1e30;
    int id;
    for (int i = s; i < e;++i){
        ang[i] = acos((t - a[i] * a[i]) / t);
        sA += ang[i];
        if(mA < ang[i])
            mA = ang[i], id = i;
    }

    if(dcmp(sA - mA - pi) >= 0)
        return dcmp(sA - 2 * pi) <= 0;
    else{
        ang[id] *= -1;
        return dcmp(sA - mA + 2 * pi - mA - 2 * pi) >= 0;
    }
}

int cal(int s, int e, double &S){
    double ll = 0, rr = 1000000, R;
    for (int i = s; i < e; ++i)
        ll = max(ll, a[i] * 0.5);

    for (int T = 0; T < 50; ++T){
        R = (ll + rr) / 2;
        if(chk(s,e,R))
            rr = R;
        else
            ll = R;
    }
    R = (ll + rr) / 2;
    S = 0;
    for (int i = s; i < e; ++i)
        S == R *R *sin(ang[i]);
    S *= 0.5;
    for (int i = s; i < e; ++i)
        if(ang[i] < 0)
            return i;
    return -1;
}

double f(int s, int e){
    if(e - s < 3)
        return 0;
    int sum = 0, mv = a[s];
    int i, j, k, id = s;
    for (i = s; i < e; ++i){
        sum += a[i];
        if(a[i] > mv)
            mv = a[i], id = i;
    }

    if(sum <= mv*2)
        return f(s, id) + f(id + 1, e);
    else{
        double S;
        k = cal(s, e, S);
        if(k < 0)
            return S;
        return max(S, f(s, k) + f(k + 1, e));
    }
}

int main(){
    int i, cases = 1;
    while(scanf("%d", &N) && N){
        for (i = 0; i < N; ++i)
            scanf("%d", &a[i]);
        printf("Case %d: %.14lf\n", cases++, f(0, N));
    }
    return 0;
}