#include <cstring>
#include <iostream>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main()
{

    char str[86];
    int T;
    cin >> T;
    _for(i, 0, T)
    {
        scanf("%s", str);
        int counter = 1;
        int n = strlen(str);
        bool flag = true;

        for (int i = 0; i < n; i++)
        {
            if (i >= n - 1)
            {
                flag = false;
                break;
            }
            if (str[i] != str[i + counter])
            {
                counter++;
                i = 0;
                continue;
            }
            if (i + counter >= n - 1)
                break;
            else
        }
        if (flag)
            cout << counter << endl;
        else
            cout << 1 << endl;
    }

    return 0;
}