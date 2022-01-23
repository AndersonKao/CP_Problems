#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int* dacsort(int n[]);
#define REP(i, n) for (int i = 0; i < n;i++)
int main()
{
    const int the_one = 10;
    int one = the_one;
    const int c_howm = 10;
    int howm = c_howm;
    double rwe=0;
    // for (int i=0; i * i < one;i++)
    // {
    //     rwe = i;
    // }
    double pt = 0;
    double z;
    while(howm >= 0)
    {
        
        
        for (int i = 1; i<10;i++)
        {
            z = rwe + i * pow(10, howm - c_howm);
            if(z*z < one){
                pt = i;
            }
        }
        
        rwe += pt * pow(10, howm - c_howm);
        howm--;
    }
    printf("%.10f", rwe);

    return 0;
}

