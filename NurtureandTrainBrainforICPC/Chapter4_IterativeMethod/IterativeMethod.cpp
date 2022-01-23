#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#define REP(i, n) for (int i = 0; i < n; i++)
using namespace std;
int main()
{
    int a, r;
    cin >> a >> r;
    int appear[a];
    REP(i, a)
    appear[i] = 0;

    int c = 0;
    int q = 0;


    while(!appear[r])
    {
        appear[r] = ++c;

        r = r * 10;
        q = r / a;
        cout << q;
        r = r % 53;
    }
    cout << c - appear[r] + 1;
    cout << endl;
    printf("%.47f", r / a);
}