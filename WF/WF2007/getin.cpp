#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
int fcmp(double a, double b){
    if(abs(a- b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
auto cmp = [](int a, int b)
{
    return (a % 5 < b % 5);
};
int main()
{
    int T = 508;
    int K;
    /*
    cin >> T >> K;
    for (int i = 0; i < T; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        printf("A%d = (%d, %d, %d)\n",i,  x, y, z);
    }

    for (int i = 0; i < K; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--, z--;
        printf("t%d = Polygon(A%d,A%d,A%d)\n", i+1, x, y, z);
    }
    */
    vector<double> V1(T), V2(T);
    for (double &e : V1)
        cin >> e;
    for(double &e: V2)
        cin >> e;
    for (int i = 0; i < T; i++){
        if(fcmp(V1[i], V2[i]) != 0){
            printf("%dth %.10f, %.10f\n", i, V1[i], V2[i]);
        }
    }
}