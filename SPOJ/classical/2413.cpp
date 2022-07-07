#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

int main() {
    int t, _max = 0;
    cin >> t;

    vector<int> _list(t);
    for (auto &i : _list) {
        cin >> i;
        _max = max(i, _max);
    }

    vector<vector<ll>> dp(2, vector<ll>(_max + 1));
    dp[1][1] = dp[0][1] = 1;
    for (int i = 2; i <= _max; i++)
    {
        dp[0][i] = dp[0][i - 1] * 4 + dp[1][i - 1];
        dp[1][i] = dp[0][i - 1] + dp[1][i - 1] * 2;

        dp[0][i] %= MOD;
        dp[1][i] %= MOD;
    }

    for (auto i : _list) {
        cout << (dp[0][i] + dp[1][i]) % MOD << endl;
    }
}