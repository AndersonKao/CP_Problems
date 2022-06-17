#include <bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x << " <: " << x << endl;
int main()
{

    int n;
        char prev = cout.fill('-');
        cout << prev << endl;
        cout << "whoamli: " << 23 << endl;
        cout << setw(17) << setbase(16)<< 85 << endl;
        cout << setw(13) << 12 << endl;
        cout.width(20);
        cout.fill(prev);
        cout << "whoamli: " << 23 << "\n";
        cout << setw(20) << setfill('?') << hex << 85 << endl;
        cout << setw(20) << dec << 12 << endl;
    return 0;
}