#include <iostream>

using namespace std;
long long N, P;
int main()
{
    cin >> N >> P;
    long long times = N / (P - 1);
    long long remain = N - (P - 1) * times;
    long long ans;
    if (times & 1)
    {
        ans = P - 1;
    }
    else
        ans = 1;
    for (int i = 1; i <= remain; i++)
    {
        ans = (ans * i) % P;
    }
    cout << ans << endl;
    return 0;
}