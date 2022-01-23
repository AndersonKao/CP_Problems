#include <iostream>
#include <algorithm>
#include <cstring>
#define maxn 1005
#define maxtar 1005
using namespace std;
int coins[maxn];
int dp[maxtar];

void solve(int n, int tar)
{
    int price;
    for (int coin_id = 0; coin_id < n; coin_id++)
    {
        for (int price = coins[coin_id]; price <= tar; price++)
        {
            if (dp[price - coins[coin_id]] != 0)
            {
                if (dp[price] == 0)
                    dp[price] = dp[price - coins[coin_id]] + 1;
                else
                    dp[price] = min(dp[price - coins[coin_id]] + 1, dp[price]);
            }
        }
    }
}

int main()
{
    int T, n, tar;
    cin >> T;
    while (T--)
    {
        // reset dp arr
        memset(dp, 0, sizeof(dp));

        cin >> n >> tar;
        for (int i = 0; i < n; i++)
        {
            cin >> coins[i];
            dp[coins[i]] = 1;
        }
        solve(n, tar);
        cout << (dp[tar] == 0 ? -1 : dp[tar]);
        cout << '\n';
    }

    return 0;
}