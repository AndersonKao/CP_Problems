#include <iostream>
#include <cmath>
using namespace std;
#define ULL unsigned long long
ULL dp[4][10005];
// 0 UU
// 1 UL
// 2 LU
// 3 LL

ULL exp_pow(ULL a,ULL b)
{
    ULL ans = 1;

    while(b)
    {
        if(b & 1)
            ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

ULL solve(ULL N)
{
    if(N == 1)
        return 0;
    else if(N == 2)
        return 0;
    for (int i = 0; i < 4; i++)
        dp[i][2] = 1;
    for (ULL i = 3; i <= N; i++)
    {
        dp[0][i] = dp[2][i - 1];
        dp[1][i] = dp[0][i - 1] + dp[2][i - 1];
        dp[2][i] = dp[1][i - 1] + dp[3][i - 1];
        dp[3][i] = dp[1][i - 1] + dp[3][i - 1];
    }
    unsigned int sum = 0;

    for (int i = 0; i < 4; i++)
        sum += dp[i][N];
    return exp_pow(2, N) - sum;
}

int main()
    {

    unsigned long long N;
    while (cin >> N)
    {
        if(N == 0)
            break;
        cout << solve(N) << endl;
    }
    return 0;
}