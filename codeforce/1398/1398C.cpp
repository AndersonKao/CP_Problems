#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
// #include <bits/stdc++.h>
using namespace std;

#define MAXN 200005

int T;
long long ans;
int dataseq[MAXN];
long long sum;
map<int, long long> M;
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    string str;
    int L;
    while (T--)
    {
        M.clear();
        sum = ans = 0;
        cin >> L;
        cin >> str;
        M[0] = 1;
        for (int i = 0; i < L; i++)
        {
            sum += (str[i] - '0' - 1);
            ans += M[sum];
            M[sum]++;
        }
        cout << ans << endl;
    }
    return 0;
}