// AC
#include <iostream>
using namespace std;
int mem[10000][1000] = {0};
int x(int n, int m)
{
    if (m == 1 || n == m)
        return 1;
    if (mem[n][m])
        return mem[n][m];
    return mem[n][m] = x(n - 1, m - 1) + x(n - 1, m);
}

int main()
{
    int T, n, m;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        cout << x(n, m) << endl;
    }
}