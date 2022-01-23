// AC Sep/07/2020 20:03UTC+8
#include <cstring>
#include <iostream>
#include <algorithm>
// #define LOCAL
using namespace std;

int ans[1000005];
int b[1000005];
bool beacon[1000005] = {false};

int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n;
    cin >> n;
    int maxpos = 0;
    int pos, level;
    for (int i = 1; i <= n; i++)
    {
        cin >> pos >> level;
        maxpos = max(maxpos, pos);
        b[pos] = level;
        beacon[pos] = true;
    }
    if(beacon[0])
        ans[0] = 1;

    for (int i = 1; i <= maxpos; i++)
    {
        if (beacon[i])
        {
            if (i - b[i] - 1 < 0) //
            {
                ans[i] = 1;
            }
            else
            {
                ans[i] = ans[i - b[i] - 1] + 1;
            }
        }
        else
        {
            ans[i] = ans[i - 1];
        }
    }
    #ifdef LOCAL
        for (int i = 1; i <= maxpos; i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    #endif
    int ANS = 0;
    for (int i = 0; i <= maxpos; i++)
    {
        ANS = max(ANS, ans[i]);
    }
    cout << n - ANS << endl;
    return 0;
}