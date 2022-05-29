// AC 2022-05-22 11:15:53
#include <bits/stdc++.h>
using namespace std;
#define al(a) a.begin(), a.end()
template <typename T>
using vec = vector<T>;
int main()
{
    int n;
    cin >> n;
    vec<int> V(n);
    for(int&a: V)
        cin >> a;
    sort(al(V));
    V.resize(distance(V.begin(), unique(al(V))));
    cout << V.size();
    return 0;
}