#include <iostream>
#include <cmath>
using namespace std;
#define MOD 100000007
int n, m;
unsigned long long seqtow[1000006];
unsigned long long seqcla[1000006];

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    unsigned long long towl = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> seqtow[i];
        towl = (towl * (seqtow[i] % MOD)) % MOD;
        // seqtow[i] = pow(seqtow[i], m);
    }
    // cout << towl << endl;
    unsigned long long towlll = 1;
    for (int i = 0; i < m; i++)
    {
        towlll = (towlll * towl) % MOD;
    }
    // cout << towlll << endl;
    unsigned long long floor = 1;
    for (int i = 0; i < m; i++)
    {
        cin >> seqcla[i];
        floor = (floor * (seqcla[i] % MOD)) % MOD;
    }
    unsigned long long floorrr = 1;
    for (int i = 0; i < n; i++)
    {
        floorrr = (floorrr * floor) % MOD;
    }
    // cout << floor << endl;
    unsigned long long ans = 1;
    cout << (towlll * floorrr) % MOD << endl;
    // cout << ans << endl;
    return 0;
}