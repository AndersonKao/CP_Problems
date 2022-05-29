#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
template <typename T>
using vec = vector<T>;
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vec<int> V1(n), V2(m);
    for(int& a: V1)
        cin >> a;
    for(int &a: V2)
        cin >> a;
    sort(al(V1));
    sort(al(V2));
    auto it = V1.begin(), it2 = V2.begin();
    int cnt = 0;
    while(it2 != V2.end() && *it2 < *it - k)
        it2++;
    auto it2b = it2;
    while (it != V1.end())
    {
        while(it2b != V2.end() && *it2b <= *it + k)
            it2b++;
        while(it2 != V2.end() && *it2 < *it-k)
            it2++;
        if(it2 != it2b){
            it2++;
            cnt++;
        }
        it++;
    }
    cout << cnt << endl;
    return 0;
}