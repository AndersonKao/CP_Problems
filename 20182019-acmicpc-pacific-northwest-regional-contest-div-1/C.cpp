#include <bits/stdc++.h>
using namespace std;

long long dp[1010][1010];
const int MOD = 998244353;

int main()
{
    int n, k;
    cin >> n >> k;

    map<int, int> _list;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        _list[tmp]++;
    }

    vector<int> cnt(_list.size());
    int i = 0;
    for (auto it = _list.begin(); it != _list.end(); it++)
    {
        cnt[i++] = it->second;
    }

    int size = _list.size();

    for (int i = 0; i < 1010; i++)
        dp[i][0] = 1;

        dp[1][1] = cnt[0];

    for (int i = 1; i <= size; i++)
        for (int z = 1; z <= i; z++)
        {
            if (i == 1 and z == 1)
                continue;

            dp[i][z] = dp[i-1][z] + dp[i - 1][z - 1] * cnt[i - 1];
            dp[i][z] %= MOD;
        }


        cout << dp[size][k] % MOD << endl;
}