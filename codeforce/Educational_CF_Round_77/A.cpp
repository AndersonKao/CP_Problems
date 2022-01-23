#include <iostream>
int ev[10005];
using namespace std;
int main()
{
    int T, c, sum;
    unsigned long long ans;
    cin >> T;
    while (T--)
    {
        cin >> c >> sum;
        for (int i = 0; i < c; i++)
        {
            ev[i] = 0;
        }
        int tmp = sum / c, ans = 0;
        while (sum > c)
        {
            sum -= tmp * c;
            for (int i = 0; i < c; i++)
            {
                ev[i] += tmp;
            }
        }
        for (int i = 0; i < sum; i++)
        {
            ev[i] += 1;
        }
        for(int i=0;i<c;i++)
            if(ev[i]!=0)
                ans += ev[i] * ev[i];
            else break;
        cout << ans << "\n";
    }
    

    return 0;
}