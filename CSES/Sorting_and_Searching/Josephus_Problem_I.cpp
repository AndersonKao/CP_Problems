// AC 2022-05-22 09:33:14
#include <bits/stdc++.h>
using namespace std;

list<int> L;
int main()
{

    int N;
    cin >> N;
    if(N == 1){
        cout << 1;
        return 0;
    }
    for (int i = 1; i <= N; i++){
        L.emplace_back(i);
    }
    auto it = (++L.begin());
    for (int i = 1; i <= N; i++){
        cout << *it << " ";
        auto del = it;
        it++;
        if (it == L.end())
            it = L.begin();
        L.erase(del);
        if(i < N)
        it++;
        if (it == L.end())
            it = L.begin();
    }


    return 0;
}