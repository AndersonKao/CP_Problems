#include <iostream>
using namespace std;

using ll = long long;
int main()
{
    for (int i = 1; i < 100000; i++)
        cout << i << endl;
    cout << 0;
    ll a, b;
    while (cin >> a >> b)
        cout << a % b << endl;
    return 0;
}