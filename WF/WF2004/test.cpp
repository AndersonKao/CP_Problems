#include <bits/stdc++.h>
using namespace std;

using pii = pair < int, int>;
template <typename T>
using vec = vector<T>;
int main()
{
    auto cmp = [](pii a, pii b)
    {
        if(a.second == b.second)
        {
            return a.first > b.first;
        }
        return a.second > b.second;
    };
    priority_queue<pii, vec<pii>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < 10000; i++){

        pq.emplace(rand() % 10000, rand() % 10000);
    }
    while(!pq.empty()){
        cout << pq.top().first << ", " << pq.top().second << endl;
        pq.pop();
    }
        cout << (pii(-9, 0) > pii(-9, -2))
             << endl;
    cout << (pii(8, -2) < pii(-9, -2)) << endl;
    cout << (pii(-9, -2) < pii(-9, -1)) << endl;

    return 0;
}