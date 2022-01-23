#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)

int main()
{
    //preprocessing
    /*
    char s[13] = "Hello World!";
    int len = strlen(s);
    REP(i, strlen(s))
    {
        cout << s[i];
    }
    */
    int s[99];
    int size = 0;
    bool flag;
    for (int i = 2; i < 100; i++)
    {
        flag = true;
        int limit = sqrt(i) + 0.5;
        for (int j = 2; j <=limit; j++)
        {
            if (i % j == 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            s[size++] = i;
    }
    int a, b;
    int ap, bp;
    cin >> a >> b;
    REP(i, size)
    {
        if (s[i] == a)
            ap = i;
        if (s[i] == b)
            bp = i;
    }

    REP(i, 99)
    {
        if (i % s[ap] == 0 && i % s[bp] == 0)
            cout << i << endl;
    }
    return 0;
}