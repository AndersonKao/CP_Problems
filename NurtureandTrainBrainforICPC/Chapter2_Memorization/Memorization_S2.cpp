#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)

int main()
{
    bool s[99] = {false};

    REP(i, 99)
    {
        bool flag = true;
        int limit = sqrt(i) + 0.5;
        for (int j = 2; j <= limit; j++)
        {
            //cout << i << "'sflag: " << flag << endl;
            if (i % j == 0)
            {
                flag = false;
                break;
            }
            //cout << i << "'sflag after: " << flag << endl;
        }
        if (flag && i >= 2)
            s[i] = true;
        //cout << i << ": " << s[i] << endl;
    }

    int a, b;
    cin >> a >> b;
    REP(i, 99)
    {
        if (i % a == 0 &&  i % b == 0)
            printf("%d\n", i);
            
    }
    return 0;
}
