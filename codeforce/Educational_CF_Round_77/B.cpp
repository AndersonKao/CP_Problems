#include <iostream>
using namespace std;
bool flag;
bool poss[10000][10000];
bool dp(int a, int b)
{
    if (a < 0 || b < 0)
        return false;
    if (a == 0 && b == 0 && flag == false)
    {
        cout << "YES\n";
        flag = true;
        return true;
    }
    if (b > a)
    {
        int c = a;
        a = b;
        b = c;
    }
    if (poss[a][b] == false)
        return false;
    for (int i = a / 2; i >= 1; i--)
        if ((a - 2 * i) >= 0)
            return dp(a - 2 * i, b - i);
}

int main()
{
    int T, a, b;
    cin >> T;
    while (T--)
    {
        flag = false;
        cin >> a >> b;
        if (b > a)
        {
            int c = a;
            a = b;
            b = c;
        }
        for (int i = b; i > 0; i--)
            for (int j = i; j > 0; j--)
                poss[i][j] = true;
        dp(a, b);
        if (!flag)
            cout << "NO"
                 << "\n";
    }
}